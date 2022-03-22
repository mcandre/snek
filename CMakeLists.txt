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
    set(CPPFLAGS "/EHsc /Ox /Wv:18 /INCREMENTAL:NO /WX /W4 /wd4204")
    set(CXXFLAGS "/std:c++17")
    set(CFLAGS "/std:c17")
else()
    set(CPPFLAGS "-O3 -Werror -Wextra -Wall -pedantic")
    set(CXXFLAGS "-Weffc++ -std=c++17")
    set(CFLAGS "-std=gnu17")

    if(CMAKE_C_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmost")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wmost")

        if(NOT CMAKE_SYSTEM_NAME MATCHES "Darwin")
            set(CMAKE_CXX_CLANG_TIDY clang-tidy -header-filter=${CMAKE_SOURCE_DIR})
            set(CMAKE_C_CLANG_TIDY clang-tidy -header-filter=${CMAKE_SOURCE_DIR})
        endif()
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

add_custom_target(docker-build-darwin
                  COMMAND docker build -t mcandre/snek:darwin .
                  WORKING_DIRECTORY docker/darwin
)
add_custom_target(docker-build-dragonflybsd
                  COMMAND docker build -t mcandre/snek:dragonflybsd .
                  WORKING_DIRECTORY docker/dragonflybsd
)
add_custom_target(docker-build-freebsd
                  COMMAND docker build -t mcandre/snek:freebsd .
                  WORKING_DIRECTORY docker/freebsd
)
add_custom_target(docker-build-musl-alpine
                  COMMAND docker build -t mcandre/snek:musl-alpine .
                  WORKING_DIRECTORY docker/musl-alpine
)
add_custom_target(docker-build-netbsd
                  COMMAND docker build -t mcandre/snek:netbsd .
                  WORKING_DIRECTORY docker/netbsd
)
add_custom_target(docker-build-openbsd
                  COMMAND docker build -t mcandre/snek:openbsd .
                  WORKING_DIRECTORY docker/openbsd
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
                  docker-build-darwin
                  docker-build-dragonflybsd
                  docker-build-freebsd
                  docker-build-musl-alpine
                  docker-build-netbsd
                  docker-build-openbsd
                  docker-build-ubuntu-mingw
                  docker-build-ubuntu-other
                  docker-build-ubuntu-x86
)

add_custom_target(publish-darwin
                  COMMAND docker push mcandre/snek:darwin
)
add_custom_target(publish-dragonflybsd
                  COMMAND docker push mcandre/snek:dragonflybsd
)
add_custom_target(publish-freebsd
                  COMMAND docker push mcandre/snek:freebsd
)
add_custom_target(publish-musl-alpine
                  COMMAND docker push mcandre/snek:musl-alpine
)
add_custom_target(publish-netbsd
                  COMMAND docker push mcandre/snek:netbsd
)
add_custom_target(publish-openbsd
                  COMMAND docker push mcandre/snek:openbsd
)
add_custom_target(publish-ubuntu-mingw
                  COMMAND docker push mcandre/snek:ubuntu-mingw
)
add_custom_target(publish-ubuntu-other
                  COMMAND docker push mcandre/snek:ubuntu-other
)
add_custom_target(publish-ubuntu-x86
                  COMMAND docker push mcandre/snek:ubuntu-x86
)

add_custom_target(publish
                  DEPENDS
                  publish-darwin
                  publish-dragonflybsd
                  publish-freebsd
                  publish-musl-alpine
                  publish-netbsd
                  publish-openbsd
                  publish-ubuntu-mingw
                  publish-ubuntu-other
                  publish-ubuntu-x86
)
