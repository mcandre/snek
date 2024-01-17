cmake_minimum_required(VERSION 3.5)

set(CMAKE_MESSAGE_LOG_LEVEL "WARNING")
set(EXECUTABLE_OUTPUT_PATH "../bin")
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

project(snek)

file(GLOB_RECURSE C_SOURCE_FILES *.h *.c)
file(GLOB_RECURSE CPP_SOURCE_FILES *.cppm *.hpp *.cpp)
file(GLOB_RECURSE CXX_SOURCE_FILES *.cppm *.hpp *.cpp *.h *.c)

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
else()
    set(CPPFLAGS "-O3 -Werror -Wextra -Wall -pedantic")
    set(CXXFLAGS "-Weffc++")

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
target_link_libraries(snek CONAN_PKG::rapidyaml)

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

add_custom_target(cpplint COMMAND cpplint --recursive ../include ../src)
add_custom_target(clang-format COMMAND clang-format -i ${CXX_SOURCE_FILES})
add_custom_target(yamllint COMMAND yamllint -s ../.yamllint ..)
add_custom_target(unmake COMMAND unmake ..)
add_custom_target(unmake_dry_run COMMAND unmake -n ..)

# Missing linter ports
if(MSVC)
    add_custom_target(lint DEPENDS yamllint unmake)
else()
    add_custom_target(lint DEPENDS cpplint clang-format yamllint unmake unmake_dry_run)
endif()

# Some toolchains (esp. non-Linux targets) break on non-x86 family Docker platforms.
set(EXCLUDE_ARCH "arm64,arm/v6,arm/v7,mips64le,ppc64le,riscv64,s390x")

add_custom_target(docker-build-darwin
                  COMMAND tug -t mcandre/snek:darwin -exclude-arch "${EXCLUDE_ARCH}"
                  WORKING_DIRECTORY ../docker/darwin
)
add_custom_target(docker-build-freebsd
                  COMMAND tug -t mcandre/snek:freebsd -exclude-arch "${EXCLUDE_ARCH}"
                  WORKING_DIRECTORY ../docker/freebsd
)
add_custom_target(docker-build-musl-alpine
                  COMMAND tug -t mcandre/snek:musl-alpine -exclude-arch "${EXCLUDE_ARCH}"
                  WORKING_DIRECTORY ../docker/musl-alpine
)
add_custom_target(docker-build-netbsd
                  COMMAND tug -t mcandre/snek:netbsd -exclude-arch "${EXCLUDE_ARCH}"
                  WORKING_DIRECTORY ../docker/netbsd
)
add_custom_target(docker-build-openbsd
                  COMMAND tug -t mcandre/snek:openbsd -exclude-arch "${EXCLUDE_ARCH}"
                  WORKING_DIRECTORY ../docker/openbsd
)
add_custom_target(docker-build-ubuntu-mingw
                  COMMAND tug -t mcandre/snek:ubuntu-mingw -exclude-arch "${EXCLUDE_ARCH}"
                  WORKING_DIRECTORY ../docker/ubuntu-mingw
)
add_custom_target(docker-build-ubuntu-other
                  COMMAND tug -t mcandre/snek:ubuntu-other -exclude-arch "${EXCLUDE_ARCH}"
                  WORKING_DIRECTORY ../docker/ubuntu-other
)
add_custom_target(docker-build-ubuntu-x86
                  COMMAND tug -t mcandre/snek:ubuntu-x86 -exclude-arch "${EXCLUDE_ARCH}"
                  WORKING_DIRECTORY ../docker/ubuntu-x86
)

add_custom_target(docker-build
                  DEPENDS
                  docker-build-darwin
                  docker-build-freebsd
                  docker-build-musl-alpine
                  docker-build-netbsd
                  docker-build-openbsd
                  docker-build-ubuntu-mingw
                  docker-build-ubuntu-other
                  docker-build-ubuntu-x86
)

add_custom_target(docker-load-darwin
                  COMMAND tug -t mcandre/snek:darwin -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64
                  WORKING_DIRECTORY ../docker/darwin
)
add_custom_target(docker-load-freebsd
                  COMMAND tug -t mcandre/snek:freebsd -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64
                  WORKING_DIRECTORY ../docker/freebsd
)
add_custom_target(docker-load-musl-alpine
                  COMMAND tug -t mcandre/snek:musl-alpine -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64
                  WORKING_DIRECTORY ../docker/musl-alpine
)
add_custom_target(docker-load-netbsd
                  COMMAND tug -t mcandre/snek:netbsd -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64
                  WORKING_DIRECTORY ../docker/netbsd
)
add_custom_target(docker-load-openbsd
                  COMMAND tug -t mcandre/snek:openbsd -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64
                  WORKING_DIRECTORY ../docker/openbsd
)
add_custom_target(docker-load-ubuntu-mingw
                  COMMAND tug -t mcandre/snek:ubuntu-mingw -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64
                  WORKING_DIRECTORY ../docker/ubuntu-mingw
)
add_custom_target(docker-load-ubuntu-other
                  COMMAND tug -t mcandre/snek:ubuntu-other -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64
                  WORKING_DIRECTORY ../docker/ubuntu-other
)
add_custom_target(docker-load-ubuntu-x86
                  COMMAND tug -t mcandre/snek:ubuntu-x86 -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64
                  WORKING_DIRECTORY ../docker/ubuntu-x86
)

add_custom_target(docker-load
                  DEPENDS
                  docker-load-darwin
                  docker-load-freebsd
                  docker-load-musl-alpine
                  docker-load-netbsd
                  docker-load-openbsd
                  docker-load-ubuntu-mingw
                  docker-load-ubuntu-other
                  docker-load-ubuntu-x86
)

add_custom_target(docker-publish-darwin
                  COMMAND tug -t mcandre/snek:darwin -exclude-arch "${EXCLUDE_ARCH}" -push
                  WORKING_DIRECTORY ../docker/darwin
)
add_custom_target(docker-publish-freebsd
                  COMMAND tug -t mcandre/snek:freebsd -exclude-arch "${EXCLUDE_ARCH}" -push
                  WORKING_DIRECTORY ../docker/freebsd
)
add_custom_target(docker-publish-musl-alpine
                  COMMAND tug -t mcandre/snek:musl-alpine -exclude-arch "${EXCLUDE_ARCH}" -push
                  WORKING_DIRECTORY ../docker/musl-alpine
)
add_custom_target(docker-publish-netbsd
                  COMMAND tug -t mcandre/snek:netbsd -exclude-arch "${EXCLUDE_ARCH}" -push
                  WORKING_DIRECTORY ../docker/netbsd
)
add_custom_target(docker-publish-openbsd
                  COMMAND tug -t mcandre/snek:openbsd -exclude-arch "${EXCLUDE_ARCH}" -push
                  WORKING_DIRECTORY ../docker/openbsd
)
add_custom_target(docker-publish-ubuntu-mingw
                  COMMAND tug -t mcandre/snek:ubuntu-mingw -exclude-arch "${EXCLUDE_ARCH}" -push
                  WORKING_DIRECTORY ../docker/ubuntu-mingw
)
add_custom_target(docker-publish-ubuntu-other
                  COMMAND tug -t mcandre/snek:ubuntu-other -exclude-arch "${EXCLUDE_ARCH}" -push
                  WORKING_DIRECTORY ../docker/ubuntu-other
)
add_custom_target(docker-publish-ubuntu-x86
                  COMMAND tug -t mcandre/snek:ubuntu-x86 -exclude-arch "${EXCLUDE_ARCH}" -push
                  WORKING_DIRECTORY ../docker/ubuntu-x86
)

add_custom_target(docker-publish
                  DEPENDS
                  docker-publish-darwin
                  docker-publish-freebsd
                  docker-publish-musl-alpine
                  docker-publish-netbsd
                  docker-publish-openbsd
                  docker-publish-ubuntu-mingw
                  docker-publish-ubuntu-other
                  docker-publish-ubuntu-x86
)
