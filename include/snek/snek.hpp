#pragma once

/**
 * @copyright 2021 YelloSoft
 */

#include <optional>
#include <string>
#include <vector>

#include "yaml-cpp/yaml.h"

namespace snek {
constexpr auto Version = "0.0.2";

constexpr auto ConfigFile = "snek.yaml";

constexpr auto BinaryCacheDir = "bin";

struct Ship {
    std::string image = "";

    std::vector<std::string> targets;
};

YAML::Emitter &operator<<(YAML::Emitter &out, const Ship &o);

struct Config {
    bool debug = false;

    std::string build_command = "";

    std::vector<Ship> ships;

    void LaunchShip(const Ship &ship, const std::string &cwd) const;

    void Launch() const;
};

YAML::Emitter &operator<<(YAML::Emitter &out, const Config &o);

Config Load();
}

namespace YAML {
template <>
struct convert<snek::Ship> {
    static bool decode(const Node &n, snek::Ship &o) { // NOLINT
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
    static bool decode(const Node &n, snek::Config &o) { // NOLINT
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
