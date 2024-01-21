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

if(DEFINED ENV{TARGET})
    set(STATIC_FLAG -static)

    if(DEFINED ENV{TARGET} AND "$ENV{TARGET}" MATCHES "w64")
        set(CMAKE_CXX_COMPILER "$ENV{TARGET}-g++-posix")
        set(CMAKE_C_COMPILER "$ENV{TARGET}-gcc-posix")
        set(ARTIFACT_EXT .exe)
    elseif("$ENV{TARGET}" MATCHES "darwin")
        set(CMAKE_CXX_COMPILER "$ENV{TARGET}20.4-clang++")
        set(CMAKE_C_COMPILER "$ENV{TARGET}20.4-clang")
        set(CROSSBUILD "$ENV{TARGET}")
        set(CPPFLAGS "-mmacosx-version-min=10.15")
        set(STATIC_FLAG)
    else()
        if("$ENV{TARGET}" MATCHES "bsd")
            set(CMAKE_SYSROOT "/usr/local/$ENV{TARGET}")

            if("$ENV{TARGET}" MATCHES "openbsd")
                set(CPPFLAGS "${CPPFLAGS} -pthread")
                set(STATIC_FLAG)
            else()
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
            endif()
        endif()

        set(CMAKE_CXX_COMPILER_TARGET "$ENV{TARGET}")
        set(CMAKE_C_COMPILER_TARGET "$ENV{TARGET}")
        include_directories("/usr/local/$ENV{TARGET}/include/c++/v1")
        include_directories("/usr/$ENV{TARGET}/include/c++/9/$ENV{TARGET}")
        include_directories("/usr/local/$ENV{TARGET}/usr/include/c++/v1")
        include_directories("/usr/$ENV{TARGET}/include")
        include_directories("/usr/local/$ENV{TARGET}/usr/include")

        if(NOT "$ENV{TARGET}" MATCHES "openbsd")
            include_directories("/usr/local/$ENV{TARGET}/usr/include/g++")
        endif()
    endif()

    set(EXECUTABLE_OUTPUT_PATH "../bin/${BANNER}/$ENV{TARGET}")
    set(CPPFLAGS "${CPPFLAGS} ${STATIC_FLAG}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CPPFLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CPPFLAGS}")
endif()

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
        set(CMAKE_CXX_CLANG_TIDY clang-tidy -header-filter=${CMAKE_SOURCE_DIR})
        set(CMAKE_C_CLANG_TIDY clang-tidy -header-filter=${CMAKE_SOURCE_DIR})
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

add_custom_target(docker-scout-darwin
                  COMMAND docker scout cves -e mcandre/snek:darwin --platform linux/amd64
)
add_custom_target(docker-scout-freebsd
                  COMMAND docker scout cves -e mcandre/snek:freebsd --platform linux/amd64
)
add_custom_target(docker-scout-mingw
                  COMMAND docker scout cves -e mcandre/snek:mingw --platform linux/amd64
)
add_custom_target(docker-scout-musl-alpine
                  COMMAND docker scout cves -e mcandre/snek:musl-alpine --platform linux/amd64
)
add_custom_target(docker-scout-netbsd
                  COMMAND docker scout cves -e mcandre/snek:netbsd --platform linux/amd64
)
add_custom_target(docker-scout-openbsd
                  COMMAND docker scout cves -e mcandre/snek:openbsd --platform linux/amd64
)
add_custom_target(docker-scout-other
                  COMMAND docker scout cves -e mcandre/snek:other --platform linux/amd64
)
add_custom_target(docker-scout-x86
                  COMMAND docker scout cves -e mcandre/snek:x86 --platform linux/amd64
)
add_custom_target(docker-scout
                  DEPENDS
                  docker-scout-darwin
                  docker-scout-freebsd
                  docker-scout-mingw
                  docker-scout-musl-alpine
                  docker-scout-netbsd
                  docker-scout-openbsd
                  docker-scout-other
                  docker-scout-x86
)

add_custom_target(safety COMMAND safety check)

add_custom_target(snyk COMMAND snyk test --unmanaged --trust-policies "${HOME}/.conan/data")

add_custom_target(audit DEPENDS docker-scout safety snyk)

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
add_custom_target(docker-build-mingw
                  COMMAND tug -t mcandre/snek:mingw -exclude-arch "${EXCLUDE_ARCH}"
                  WORKING_DIRECTORY ../docker/mingw
)
add_custom_target(docker-build-other
                  COMMAND tug -t mcandre/snek:other -exclude-arch "${EXCLUDE_ARCH}"
                  WORKING_DIRECTORY ../docker/other
)
add_custom_target(docker-build-x86
                  COMMAND tug -t mcandre/snek:x86 -exclude-arch "${EXCLUDE_ARCH}"
                  WORKING_DIRECTORY ../docker/x86
)

add_custom_target(docker-build
                  DEPENDS
                  docker-build-darwin
                  docker-build-freebsd
                  docker-build-musl-alpine
                  docker-build-netbsd
                  docker-build-openbsd
                  docker-build-mingw
                  docker-build-other
                  docker-build-x86
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
add_custom_target(docker-load-mingw
                  COMMAND tug -t mcandre/snek:mingw -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64
                  WORKING_DIRECTORY ../docker/mingw
)
add_custom_target(docker-load-other
                  COMMAND tug -t mcandre/snek:other -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64
                  WORKING_DIRECTORY ../docker/other
)
add_custom_target(docker-load-x86
                  COMMAND tug -t mcandre/snek:x86 -exclude-arch "${EXCLUDE_ARCH}" -load linux/amd64
                  WORKING_DIRECTORY ../docker/x86
)

add_custom_target(docker-load
                  DEPENDS
                  docker-load-darwin
                  docker-load-freebsd
                  docker-load-musl-alpine
                  docker-load-netbsd
                  docker-load-openbsd
                  docker-load-mingw
                  docker-load-other
                  docker-load-x86
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
add_custom_target(docker-publish-mingw
                  COMMAND tug -t mcandre/snek:mingw -exclude-arch "${EXCLUDE_ARCH}" -push
                  WORKING_DIRECTORY ../docker/mingw
)
add_custom_target(docker-publish-other
                  COMMAND tug -t mcandre/snek:other -exclude-arch "${EXCLUDE_ARCH}" -push
                  WORKING_DIRECTORY ../docker/other
)
add_custom_target(docker-publish-x86
                  COMMAND tug -t mcandre/snek:x86 -exclude-arch "${EXCLUDE_ARCH}" -push
                  WORKING_DIRECTORY ../docker/x86
)

add_custom_target(docker-publish
                  DEPENDS
                  docker-publish-darwin
                  docker-publish-freebsd
                  docker-publish-musl-alpine
                  docker-publish-netbsd
                  docker-publish-openbsd
                  docker-publish-mingw
                  docker-publish-other
                  docker-publish-x86
)
