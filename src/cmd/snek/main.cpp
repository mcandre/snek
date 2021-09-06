/**
 * @copyright 2021 YelloSoft
 */

#include <cstdlib>

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "snek/snek.hpp"
#include "yaml-cpp/yaml.h"

void Usage(const char *program) {
    std::cerr << "Usage: " << program << " [options]" << std::endl
              << std::endl;

    std::cerr << "-d\tEnable debugging information" << std::endl
              << "-v\tShow version information" << std::endl
              << "-h\tShow usage information" << std::endl;
}

int main(int argc, const char **argv) {
    bool debug = false;

    const auto *program = argv[0];
    const auto args = std::vector<std::string_view>{ argv, argv + argc };

    size_t i(1);
    for (; i < args.size(); i++) {
        const auto arg = args[i];

        if (arg == "-d") {
            debug = true;
            continue;
        }

        if (arg == "-h") {
            Usage(program);
            return EXIT_SUCCESS;
        }

        Usage(program);
        return EXIT_FAILURE;
    }

    try {
        const auto config = snek::Load();

        if (debug) {
            std::cerr << config << std::endl;
        }

        config.Launch();
        return EXIT_SUCCESS;
    } catch (const YAML::BadFile &err) {
        std::cerr << "error: could not open config file for reading: " << snek::ConfigFile << std::endl;
    } catch (const YAML::ParserException &err) {
        std::cerr << err.what() << std::endl;
    } catch (const std::string &err) {
        std::cerr << err << std::endl;
        return EXIT_FAILURE;
    }
}
