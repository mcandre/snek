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

namespace snek {
void Ship::Launch(const std::string &cwd) const {
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

std::ostream &operator<<(std::ostream &os, const Ship &o) {
    os << "Ship {"
       << " image: " << o.image
       << ", targets: [ ";

    for (const auto &target : o.targets) {
        os << target << ",";
    }

    return os << " ], build_command: " << o.build_command
              << " }";
}

void Config::Launch() const {
    const auto cwd = std::filesystem::current_path().string();

    for (const auto &ship : ships) {
        ship.Launch(cwd);
    }
}

Config Load() {
    Config config;

    const YAML::Node node = YAML::LoadFile(ConfigFile);
    const auto build_command_override = node["build_command"];

    if (build_command_override) {
        config.build_command = build_command_override.as<std::string>();

        for (auto i = size_t(0); i < config.ships.size(); i++) {
            config.ships[i].build_command = config.build_command;
        }
    }

    const auto ship_overrides = node["ships"];

    if (ship_overrides) {
        std::vector<Ship> ships;

        for (const auto &ship_override : ship_overrides) {
            Ship ship;
            ship.build_command = config.build_command;
            const auto ship_build_command_override = ship_override["build_command"];

            if (ship_build_command_override) {
                ship.build_command = ship_build_command_override.as<std::string>();
            }

            const auto image_override = ship_override["image"];

            if (image_override) {
                ship.image = image_override.as<std::string>();
            }

            ship.targets = ship_override["targets"].as<std::vector<std::string>>();
            ships.push_back(ship);
        }

        config.ships = ships;
    }

    if (config.build_command.empty()) {
        throw "error: no build_command specified"s;
    }

    if (config.ships.empty()) {
        throw "error: no ships specified"s;
    }

    return config;
}

std::ostream &operator<<(std::ostream &os, const Config &o) {
    os << "Config {"
       << " build_command: " << o.build_command
       << ", ships: [ ";

    for (const auto &ship : o.ships) {
        os << ship << ",";
    }

    return os << " ] }";
}
}
