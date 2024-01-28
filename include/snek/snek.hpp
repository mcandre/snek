#pragma once

/**
 * @copyright 2021 YelloSoft
 */

#include <optional>
#include <regex>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include "ryml.hpp"
#include "ryml_std.hpp"

namespace snek {
constexpr auto Version{ "0.0.5" };

constexpr auto ConfigFile{ "snek.yaml" };

constexpr auto BinaryCacheDir{ "bin" };

constexpr auto DockerImagePattern{ "^[^:]+:([^:]+)$" };

struct Config {
    bool debug{ false };

    std::string build_command;

    std::vector<std::string> images{
        "mcandre/snek:aarch64-linux-gnu",
        "mcandre/snek:arm-linux-gnueabi",
        "mcandre/snek:arm-linux-gnueabihf",
        "mcandre/snek:arm64-apple-darwin",
        "mcandre/snek:i686-pc-linux-gnu",
        "mcandre/snek:i686-w64-mingw32-posix",
        "mcandre/snek:i686-w64-mingw32-win32",
        "mcandre/snek:m68k-linux-gnu",
        "mcandre/snek:mips-linux-gnu",
        "mcandre/snek:mips64-linux-gnuabi64",
        "mcandre/snek:mips64el-linux-gnuabi64",
        "mcandre/snek:mipsel-linux-gnu",
        "mcandre/snek:mipsisa32r6-linux-gnu",
        "mcandre/snek:mipsisa32r6el-linux-gnu",
        "mcandre/snek:mipsisa64r6el-linux-gnuabi64",
        "mcandre/snek:powerpc-linux-gnu",
        "mcandre/snek:powerpc-linux-gnu",
        "mcandre/snek:powerpc64-linux-gnu",
        "mcandre/snek:powerpc64le-linux-gnu",
        "mcandre/snek:riscv64-linux-gnu",
        "mcandre/snek:s390x-linux-gnu",
        "mcandre/snek:sparc64-linux-gnu",
        "mcandre/snek:x86_64-alpine-linux-musl",
        "mcandre/snek:x86_64-apple-darwin",
        "mcandre/snek:x86_64-linux-gnux32",
        "mcandre/snek:x86_64-pc-linux-gnu",
        "mcandre/snek:x86_64-unknown-freebsd",
        "mcandre/snek:x86_64-unknown-netbsd",
        "mcandre/snek:x86_64-unknown-openbsd",
        "mcandre/snek:x86_64-w64-mingw32-posix",
        "mcandre/snek:x86_64-w64-mingw32-win32",
    };

    /** cwd is overwritten by Load. */
    std::string cwd;

    /** image_to_target is overwritten by Load. */
    std::unordered_map<std::string, std::string> image_to_target;

    [[nodiscard]] std::optional<std::string> Parse(const c4::yml::ConstNodeRef &root);

    void Format(c4::yml::NodeRef &root) const; // NOLINT(runtime/references)

    [[nodiscard]] std::optional<std::string> LaunchImage(const std::string &image, const std::string &target) const;

    [[nodiscard]] std::optional<std::string> Launch() const;
} __attribute__((aligned(128)));

std::ostream &operator<<(std::ostream &out, const Config &o);

std::variant<Config, std::string> Load();
}
