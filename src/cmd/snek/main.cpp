/**
 * @copyright 2021 YelloSoft
 */

#include <cstdlib>

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "snek/snek.hpp"

/**
 * @brief Usage emits operational documentation.
 *
 * @param program the invoked name of this program
 */
void Usage(const std::string_view &program) {
    std::cerr << "Usage: " << program << " [options]" << std::endl
              << std::endl;

    std::cerr << "-d\tEnable debugging information" << std::endl
              << "-v\tShow version information" << std::endl
              << "-h\tShow usage information" << std::endl;
}

/**
 * @brief main is the entrypoint.
 *
 * @param argc argument count
 * @param argv CLI arguments
 * @returns CLI exit code
 */
int main(int argc, const char **argv) {
    const std::vector<std::string_view> args{ argv, argv + argc };

    if (args.empty()) {
        std::cerr << "error: missing program name" << std::endl;
        return EXIT_FAILURE;
    }

    bool debug{false};

    size_t i(1);
    for (; i < args.size(); i++) {
        const std::string_view arg{args[i]};

        if (arg == "-h") {
            Usage(args[0]);
            return EXIT_SUCCESS;
        }

        if (arg == "-v") {
            std::cout << "snek " << snek::Version << std::endl;
            return EXIT_SUCCESS;
        }

        if (arg == "-d") {
            debug = true;
            continue;
        }

        Usage(args[0]);
        return EXIT_FAILURE;
    }

    try {
        snek::Config config{snek::Load()};

        if (debug) {
            config.debug = debug;

            std::stringstream ss;
            ss << config;
            std::cerr << ss.str() << std::endl
                      << std::endl;
        }

        config.Launch();
        return EXIT_SUCCESS;
    } catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
        return EXIT_FAILURE;
    }
}
