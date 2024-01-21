#pragma once

/**
 * @copyright 2021 YelloSoft
 */

#include <optional>
#include <string>
#include <variant>
#include <vector>

#include "ryml.hpp"
#include "ryml_std.hpp"

namespace snek {
constexpr auto Version{ "0.0.4" };

constexpr auto ConfigFile{ "snek.yaml" };

constexpr auto BinaryCacheDir{ "bin" };

struct Ship {
    std::string image;

    std::vector<std::string> targets;

    [[nodiscard]] std::optional<std::string> Parse(const c4::yml::ConstNodeRef &root);

    void Format(c4::yml::NodeRef &root) const; // NOLINT(runtime/references)
} __attribute__((aligned(64)));

std::ostream &operator<<(std::ostream &out, const Ship &o);

struct Config {
    bool debug{ false };

    std::string build_command;

    std::vector<Ship> ships;

    [[nodiscard]] std::optional<std::string> Parse(const c4::yml::ConstNodeRef &root);

    void Format(c4::yml::NodeRef &root) const; // NOLINT(runtime/references)

    [[nodiscard]] std::optional<std::string> LaunchShip(const Ship &ship, const std::string &cwd) const;

    [[nodiscard]] std::optional<std::string> Launch() const;
} __attribute__((aligned(64)));

std::ostream &operator<<(std::ostream &out, const Config &o);

std::variant<Config, std::string> Load();
}
