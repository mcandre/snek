/**
 * @copyright 2021 YelloSoft
 */

#include <cstdlib>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include "ryml.hpp"
#include "ryml_std.hpp"

#include "snek/snek.hpp"

namespace snek {
[[nodiscard]] std::optional<std::string> Config::LaunchImage(const std::string &image, const std::string &target) const {
    std::cerr << "building " << target << "\n";

    std::stringstream command_stream;
    command_stream << "docker "
                   << "run "
                   << "--rm "
                   << "-e TARGET=" << target << " "
                   << "-v " << this->cwd << ":/src "
                   << image << " "
                   << "sh -c \"" << build_command << "\"";
    const std::string command{ command_stream.str() };

    if (debug) {
        std::cerr << "command: " << command << "\n";
    }

    const int status{ system(command.c_str()) };

    if (status != EXIT_SUCCESS) {
        std::stringstream err;
        err << "error running toolchain command: "
            << command
            << " status: "
            << status;
        return err.str();
    }

    return std::nullopt;
}

[[nodiscard]] std::optional<std::string> Config::Launch() const {
    const std::string cwd{ std::filesystem::current_path().string() };

    if (debug) {
        std::cerr << "cwd: " << cwd << "\n";
    }

    if (images.empty()) {
        return "empty custom `images` list";
    }

    for (const auto &image : images) {
        const auto target_iterator{ image_to_target.find(image) };
        const auto target{ target_iterator->second };

        if (const auto err_opt = LaunchImage(image, target)) {
            return *err_opt;
        }
    }

    return std::nullopt;
}

[[nodiscard]] std::optional<std::string> Config::Parse(const c4::yml::ConstNodeRef &root) {
    if (!root.is_map()) {
        return "invalid map";
    }

    if (root.has_child("debug")) {
        const c4::yml::ConstNodeRef debug_node{ root["debug"] };
        bool debug_override{ false };
        debug_node >> debug_override;
        this->debug = debug_override;
    }

    if (!root.has_child("build_command")) {
        return "missing build_command";
    }

    const c4::yml::ConstNodeRef build_command_node{ root["build_command"] };
    std::string cmd;
    build_command_node >> cmd;

    if (cmd.empty()) {
        return "blank build_command";
    }

    this->build_command = cmd;

    if (root.has_child("images")) {
        const c4::yml::ConstNodeRef images_node = root["images"];
        this->images.clear();

        for (const auto image_node : images_node) {
            std::string image;
            image_node >> image;
            this->images.push_back(image);
        }
    }

    return std::nullopt;
}

void Config::Format(c4::yml::NodeRef &root) const {
    if (this->debug) {
        root["debug"] << ryml::to_csubstr("true");
    } else {
        root["debug"] << ryml::to_csubstr("false");
    }

    root["build_command"] << ryml::to_csubstr(this->build_command);

    auto images_node = root["images"];
    images_node |= ryml::SEQ;

    for (const std::string &image : this->images) {
        images_node.append_child() = ryml::to_csubstr(image);
    }
}

std::ostream &operator<<(std::ostream &out, const Config &o) {
    ryml::Tree tree{ ryml::Tree() };
    ryml::NodeRef root{ tree.rootref() };
    root |= ryml::MAP;
    o.Format(root);
    return out << tree;
}

std::variant<Config, std::string> Load() {
    std::variant<Config, std::string> result;
    const std::ifstream is{ ConfigFile };
    std::stringstream buf;
    buf << is.rdbuf();
    ryml::Tree tree{ ryml::parse_in_arena(ryml::to_csubstr(buf.str())) };
    ryml::NodeRef root{ tree.rootref() };

    if (root.is_stream()) {
        if (root.num_children() < 1) {
            result = "invalid yaml";
            return result;
        }

        root = root[0];
    }

    Config config;

    if (const auto err_opt = config.Parse(root)) {
        result = *err_opt;
        return result;
    }

    if (config.build_command.empty()) {
        result = "blank build_command";
        return result;
    }

    config.cwd = std::filesystem::current_path().string();

    const std::regex dockerImagePattern{ DockerImagePattern };

    for (const auto &image : config.images) {
        std::smatch matches;

        if (!std::regex_search(image, matches, dockerImagePattern)) {
            std::stringstream ss;
            ss << "expected pattern `<base>:<target>` for image: "
               << image;
            result = ss.str();
            return result;
        }

        const auto target{ matches[1] };

        config.image_to_target.insert({image, target});
    }

    result = config;
    return result;
}
}
