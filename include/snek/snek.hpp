#pragma once

/**
 * @copyright 2021 YelloSoft
 */

#include <optional>
#include <string>
#include <vector>

#include "yaml-cpp/yaml.h"

namespace snek {
constexpr auto Version = "0.0.1";

constexpr auto ConfigFile = "snek.yaml";

constexpr auto BinaryCacheDir = "bin";

struct Ship {
    std::string image = "";

    std::vector<std::string> targets;

    void Launch(const std::string &cwd, const std::string &build_command) const;
};

YAML::Emitter &operator<<(YAML::Emitter &out, const Ship &o);

struct Config {
    std::string build_command = "";

    std::vector<Ship> ships;

    void Launch() const;
};

YAML::Emitter &operator<<(YAML::Emitter &out, const Config &o);

Config Load();
}
