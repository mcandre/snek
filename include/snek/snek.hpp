#pragma once

/**
 * @copyright 2021 YelloSoft
 */

#include <optional>
#include <string>
#include <vector>

#include "ryml_std.hpp"
#include "ryml.hpp"

namespace snek {
constexpr auto Version{"0.0.3"};

constexpr auto ConfigFile{"snek.yaml"};

constexpr auto BinaryCacheDir{"bin"};

struct Ship {
    std::string image{""};

    std::vector<std::string> targets;

    bool Parse(const ryml::NodeRef &root);

    void Format(ryml::NodeRef& root) const;
};

std::ostream &operator<<(std::ostream &out, const Ship &o);

struct Config {
    bool debug{false};

    std::string build_command{""};

    std::vector<Ship> ships;

    bool Parse(const ryml::NodeRef &root);

    void Format(ryml::NodeRef& root) const;

    void LaunchShip(const Ship &ship, const std::string &cwd) const;

    void Launch() const;
};

std::ostream &operator<<(std::ostream &out, const Config &o);

Config Load();
}
