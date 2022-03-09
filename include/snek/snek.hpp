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
