cmake_minimum_required(VERSION 3.8)

set(CMAKE_MESSAGE_LOG_LEVEL "WARNING")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

project(snek)

file(GLOB_RECURSE CPP_SOURCE_FILES *.cppm *.hpp *.cpp *.h *.c)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(CPPFLAGS "$ENV{CPPFLAGS} -O3 -Werror -Wextra -Wall -pedantic")
set(CXXFLAGS "$ENV{CXXFLAGS}")

# Work around linter bugs in old MinGW compilers
if(NOT "$ENV{TARGET}" MATCHES "w64")
    set(CXXFLAGS "${CXXFLAGS} -Weffc++")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CPPFLAGS} ${CXXFLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CPPFLAGS}")

if(CMAKE_C_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmost")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wmost")
    set(CMAKE_CXX_CLANG_TIDY clang-tidy -header-filter=${CMAKE_SOURCE_DIR})
    set(CMAKE_C_CLANG_TIDY clang-tidy -header-filter=${CMAKE_SOURCE_DIR})
endif()

include_directories(include ${CONAN_INCLUDE_DIRS})
add_executable(snek src/cmd/snek/main.cpp src/snek.cpp)
target_link_libraries(snek CONAN_PKG::rapidyaml)

set(HOME "$ENV{HOME}")
set(ARTIFACT snek)

file(TO_NATIVE_PATH "${HOME}/bin" INSTALL_DIR)
file(TO_NATIVE_PATH "${INSTALL_DIR}/${ARTIFACT}" INSTALL_FILE)

install(PROGRAMS $<TARGET_FILE:snek> DESTINATION "${INSTALL_DIR}")

add_custom_target(uninstall COMMAND rm -f "${INSTALL_FILE}")

add_custom_target(cpplint COMMAND cpplint --recursive ../include ../src)
add_custom_target(clang-format COMMAND clang-format -i ${CPP_SOURCE_FILES})
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

add_custom_target(docker-load-aarch64-linux-gnu            COMMAND tug -t mcandre/snek:aarch64-linux-gnu            -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/aarch64-linux-gnu)
add_custom_target(docker-load-arm-linux-gnueabi            COMMAND tug -t mcandre/snek:arm-linux-gnueabi            -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/arm-linux-gnueabi)
add_custom_target(docker-load-arm-linux-gnueabihf          COMMAND tug -t mcandre/snek:arm-linux-gnueabihf          -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/arm-linux-gnueabihf)
add_custom_target(docker-load-arm64-apple-darwin           COMMAND tug -t mcandre/snek:arm64-apple-darwin           -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/arm64-apple-darwin)
add_custom_target(docker-load-arm64e-apple-darwin          COMMAND tug -t mcandre/snek:arm64e-apple-darwin          -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/arm64e-apple-darwin)
add_custom_target(docker-load-i686-pc-linux-gnu            COMMAND tug -t mcandre/snek:i686-pc-linux-gnu            -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/i686-pc-linux-gnu)
add_custom_target(docker-load-i686-w64-mingw32-posix       COMMAND tug -t mcandre/snek:i686-w64-mingw32-posix       -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/i686-w64-mingw32-posix)
add_custom_target(docker-load-i686-w64-mingw32-win32       COMMAND tug -t mcandre/snek:i686-w64-mingw32-win32       -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/i686-w64-mingw32-win32)
add_custom_target(docker-load-m68k-linux-gnu               COMMAND tug -t mcandre/snek:m68k-linux-gnu               -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/m68k-linux-gnu)
add_custom_target(docker-load-mips-linux-gnu               COMMAND tug -t mcandre/snek:mips-linux-gnu               -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/mips-linux-gnu)
add_custom_target(docker-load-mips64-linux-gnuabi64        COMMAND tug -t mcandre/snek:mips64-linux-gnuabi64        -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/mips64-linux-gnuabi64)
add_custom_target(docker-load-mips64el-linux-gnuabi64      COMMAND tug -t mcandre/snek:mips64el-linux-gnuabi64      -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/mips64el-linux-gnuabi64)
add_custom_target(docker-load-mipsel-linux-gnu             COMMAND tug -t mcandre/snek:mipsel-linux-gnu             -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/mipsel-linux-gnu)
add_custom_target(docker-load-mipsisa32r6-linux-gnu        COMMAND tug -t mcandre/snek:mipsisa32r6-linux-gnu        -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/mipsisa32r6-linux-gnu)
add_custom_target(docker-load-mipsisa32r6el-linux-gnu      COMMAND tug -t mcandre/snek:mipsisa32r6el-linux-gnu      -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/mipsisa32r6el-linux-gnu)
add_custom_target(docker-load-mipsisa64r6-linux-gnuabi64   COMMAND tug -t mcandre/snek:mipsisa64r6-linux-gnuabi64   -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/mipsisa64r6-linux-gnuabi64)
add_custom_target(docker-load-mipsisa64r6el-linux-gnuabi64 COMMAND tug -t mcandre/snek:mipsisa64r6el-linux-gnuabi64 -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/mipsisa64r6el-linux-gnuabi64)
add_custom_target(docker-load-powerpc-linux-gnu            COMMAND tug -t mcandre/snek:powerpc-linux-gnu            -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/powerpc-linux-gnu)
add_custom_target(docker-load-powerpc64-linux-gnu          COMMAND tug -t mcandre/snek:powerpc64-linux-gnu          -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/powerpc64-linux-gnu)
add_custom_target(docker-load-powerpc64le-linux-gnu        COMMAND tug -t mcandre/snek:powerpc64le-linux-gnu        -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/powerpc64le-linux-gnu)
add_custom_target(docker-load-riscv64-linux-gnu            COMMAND tug -t mcandre/snek:riscv64-linux-gnu            -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/riscv64-linux-gnu)
add_custom_target(docker-load-s390x-linux-gnu              COMMAND tug -t mcandre/snek:s390x-linux-gnu              -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/s390x-linux-gnu)
add_custom_target(docker-load-sparc64-linux-gnu            COMMAND tug -t mcandre/snek:sparc64-linux-gnu            -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/sparc64-linux-gnu)
add_custom_target(docker-load-x86_64-alpine-linux-musl     COMMAND tug -t mcandre/snek:x86_64-alpine-linux-musl     -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/x86_64-alpine-linux-musl)
add_custom_target(docker-load-x86_64-apple-darwin          COMMAND tug -t mcandre/snek:x86_64-apple-darwin          -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/x86_64-apple-darwin)
add_custom_target(docker-load-x86_64-linux-gnux32          COMMAND tug -t mcandre/snek:x86_64-linux-gnux32          -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/x86_64-linux-gnux32)
add_custom_target(docker-load-x86_64-pc-linux-gnu          COMMAND tug -t mcandre/snek:x86_64-pc-linux-gnu          -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/x86_64-pc-linux-gnu)
add_custom_target(docker-load-x86_64-unknown-freebsd       COMMAND tug -t mcandre/snek:x86_64-unknown-freebsd       -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/x86_64-unknown-freebsd)
add_custom_target(docker-load-x86_64-unknown-netbsd        COMMAND tug -t mcandre/snek:x86_64-unknown-netbsd        -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/x86_64-unknown-netbsd)
add_custom_target(docker-load-x86_64-unknown-openbsd       COMMAND tug -t mcandre/snek:x86_64-unknown-openbsd       -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/x86_64-unknown-openbsd)
add_custom_target(docker-load-x86_64-w64-mingw32-posix     COMMAND tug -t mcandre/snek:x86_64-w64-mingw32-posix     -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/x86_64-w64-mingw32-posix)
add_custom_target(docker-load-x86_64-w64-mingw32-win32     COMMAND tug -t mcandre/snek:x86_64-w64-mingw32-win32     -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/x86_64-w64-mingw32-win32)
add_custom_target(docker-load-x86_64h-apple-darwin         COMMAND tug -t mcandre/snek:x86_64h-apple-darwin         -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64 WORKING_DIRECTORY ../docker/x86_64h-apple-darwin)
add_custom_target(docker-load
                  DEPENDS
                  docker-load-aarch64-linux-gnu
                  docker-load-arm-linux-gnueabi
                  docker-load-arm-linux-gnueabihf
                #   docker-load-arm64-apple-darwin
                #   docker-load-arm64e-apple-darwin
                  docker-load-i686-pc-linux-gnu
                  docker-load-i686-w64-mingw32-posix
                  docker-load-i686-w64-mingw32-win32
                  docker-load-m68k-linux-gnu
                  docker-load-mips-linux-gnu
                  docker-load-mips64-linux-gnuabi64
                  docker-load-mips64el-linux-gnuabi64
                  docker-load-mipsel-linux-gnu
                  docker-load-mipsisa32r6-linux-gnu
                  docker-load-mipsisa32r6el-linux-gnu
                  docker-load-mipsisa64r6-linux-gnuabi64
                  docker-load-mipsisa64r6el-linux-gnuabi64
                  docker-load-powerpc-linux-gnu
                  docker-load-powerpc64-linux-gnu
                  docker-load-powerpc64le-linux-gnu
                  docker-load-riscv64-linux-gnu
                  docker-load-s390x-linux-gnu
                  docker-load-sparc64-linux-gnu
                  docker-load-x86_64-alpine-linux-musl
                #   docker-load-x86_64-apple-darwin
                  docker-load-x86_64-linux-gnux32
                  docker-load-x86_64-pc-linux-gnu
                  docker-load-x86_64-unknown-freebsd
                  docker-load-x86_64-unknown-netbsd
                  docker-load-x86_64-unknown-openbsd
                  docker-load-x86_64-w64-mingw32-posix
                  docker-load-x86_64-w64-mingw32-win32
                #   docker-load-x86_64h-apple-darwin
)

add_custom_target(docker-publish-aarch64-linux-gnu            COMMAND tug -t mcandre/snek:aarch64-linux-gnu            -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/aarch64-linux-gnu)
add_custom_target(docker-publish-arm-linux-gnueabi            COMMAND tug -t mcandre/snek:arm-linux-gnueabi            -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/arm-linux-gnueabi)
add_custom_target(docker-publish-arm-linux-gnueabihf          COMMAND tug -t mcandre/snek:arm-linux-gnueabihf          -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/arm-linux-gnueabihf)
add_custom_target(docker-publish-arm64-apple-darwin           COMMAND tug -t mcandre/snek:arm64-apple-darwin           -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/arm64-apple-darwin)
add_custom_target(docker-publish-arm64e-apple-darwin          COMMAND tug -t mcandre/snek:arm64e-apple-darwin          -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/arm64e-apple-darwin)
add_custom_target(docker-publish-i686-pc-linux-gnu            COMMAND tug -t mcandre/snek:i686-pc-linux-gnu            -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/i686-pc-linux-gnu)
add_custom_target(docker-publish-i686-w64-mingw32-posix       COMMAND tug -t mcandre/snek:i686-w64-mingw32-posix       -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/i686-w64-mingw32-posix)
add_custom_target(docker-publish-i686-w64-mingw32-win32       COMMAND tug -t mcandre/snek:i686-w64-mingw32-posix-win32 -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/i686-w64-mingw32-posix-win32)
add_custom_target(docker-publish-m68k-linux-gnu               COMMAND tug -t mcandre/snek:mips-linux-gnu               -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/mips-linux-gnu)
add_custom_target(docker-publish-mips-linux-gnu               COMMAND tug -t mcandre/snek:mips-linux-gnu               -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/mips-linux-gnu)
add_custom_target(docker-publish-mips64-linux-gnuabi64        COMMAND tug -t mcandre/snek:mips64-linux-gnuabi64        -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/mips64-linux-gnuabi64)
add_custom_target(docker-publish-mips64el-linux-gnuabi64      COMMAND tug -t mcandre/snek:mips64el-linux-gnuabi64      -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/mips64el-linux-gnuabi64)
add_custom_target(docker-publish-mipsel-linux-gnu             COMMAND tug -t mcandre/snek:mipsel-linux-gnu             -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/mipsel-linux-gnu)
add_custom_target(docker-publish-mipsisa32r6-linux-gnu        COMMAND tug -t mcandre/snek:mipsisa32r6-linux-gnu        -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/mipsisa32r6-linux-gnu)
add_custom_target(docker-publish-mipsisa32r6el-linux-gnu      COMMAND tug -t mcandre/snek:mipsisa32r6el-linux-gnu      -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/mipsisa32r6el-linux-gnu)
add_custom_target(docker-publish-mipsisa64r6-linux-gnuabi64   COMMAND tug -t mcandre/snek:mipsisa64r6-linux-gnuabi64   -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/mipsisa64r6-linux-gnuabi64)
add_custom_target(docker-publish-mipsisa64r6el-linux-gnuabi64 COMMAND tug -t mcandre/snek:mipsisa64r6el-linux-gnuabi64 -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/mipsisa64r6el-linux-gnuabi64)
add_custom_target(docker-publish-powerpc-linux-gnu            COMMAND tug -t mcandre/snek:powerpc-linux-gnu            -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/powerpc-linux-gnu)
add_custom_target(docker-publish-powerpc64-linux-gnu          COMMAND tug -t mcandre/snek:powerpc64-linux-gnu          -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/powerpc64-linux-gnu)
add_custom_target(docker-publish-powerpc64le-linux-gnu        COMMAND tug -t mcandre/snek:powerpc64le-linux-gnu        -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/powerpc64le-linux-gnu)
add_custom_target(docker-publish-riscv64-linux-gnu            COMMAND tug -t mcandre/snek:riscv64-linux-gnu            -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/riscv64-linux-gnu)
add_custom_target(docker-publish-s390x-linux-gnu              COMMAND tug -t mcandre/snek:s390x-linux-gnu              -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/s390x-linux-gnu)
add_custom_target(docker-publish-sparc64-linux-gnu            COMMAND tug -t mcandre/snek:sparc64-linux-gnu            -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/sparc64-linux-gnu)
add_custom_target(docker-publish-x86_64-alpine-linux-musl     COMMAND tug -t mcandre/snek:x86_64-alpine-linux-musl     -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/x86_64-alpine-linux-musl)
add_custom_target(docker-publish-x86_64-apple-darwin          COMMAND tug -t mcandre/snek:x86_64-apple-darwin          -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/x86_64-apple-darwin)
add_custom_target(docker-publish-x86_64-linux-gnux32          COMMAND tug -t mcandre/snek:x86_64-linux-gnux32          -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/x86_64-linux-gnux32)
add_custom_target(docker-publish-x86_64-pc-linux-gnu          COMMAND tug -t mcandre/snek:x86_64-pc-linux-gnu          -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/x86_64-pc-linux-gnu)
add_custom_target(docker-publish-x86_64-unknown-freebsd       COMMAND tug -t mcandre/snek:x86_64-unknown-freebsd       -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/x86_64-unknown-freebsd)
add_custom_target(docker-publish-x86_64-unknown-netbsd        COMMAND tug -t mcandre/snek:x86_64-unknown-netbsd        -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/x86_64-unknown-netbsd)
add_custom_target(docker-publish-x86_64-unknown-openbsd       COMMAND tug -t mcandre/snek:x86_64-unknown-openbsd       -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/x86_64-unknown-openbsd)
add_custom_target(docker-publish-x86_64-w64-mingw32-posix     COMMAND tug -t mcandre/snek:x86_64-w64-mingw32-posix     -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/x86_64-w64-mingw32-posix)
add_custom_target(docker-publish-x86_64-w64-mingw32-win32     COMMAND tug -t mcandre/snek:x86_64-w64-mingw32-win32     -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/x86_64-w64-mingw32-posix-win32)
add_custom_target(docker-publish-x86_64h-apple-darwin         COMMAND tug -t mcandre/snek:x86_64h-apple-darwin         -exclude-arch "${EXCLUDE_ARCH}" -push WORKING_DIRECTORY ../docker/x86_64h-apple-darwin)
add_custom_target(docker-publish
                  DEPENDS
                  docker-publish-aarch64-linux-gnu
                  docker-publish-arm-linux-gnueabi
                  docker-publish-arm-linux-gnueabihf
                  docker-publish-arm64-apple-darwin
                  docker-publish-arm64e-apple-darwin
                  docker-publish-i686-pc-linux-gnu
                  docker-publish-i686-w64-mingw32-posix
                  docker-publish-i686-w64-mingw32-win32
                  docker-publish-m68k-linux-gnu
                  docker-publish-mips-linux-gnu
                  docker-publish-mips64-linux-gnuabi64
                  docker-publish-mips64el-linux-gnuabi64
                  docker-publish-mipsel-linux-gnu
                  docker-publish-mipsisa32r6-linux-gnu
                  docker-publish-mipsisa32r6el-linux-gnu
                  docker-publish-mipsisa64r6-linux-gnuabi64
                  docker-publish-mipsisa64r6el-linux-gnuabi64
                  docker-publish-powerpc-linux-gnu
                  docker-publish-powerpc64-linux-gnu
                  docker-publish-powerpc64le-linux-gnu
                  docker-publish-riscv64-linux-gnu
                  docker-publish-s390x-linux-gnu
                  docker-publish-sparc64-linux-gnu
                  docker-publish-x86_64-alpine-linux-musl
                  docker-publish-x86_64-apple-darwin
                  docker-publish-x86_64-linux-gnux32
                  docker-publish-x86_64-pc-linux-gnu
                  docker-publish-x86_64-unknown-freebsd
                  docker-publish-x86_64-unknown-netbsd
                  docker-publish-x86_64-unknown-openbsd
                  docker-publish-x86_64-w64-mingw32-posix
                  docker-publish-x86_64-w64-mingw32-win32
                  docker-publish-x86_64h-apple-darwin
)

add_custom_target(docker-scout-aarch64-linux-gnu            COMMAND docker scout cves -e mcandre/snek:aarch64-linux-gnu            --platform linux/amd64)
add_custom_target(docker-scout-arm-linux-gnueabi            COMMAND docker scout cves -e mcandre/snek:arm-linux-gnueabi            --platform linux/amd64)
add_custom_target(docker-scout-arm-linux-gnueabihf          COMMAND docker scout cves -e mcandre/snek:arm-linux-gnueabihf          --platform linux/amd64)
add_custom_target(docker-scout-arm64-apple-darwin           COMMAND docker scout cves -e mcandre/snek:arm64-apple-darwin           --platform linux/amd64)
add_custom_target(docker-scout-arm64e-apple-darwin          COMMAND docker scout cves -e mcandre/snek:arm64e-apple-darwin          --platform linux/amd64)
add_custom_target(docker-scout-i686-pc-linux-gnu            COMMAND docker scout cves -e mcandre/snek:i686-pc-linux-gnu            --platform linux/amd64)
add_custom_target(docker-scout-i686-w64-mingw32-posix       COMMAND docker scout cves -e mcandre/snek:i686-w64-mingw32-posix       --platform linux/amd64)
add_custom_target(docker-scout-i686-w64-mingw32-win32       COMMAND docker scout cves -e mcandre/snek:i686-w64-mingw32-win32       --platform linux/amd64)
add_custom_target(docker-scout-m68k-linux-gnu               COMMAND docker scout cves -e mcandre/snek:m68k-linux-gnu               --platform linux/amd64)
add_custom_target(docker-scout-mips-linux-gnu               COMMAND docker scout cves -e mcandre/snek:mips-linux-gnu               --platform linux/amd64)
add_custom_target(docker-scout-mips64-linux-gnuabi64        COMMAND docker scout cves -e mcandre/snek:mips64-linux-gnuabi64        --platform linux/amd64)
add_custom_target(docker-scout-mips64el-linux-gnuabi64      COMMAND docker scout cves -e mcandre/snek:mips64el-linux-gnuabi64      --platform linux/amd64)
add_custom_target(docker-scout-mipsel-linux-gnu             COMMAND docker scout cves -e mcandre/snek:mipsel-linux-gnu             --platform linux/amd64)
add_custom_target(docker-scout-mipsisa32r6-linux-gnu        COMMAND docker scout cves -e mcandre/snek:mipsisa32r6-linux-gnu        --platform linux/amd64)
add_custom_target(docker-scout-mipsisa32r6el-linux-gnu      COMMAND docker scout cves -e mcandre/snek:mipsisa32r6el-linux-gnu      --platform linux/amd64)
add_custom_target(docker-scout-mipsisa64r6-linux-gnuabi64   COMMAND docker scout cves -e mcandre/snek:mipsisa64r6-linux-gnuabi64   --platform linux/amd64)
add_custom_target(docker-scout-mipsisa64r6el-linux-gnuabi64 COMMAND docker scout cves -e mcandre/snek:mipsisa64r6el-linux-gnuabi64 --platform linux/amd64)
add_custom_target(docker-scout-powerpc-linux-gnu            COMMAND docker scout cves -e mcandre/snek:powerpc-linux-gnu            --platform linux/amd64)
add_custom_target(docker-scout-powerpc64-linux-gnu          COMMAND docker scout cves -e mcandre/snek:powerpc64-linux-gnu          --platform linux/amd64)
add_custom_target(docker-scout-powerpc64le-linux-gnu        COMMAND docker scout cves -e mcandre/snek:powerpc64le-linux-gnu        --platform linux/amd64)
add_custom_target(docker-scout-riscv64-linux-gnu            COMMAND docker scout cves -e mcandre/snek:riscv64-linux-gnu            --platform linux/amd64)
add_custom_target(docker-scout-s390x-linux-gnu              COMMAND docker scout cves -e mcandre/snek:s390x-linux-gnu              --platform linux/amd64)
add_custom_target(docker-scout-sparc64-linux-gnu            COMMAND docker scout cves -e mcandre/snek:sparc64-linux-gnu            --platform linux/amd64)
add_custom_target(docker-scout-x86_64-alpine-linux-musl     COMMAND docker scout cves -e mcandre/snek:x86_64-alpine-linux-musl     --platform linux/amd64)
add_custom_target(docker-scout-x86_64-apple-darwin          COMMAND docker scout cves -e mcandre/snek:x86_64-apple-darwin          --platform linux/amd64)
add_custom_target(docker-scout-x86_64-linux-gnux32          COMMAND docker scout cves -e mcandre/snek:x86_64-linux-gnux32          --platform linux/amd64)
add_custom_target(docker-scout-x86_64-pc-linux-gnu          COMMAND docker scout cves -e mcandre/snek:x86_64-pc-linux-gnu          --platform linux/amd64)
add_custom_target(docker-scout-x86_64-unknown-freebsd       COMMAND docker scout cves -e mcandre/snek:x86_64-unknown-freebsd       --platform linux/amd64)
add_custom_target(docker-scout-x86_64-unknown-netbsd        COMMAND docker scout cves -e mcandre/snek:x86_64-unknown-netbsd        --platform linux/amd64)
add_custom_target(docker-scout-x86_64-unknown-openbsd       COMMAND docker scout cves -e mcandre/snek:x86_64-unknown-openbsd       --platform linux/amd64)
add_custom_target(docker-scout-x86_64-w64-mingw32-posix     COMMAND docker scout cves -e mcandre/snek:x86_64-w64-mingw32-posix     --platform linux/amd64)
add_custom_target(docker-scout-x86_64-w64-mingw32-win32     COMMAND docker scout cves -e mcandre/snek:x86_64-w64-mingw32-win32     --platform linux/amd64)
add_custom_target(docker-scout-x86_64h-apple-darwin         COMMAND docker scout cves -e mcandre/snek:x86_64h-apple-darwin         --platform linux/amd64)
add_custom_target(docker-scout
                  DEPENDS
                  docker-scout-aarch64-linux-gnu
                  docker-scout-arm-linux-gnueabi
                  docker-scout-arm-linux-gnueabihf
                  docker-scout-arm64-apple-darwin
                  docker-scout-arm64e-apple-darwin
                  docker-scout-i686-pc-linux-gnu
                  docker-scout-i686-w64-mingw32-posix
                  docker-scout-i686-w64-mingw32-win32
                  docker-scout-m68k-linux-gnu
                  docker-scout-mips-linux-gnu
                  docker-scout-mips64-linux-gnuabi64
                  docker-scout-mips64el-linux-gnuabi64
                  docker-scout-mipsel-linux-gnu
                  docker-scout-mipsisa32r6-linux-gnu
                  docker-scout-mipsisa32r6el-linux-gnu
                  docker-scout-mipsisa64r6-linux-gnuabi64
                  docker-scout-mipsisa64r6el-linux-gnuabi64
                  docker-scout-powerpc-linux-gnu
                  docker-scout-powerpc64-linux-gnu
                  docker-scout-powerpc64le-linux-gnu
                  docker-scout-riscv64-linux-gnu
                  docker-scout-s390x-linux-gnu
                  docker-scout-sparc64-linux-gnu
                  docker-scout-x86_64-alpine-linux-musl
                  docker-scout-x86_64-apple-darwin
                  docker-scout-x86_64-linux-gnux32
                  docker-scout-x86_64-pc-linux-gnu
                  docker-scout-x86_64-unknown-freebsd
                  docker-scout-x86_64-unknown-netbsd
                  docker-scout-x86_64-unknown-openbsd
                  docker-scout-x86_64-w64-mingw32-posix
                  docker-scout-x86_64-w64-mingw32-win32
                  docker-scout-x86_64h-apple-darwin
)

add_custom_target(safety COMMAND safety check)

add_custom_target(snyk COMMAND snyk test --unmanaged --trust-policies "${HOME}/.conan/data")

add_custom_target(audit DEPENDS docker-scout safety snyk)
