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
bool Ship::Parse(const ryml::NodeRef &root) {
    if (!root.is_map()) {
        std::cerr << "ship is not a map" << std::endl;
        return false;
    }

    if (!root.has_child("image")) {
        std::cerr << "missing image" << std::endl;
        return false;
    }

    const auto image_node{ root["image"] };

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

    for (const ryml::NodeRef &&target_node : targets_node) {
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

void Ship::Format(ryml::NodeRef &root) const {
    root["image"] = c4::to_csubstr(this->image.c_str());
    root["targets"] |= ryml::SEQ;

    for (size_t i{ 0 }; i < this->targets.size(); i++) {
        root["targets"][i] = c4::to_csubstr(targets[i].c_str());
    }
}

std::ostream &operator<<(std::ostream &out, const Ship &o) {
    ryml::Tree tree;
    ryml::NodeRef root{ tree.rootref() };
    o.Format(root);
    return out << ryml::emitrs<std::string>(root);
}

void Config::LaunchShip(const Ship &ship, const std::string &cwd) const {
    for (const auto &target : ship.targets) {
        std::cerr << "building " << target << std::endl;

        std::stringstream command;
        command << "docker "
                << "run "
                << "--rm "
                << "-e TARGET=" << target << " "
                << "-v " << cwd << ":/src "
                << ship.image << " "
                << "sh -c \"" << build_command << "\"";

        const std::string command_s{ command.str() };

        if (debug) {
            std::cerr << "command: " << command_s << std::endl;
        }

        const int status{ system(command_s.c_str()) };

        if (status != EXIT_SUCCESS) {
            std::stringstream err;
            err << "error running toolchain command: "
                << command_s
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

bool Config::Parse(const ryml::NodeRef &root) {
    if (!root.is_map()) {
        std::cerr << "invalid map" << std::endl;
        return false;
    }

    if (root.has_child("debug")) {
        const ryml::NodeRef debug_node{ root["debug"] };
        bool debug_override;
        debug_node >> debug_override;
        this->debug = debug_override;
    }

    if (!root.has_child("build_command")) {
        std::cerr << "missing build_command" << std::endl;
        return false;
    }

    const ryml::NodeRef build_command_node{ root["build_command"] };

    std::string c;
    build_command_node >> c;

    if (c.empty()) {
        std::cerr << "blank build_command" << std::endl;
        return false;
    }

    this->build_command = c;

    if (!root.has_child("ships")) {
        std::cerr << "missing ships" << std::endl;
        return false;
    }

    const ryml::NodeRef ships_node{ root["ships"] };

    std::vector<Ship> ss;

    for (const ryml::NodeRef &&ship_node : ships_node) {
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

void Config::Format(ryml::NodeRef &root) const {
    if (this->debug) {
        root["debug"] = ryml::to_csubstr("true");
    } else {
        root["debug"] = ryml::to_csubstr("false");
    }

    root["build_command"] = ryml::to_csubstr(this->build_command);
    root["ships"] |= ryml::SEQ;

    for (size_t i{ 0 }; i < this->ships.size(); i++) {
        root["ships"][i] |= ryml::MAP;
        ryml::NodeRef shipRoot{ root["ships"][i] };
        this->ships[i].Format(shipRoot);
        root["ships"][i] = shipRoot;
    }
}

std::ostream &operator<<(std::ostream &out, const Config &o) {
    ryml::Tree tree{ ryml::Tree() };
    ryml::NodeRef root{ tree.rootref() };
    root |= ryml::MAP;
    o.Format(root);
    return out << ryml::emitrs<std::string>(root);
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
