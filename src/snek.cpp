/**
 * @copyright 2021 YelloSoft
 */

#include <cstdlib>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

#include "ryml.hpp"
#include "ryml_std.hpp"

#include "snek/snek.hpp"

namespace snek {
[[nodiscard]] std::optional<std::string> Ship::Parse(const c4::yml::ConstNodeRef &root) {
    if (!root.is_map()) {
        return "ship is not a map";
    }

    if (!root.has_child("image")) {
        return "missing image";
    }

    const c4::yml::ConstNodeRef image_node{ root["image"] };
    std::string im;
    image_node >> im;

    if (im.empty()) {
        return "blank image";
    }

    this->image = im;

    if (!root.has_child("targets")) {
        return "missing targets";
    }

    const auto targets_node{ root["targets"] };
    std::vector<std::string> ts;

    for (const auto &&target_node : targets_node) {
        std::string t;
        target_node >> t;
        ts.push_back(t);
    }

    if (ts.empty()) {
        return "empty targets";
    }

    this->targets = ts;
    return std::nullopt;
}

void Ship::Format(c4::yml::NodeRef &root) const {
    root.append_child() << c4::yml::key("image") << c4::to_csubstr(this->image.c_str());

    root.append_child() << c4::yml::key("targets");

    auto targets_node = root["targets"];
    targets_node |= c4::yml::SEQ;

    for (const auto &target : targets) {
        targets_node.append_child() = c4::to_csubstr(target.c_str());
    }
}

std::ostream &operator<<(std::ostream &out, const Ship &o) {
    ryml::Tree tree;
    ryml::NodeRef root{ tree.rootref() };
    o.Format(root);
    return out << tree;
}

[[nodiscard]] std::optional<std::string> Config::LaunchShip(const Ship &ship, const std::string &cwd) const {
    for (const auto &target : ship.targets) {
        std::cerr << "building " << target << "\n";

        std::stringstream command_stream;
        command_stream << "docker "
                       << "run "
                       << "--rm "
                       << "-e TARGET=" << target << " "
                       << "-v " << cwd << ":/src "
                       << ship.image << " "
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
    }

    return std::nullopt;
}

[[nodiscard]] std::optional<std::string> Config::Launch() const {
    const std::string cwd{ std::filesystem::current_path().string() };

    if (debug) {
        std::cerr << "cwd: " << cwd << "\n";
    }

    for (const Ship &ship : ships) {
        if (const auto err_opt = LaunchShip(ship, cwd)) {
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

    if (!root.has_child("ships")) {
        return "missing ships";
    }

    const c4::yml::ConstNodeRef ships_node{ root["ships"] };
    std::vector<Ship> ss;

    for (const auto &&ship_node : ships_node) {
        Ship ship;

        if (const auto err_opt = ship.Parse(ship_node)) {
            return *err_opt;
        }

        ss.push_back(ship);
    }

    if (ss.empty()) {
        return "empty ships";
    }

    this->ships = ss;
    return std::nullopt;
}

void Config::Format(c4::yml::NodeRef &root) const {
    if (this->debug) {
        root["debug"] << ryml::to_csubstr("true");
    } else {
        root["debug"] << ryml::to_csubstr("false");
    }

    root["build_command"] << ryml::to_csubstr(this->build_command);

    auto ships_node = root["ships"];
    ships_node |= ryml::SEQ;

    for (const auto &ship : this->ships) {
        auto ship_node = ships_node.append_child();
        ship_node |= ryml::MAP;
        ryml::NodeRef shipRoot{ ship_node };
        ship.Format(shipRoot);
        ship_node = shipRoot;
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

    if (config.ships.empty()) {
        result = "empty ships";
        return result;
    }

    result = config;
    return result;
}
}
