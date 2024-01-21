/**
 * @copyright 2021 YelloSoft
 */

#include <cstdlib>

#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

#include "snek/snek.hpp"

/**
 * @brief Usage emits operational documentation.
 *
 * @param program the invoked name of this program
 */
void Usage(const std::string_view &program) {
    std::cerr << "Usage: " << program << " [options]\n"
              << "\n"
              << "-d\tEnable debugging information\n"
              << "-v\tShow version information\n"
              << "-h\tShow usage information\n";
}

/**
 * @brief main is the entrypoint.
 *
 * @param argc argument count
 * @param argv CLI arguments
 * @returns CLI exit code
 */
int main(int argc, const char **argv) {
    std::vector<std::string_view> args{ argv, argv + argc };

    if (args.empty()) {
        std::cerr << "error: missing program name\n";
        return EXIT_FAILURE;
    }

    const std::string_view program{ args[0] };
    bool debug{ false };

    for (size_t i{ 1 }; i < args.size(); i++) {
        const auto arg = args[i];

        if (arg == "-h") {
            Usage(program);
            return EXIT_SUCCESS;
        }

        if (arg == "-v") {
            std::cout << "snek " << snek::Version << "\n";
            return EXIT_SUCCESS;
        }

        if (arg == "-d") {
            debug = true;
            continue;
        }

        Usage(program);
        return EXIT_FAILURE;
    }

    const auto config_variant{ snek::Load() };

    if (std::holds_alternative<std::string>(config_variant)) {
        auto err{ *std::get_if<std::string>(&config_variant) };
        std::cerr << "error: " << err << "\n";
        return EXIT_FAILURE;
    }

    auto config{ *std::get_if<snek::Config>(&config_variant) };

    if (debug) {
        config.debug = debug;
        std::stringstream ss;
        ss << config;
        std::cerr << ss.str() << "\n\n";
    }

    if (const auto err_opt = config.Launch()) {
        std::cerr << *err_opt << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
