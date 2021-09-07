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

using std::string_literals::operator""s;

namespace YAML {
template<>
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

template<>
struct convert<snek::Config> {
    static bool decode(const Node &n, snek::Config &o) {
        if (!n.IsMap()) {
            return false;
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
void Ship::Launch(const std::string &cwd, const std::string &build_command) const {
    for (const auto &target : targets) {
        std::cerr << "building " << target << std::endl;

        std::stringstream command;
        command << "docker "
                << "run "
                << "--rm "
                << "-e TARGET=" << target << " "
                << "-v " << cwd << ":/src "
                << image << " "
                << build_command;
        std::string command_s = command.str();
        const auto status = system(command_s.c_str());

        if (status != EXIT_SUCCESS) {
            std::stringstream err;
            err << "error running toolchain command: "
                << command_s
                << " status: "
                << status;
            throw err.str();
        }
    }
}

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

void Config::Launch() const {
    const auto cwd = std::filesystem::current_path().string();

    for (const auto &ship : ships) {
        ship.Launch(cwd, build_command);
    }
}

YAML::Emitter &operator<<(YAML::Emitter &out, const Config &o) {
    out << YAML::BeginMap
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
        throw "error: blank build_command"s;
    }

    if (config.ships.empty()) {
        throw "error: empty ships"s;
    }

    return config;
}
}
