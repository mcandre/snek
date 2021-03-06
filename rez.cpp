#include <cstdlib>

#include <filesystem>
#include <functional>
#include <iostream>
#include <string_view>
#include <sstream>
#include <map>
#include <unordered_set>
#include <vector>

using std::literals::string_view_literals::operator""sv;

std::optional<std::string> GetEnvironmentVariable(const std::string &key) {
    char *transient{ nullptr };

#if defined(_WIN32)
    size_t len{ 0 };
    errno = 0;
    _dupenv_s(&transient, &len, key.c_str());

    if (errno != 0) {
        std::cerr << "error querying environment variable " << key << " errno: " << errno << std::endl;
        free(transient);
        return std::nullopt;
    }

    if (transient != nullptr) {
        const std::string s{ transient };
        free(transient);
        return std::optional(s);
    }

    free(transient);
#else
    transient = getenv(key.c_str());

    if (transient != nullptr) {
        const std::string s{ transient };
        return std::optional(s);
    }
#endif

    return std::nullopt;
}

static int cmake_init() {
    return system("cmake .");
}

static int lint() {
    const int status{ cmake_init() };

    if (status) {
        return status;
    }

    return system("cmake --build . --target lint");
}

static int build() {
    const int status{ cmake_init() };

    if (status != EXIT_SUCCESS) {
        return status;
    }

    return system("cmake --build . --config Release");
}

static int audit() {
#if defined(_WIN32)
    const std::string home_env_var_name{"USERPROFILE"};
#else
    const std::string home_env_var_name{"HOME"};
#endif

    const std::optional<std::string> home_opt{GetEnvironmentVariable(home_env_var_name)};

    if (!home_opt.has_value()) {
        std::cerr << "error missing environment variable: ";
        std::cerr << home_env_var_name;
        return EXIT_FAILURE;
    }

    const std::filesystem::path home{*home_opt};
    const std::filesystem::path conan_data_dir{home / ".conan" / "data"};
    std::stringstream command;
    command << "snyk test --unmanaged --trust-policies"
        << " "
        << conan_data_dir;

    const int status{system(command.str().c_str())};

    if (status) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

static int install() {
    const int status{ build() };

    if (status != EXIT_SUCCESS) {
        return status;
    }

    return system("cmake --build . --target install");
}

static int uninstall() {
    const int status{ cmake_init() };

    if (status != EXIT_SUCCESS) {
        return status;
    }

    return system("cmake --build . --target uninstall");
}

static int clean_bin() {
    std::filesystem::remove_all("bin");
    return EXIT_SUCCESS;
}

static int clean_msvc() {
    std::filesystem::remove_all("x64");
    std::filesystem::remove_all("x86");

    const std::unordered_set<std::string> junk_extensions{
        ".dir",
        ".filters",
        ".obj",
        ".sln",
        ".vcxproj"
    };

    for (const std::filesystem::directory_entry &child : std::filesystem::directory_iterator(std::filesystem::current_path())) {
        const std::filesystem::path child_path{ child.path() };

        if (junk_extensions.find(child_path.extension().string()) != junk_extensions.end()) {
            std::filesystem::remove_all(child_path);
        }
    }

    return EXIT_SUCCESS;
}

static int clean_cmake() {
    std::filesystem::remove_all("install_manifest.txt");
    std::filesystem::remove_all("Makefile");
    std::filesystem::remove_all("CMakeFiles");
    std::filesystem::remove_all("CMakeCache.txt");
    std::filesystem::remove_all("cmake_install.cmake");
    std::filesystem::remove_all("CTestTestfile.cmake");
    std::filesystem::remove_all("Testing");
    return EXIT_SUCCESS;
}

static int clean_conan() {
    std::filesystem::remove_all("conanbuildinfo.cmake");
    std::filesystem::remove_all("graph_info.json");
    std::filesystem::remove_all("conan.lock");
    std::filesystem::remove_all("conanbuildinfo.txt");
    std::filesystem::remove_all("conaninfo.txt");
    return system("conan remove -f \"*\"");
}

static int clean() {
    clean_bin();
    clean_msvc();
    clean_cmake();
    clean_conan();
    return EXIT_SUCCESS;
}

int main(int argc, const char **argv) {
    const std::vector<std::string_view> args{ argv + 1, argv + argc };
    const std::function<int()> default_task{ install };

    if (args.empty()) {
        if (default_task()) {
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    const std::map<std::string_view, std::function<int()>> tasks{
        { "clean"sv, clean },
        { "clean_bin"sv, clean_bin },
        { "clean_cmake"sv, clean_cmake },
        { "clean_conan"sv, clean_conan },
        { "clean_msvc"sv, clean_msvc },
        { "cmake_init"sv, cmake_init },
        { "audit"sv, audit },
        { "build"sv, build },
        { "lint"sv, lint},
        { "install"sv, install },
        { "uninstall"sv, uninstall }
    };

    if (args.front() == "-l") {
        for (const auto &[name, _] : tasks) {
            std::cout << name << std::endl;
        }

        return EXIT_SUCCESS;
    }

    for (const std::string_view &arg : args) {
        try {
            const std::function<int()> f{ tasks.at(arg) };

            if (f()) {
                return EXIT_FAILURE;
            }
        } catch (std::out_of_range &e) {
            std::cerr << "no such task: " << arg << std::endl;
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
