#pragma once

/**
 * @copyright 2021 YelloSoft
 */

#include <optional>
#include <string>
#include <vector>

namespace snek {
constexpr auto Version = "0.0.1";

constexpr auto ConfigFile = "snek.yaml";

constexpr auto BinaryCacheDir = "bin";

constexpr auto DefaultBuildCommand = "make";

struct Ship {
    std::string image = "";

    std::vector<std::string> targets;

    std::string build_command = DefaultBuildCommand;

    void Launch(const std::string &cwd) const;
};

std::ostream &operator<<(std::ostream &os, const Ship &o);

struct Config {
    std::string build_command = DefaultBuildCommand;

    std::vector<Ship> ships;

    void Launch() const;
};

std::ostream &operator<<(std::ostream &os, const Config &o);

Config Load();
}
