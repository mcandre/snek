/**
 * @copyright 2021 YelloSoft
 */

#include <cstdlib>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "ryml.hpp"
#include "ryml_std.hpp"

#include "snek/snek.hpp"

namespace snek {
bool Ship::Parse(const c4::yml::ConstNodeRef &root) {
    if (!root.is_map()) {
        std::cerr << "ship is not a map" << std::endl;
        return false;
    }

    if (!root.has_child("image")) {
        std::cerr << "missing image" << std::endl;
        return false;
    }

    const c4::yml::ConstNodeRef image_node{ root["image"] };
    std::string im;
    image_node >> im;

    if (im.empty()) {
        std::cerr << "blank image" << std::endl;
        return false;
    }

    this->image = im;

    if (!root.has_child("targets")) {
        std::cerr << "missing targets" << std::endl;
        return false;
    }

    const auto targets_node{ root["targets"] };
    std::vector<std::string> ts;

    for (const auto &&target_node : targets_node) {
        std::string t;
        target_node >> t;
        ts.push_back(t);
    }

    if (ts.empty()) {
        std::cerr << "empty targets" << std::endl;
        return false;
    }

    this->targets = ts;
    return true;
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

void Config::LaunchShip(const Ship &ship, const std::string &cwd) const {
    for (const auto &target : ship.targets) {
        std::cerr << "building " << target << std::endl;

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
            std::cerr << "command: " << command << std::endl;
        }

        const int status{ system(command.c_str()) };

        if (status != EXIT_SUCCESS) {
            std::stringstream err;
            err << "error running toolchain command: "
                << command
                << " status: "
                << status;
            throw std::runtime_error(err.str());
        }
    }
}

void Config::Launch() const {
    const std::string cwd{ std::filesystem::current_path().string() };

    if (debug) {
        std::cerr << "cwd: " << cwd << std::endl;
    }

    for (const Ship &ship : ships) {
        LaunchShip(ship, cwd);
    }
}

bool Config::Parse(const c4::yml::ConstNodeRef &root) {
    if (!root.is_map()) {
        std::cerr << "invalid map" << std::endl;
        return false;
    }

    if (root.has_child("debug")) {
        const c4::yml::ConstNodeRef debug_node{ root["debug"] };
        bool debug_override;
        debug_node >> debug_override;
        this->debug = debug_override;
    }

    if (!root.has_child("build_command")) {
        std::cerr << "missing build_command" << std::endl;
        return false;
    }

    const c4::yml::ConstNodeRef build_command_node{ root["build_command"] };

    std::string cmd;
    build_command_node >> cmd;

    if (cmd.empty()) {
        std::cerr << "blank build_command" << std::endl;
        return false;
    }

    this->build_command = cmd;

    if (!root.has_child("ships")) {
        std::cerr << "missing ships" << std::endl;
        return false;
    }

    const c4::yml::ConstNodeRef ships_node{ root["ships"] };

    std::vector<Ship> ss;

    for (const auto &&ship_node : ships_node) {
        Ship ship;
        ship.Parse(ship_node);
        ss.push_back(ship);
    }

    if (ss.empty()) {
        std::cerr << "empty ships" << std::endl;
        return false;
    }

    this->ships = ss;
    return true;
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

Config Load() {
    std::ifstream is{ ConfigFile };
    std::stringstream buf;
    buf << is.rdbuf();
    ryml::Tree tree{ ryml::parse_in_arena(ryml::to_csubstr(buf.str())) };
    ryml::NodeRef root{ tree.rootref() };

    if (root.is_stream()) {
        if (root.num_children() < 1) {
            throw std::runtime_error("error: invalid yaml");
        }

        root = root[0];
    }

    Config config;

    if (!config.Parse(root)) {
        throw std::runtime_error("error: invalid yaml");
    }

    if (config.build_command.empty()) {
        throw std::runtime_error("error: blank build_command");
    }

    if (config.ships.empty()) {
        throw std::runtime_error("error: empty ships");
    }

    return config;
}
}
