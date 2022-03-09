/**
 * @copyright 2021 YelloSoft
 */

#include <cstdlib>

#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "snek/snek.hpp"
#include "yaml-cpp/yaml.h"

namespace YAML {
template <>
struct convert<snek::Ship> {
    static bool decode(const Node &n, snek::Ship &o) {
        if (!n.IsMap()) {
            return false;
        }

        const auto image_node = n["image"];

        if (!image_node) {
            return false;
        }

        const auto image = image_node.as<std::string>();

        if (image.empty()) {
            return false;
        }

        o.image = image;

        const auto targets_node = n["targets"];

        if (!targets_node) {
            return false;
        }

        const auto targets = targets_node.as<std::vector<std::string>>();

        if (targets.empty()) {
            return false;
        }

        o.targets = targets;
        return true;
    }
};

template <>
struct convert<snek::Config> {
    static bool decode(const Node &n, snek::Config &o) {
        if (!n.IsMap()) {
            return false;
        }

        const auto debug_node = n["debug"];

        if (debug_node) {
            const auto debug_override = debug_node.as<bool>();
            o.debug = debug_override;
        }

        const auto build_command_node = n["build_command"];

        if (!build_command_node) {
            return false;
        }

        const auto build_command = build_command_node.as<std::string>();

        if (build_command.empty()) {
            return false;
        }

        o.build_command = build_command;

        const auto ships_node = n["ships"];

        if (!ships_node) {
            return false;
        }

        const auto ships = ships_node.as<std::vector<snek::Ship>>();

        if (ships.empty()) {
            return false;
        }

        o.ships = ships;
        return true;
    }
};
}

namespace snek {
YAML::Emitter &operator<<(YAML::Emitter &out, const Ship &o) {
    out << YAML::BeginMap
        << YAML::Key << "image" << YAML::Value << o.image
        << YAML::Key << "targets" << YAML::BeginSeq;

    for (const auto &target : o.targets) {
        out << target;
    }

    return out << YAML::EndSeq
               << YAML::EndMap;
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

        const std::string command_s = command.str();

        if (debug) {
            std::cerr << "command: " << command_s << std::endl;
        }

        const auto status = system(command_s.c_str());

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
    const auto cwd = std::filesystem::current_path().string();

    if (debug) {
        std::cerr << "cwd: " << cwd << std::endl;
    }

    for (const auto &ship : ships) {
        LaunchShip(ship, cwd);
    }
}

YAML::Emitter &operator<<(YAML::Emitter &out, const Config &o) {
    out << YAML::BeginMap
        << YAML::Key << "debug" << YAML::Value << o.debug
        << YAML::Key << "build_command" << YAML::Value << o.build_command
        << YAML::Key << "ships" << YAML::Value << YAML::BeginSeq;

    for (const auto &ship : o.ships) {
        out << ship;
    }

    return out << YAML::EndSeq
               << YAML::EndMap;
}

Config Load() {
    const YAML::Node node = YAML::LoadFile(ConfigFile);
    auto config = node.as<Config>();

    if (config.build_command.empty()) {
        throw std::runtime_error("error: blank build_command");
    }

    if (config.ships.empty()) {
        throw std::runtime_error("error: empty ships");
    }

    return config;
}
}
