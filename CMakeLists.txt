cmake_minimum_required(VERSION 3.4)
set(CMAKE_MESSAGE_LOG_LEVEL "WARNING")
set(EXECUTABLE_OUTPUT_PATH "bin")
project(snek)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

if(MSVC)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${EXECUTABLE_OUTPUT_PATH}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${EXECUTABLE_OUTPUT_PATH}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${EXECUTABLE_OUTPUT_PATH}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${EXECUTABLE_OUTPUT_PATH}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${EXECUTABLE_OUTPUT_PATH}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${EXECUTABLE_OUTPUT_PATH}")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /INCREMENTAL:NO /std:c17 /EHsc /Ox /WX /W4 /wd4204 /Wv:18")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /INCREMENTAL:NO /std:c++17 /EHsc /Ox /WX /W4 /wd4204 /Wv:18")
else()
    set(UNIX_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Werror")
    set(UNIX_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Werror")
    set(GNU_C_FLAGS "${UNIX_C_FLAGS} -std=gnu17 -Wextra -Wall -pedantic")
    set(GNU_CXX_FLAGS "${UNIX_CXX_FLAGS} -std=c++17 -Wextra -Wall -pedantic -Weffc++")
    set(LLVM_FLAGS "-Wmost")
    set(CLANG_C_FLAGS "${GNU_C_FLAGS} ${LLVM_FLAGS}")
    set(CLANG_CXX_FLAGS "${GNU_CXX_FLAGS} ${LLVM_FLAGS}")

    if(CMAKE_C_COMPILER_ID MATCHES "Clang")
        set(CMAKE_C_FLAGS "${CLANG_C_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CLANG_CXX_FLAGS}")

        if(NOT CMAKE_SYSTEM_NAME MATCHES "Darwin")
            set(CMAKE_C_CLANG_TIDY clang-tidy -header-filter=${CMAKE_SOURCE_DIR})
            set(CMAKE_CXX_CLANG_TIDY clang-tidy -header-filter=${CMAKE_SOURCE_DIR})
        endif()
    else()
        set(CMAKE_C_FLAGS "${GNU_C_FLAGS}")
        set(CMAKE_CXX_FLAGS "${GNU_CXX_FLAGS}")
    endif()
endif()

include_directories(include ${CONAN_INCLUDE_DIRS})

add_executable(snek src/cmd/snek/main.cpp src/snek.cpp)
target_link_libraries(snek CONAN_PKG::yaml-cpp)

if(MSVC)
    set(HOME "$ENV{HOMEDRIVE}$ENV{HOMEPATH}")
    set(ARTIFACT snek.exe)
else()
    set(HOME "$ENV{HOME}")
    set(ARTIFACT snek)
endif()

file(TO_NATIVE_PATH "${HOME}/bin" INSTALL_DIR)
file(TO_NATIVE_PATH "${INSTALL_DIR}/${ARTIFACT}" INSTALL_FILE)

install(PROGRAMS $<TARGET_FILE:snek> DESTINATION "${INSTALL_DIR}")

if(MSVC)
    add_custom_target(uninstall COMMAND del /s /q "${INSTALL_FILE}")
else()
    add_custom_target(uninstall COMMAND rm -f "${INSTALL_FILE}")
endif()

add_custom_target(cppcheck COMMAND cppcheck -q --force --enable=all --inline-suppr --suppressions-list=suppressions.cfg --error-exitcode=1 -U__SANITIZE_ADDRESS__ -I include src)
add_custom_target(cpplint COMMAND sail include src | xargs -n 1 cpplint)
add_custom_target(vera++ COMMAND sail include src | xargs -n 1 vera++)
add_custom_target(clang-format COMMAND sail include src | xargs -n 1 clang-format -i)

# Missing linter ports
if(MSVC)
    add_custom_target(lint DEPENDS cppcheck)
else()
    add_custom_target(lint DEPENDS cppcheck cpplint vera++ clang-format)
endif()

add_custom_target(doc COMMAND doxygen Doxyfile)

add_custom_target(docker-build-musl-alpine
                  COMMAND docker build -t mcandre/snek:musl-alpine .
                  WORKING_DIRECTORY docker/musl-alpine
)
add_custom_target(docker-build-musl-void
                  COMMAND docker build -t mcandre/snek:musl-void .
                  WORKING_DIRECTORY docker/musl-void
)
add_custom_target(docker-build-ubuntu-mingw
                  COMMAND docker build -t mcandre/snek:ubuntu-mingw .
                  WORKING_DIRECTORY docker/ubuntu-mingw
)
add_custom_target(docker-build-ubuntu-other
                  COMMAND docker build -t mcandre/snek:ubuntu-other .
                  WORKING_DIRECTORY docker/ubuntu-other
)
add_custom_target(docker-build-ubuntu-x86
                  COMMAND docker build -t mcandre/snek:ubuntu-x86 .
                  WORKING_DIRECTORY docker/ubuntu-x86
)

add_custom_target(docker-build
                  DEPENDS
                  docker-build-musl-alpine
                  docker-build-musl-void
                  docker-build-ubuntu-mingw
                  docker-build-ubuntu-other
                  docker-build-ubuntu-x86
)

add_custom_target(publish-musl-alpine DEPENDS docker-build-musl-alpine)
add_custom_target(publish-musl-void DEPENDS docker-build-musl-void)
add_custom_target(publish-ubuntu-mingw DEPENDS docker-build-ubuntu-mingw)
add_custom_target(publish-ubuntu-other DEPENDS docker-build-ubuntu-other)
add_custom_target(publish-ubuntu-x86 DEPENDS docker-build-ubuntu-x86)

add_custom_target(publish
                  DEPENDS
                  publish-musl-alpine
                  publish-musl-void
                  publish-ubuntu-mingw
                  publish-ubuntu-other
                  publish-ubuntu-x86
)

add_custom_target(clean-cmake COMMAND sh clean-cmake.sh)
