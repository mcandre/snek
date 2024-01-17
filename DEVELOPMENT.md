# BUILDTIME REQUIREMENTS

* a [C++](https://www.cplusplus.com/) compiler with C++17 support (e.g. clang 9+, g++ 9+, MSVC 19+)
* [clang-format](https://clang.llvm.org/docs/ClangFormat.html)
* [clang-tidy](https://clang.llvm.org/extra/clang-tidy/)
* [cmake](https://cmake.org/) 3.5+
* [Docker](https://www.docker.com/) 20.10.12+
* GNU or BSD [findutils](https://en.wikipedia.org/wiki/Find_(Unix))
* [Go](https://go.dev/) 1.21.5+
* POSIX compatible [make](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/make.html)
* [Node.js](https://www.npmjs.com/) 20.10.0+
* [Python](https://www.python.org/) 3.12.1+
* [rez](https://github.com/mcandre/rez) 0.0.15
* [Rust](https://www.rust-lang.org/en-US/) 1.68.2+
* POSIX compatible [sh](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/sh.html)
* Provision additional dev tools with `make -f install.mk`

## Recommended

* a host capable of running musl/Linux containers (e.g. a GNU/Linux, musl/Linux, macOS, or Windows host)
* [Docker First Aid Kit](https://github.com/mcandre/docker-first-aid-kit)
* Apply `DOCKER_DEFAULT_PLATFORM` = `linux/amd64` environment variable
* [ASDF](https://asdf-vm.com/) 0.10 (run `asdf reshim` after provisioning)
* [direnv](https://direnv.net/) 2
* [clang](https://clang.llvm.org/) (UNIX) or [MSVC](https://gist.github.com/mcandre/5ceb67ad44f6b974d33bcddedcb16e89) (Windows)
* [clang-format](https://clang.llvm.org/docs/ClangFormat.html)
* [clang-tidy](https://clang.llvm.org/extra/clang-tidy/)
* [ninja](https://ninja-build.org/) 1.11.1+
* [file](https://linux.die.net/man/1/file)
* [tree](https://linux.die.net/man/1/tree)
* POSIX compatible [tar](https://pubs.opengroup.org/onlinepubs/7908799/xcu/tar.html)
* a UNIX environment, such as macOS, Linux, BSD, [WSL](https://learn.microsoft.com/en-us/windows/wsl/), etc.

Non-UNIX environments may produce subtle adverse effects when linting or generating application ports.

# INSTALL DEPENDENCIES

## macOS

```console
$ conan install -s compiler.cppstd=17 -s compiler=apple-clang -s compiler.version=<version> --build missing . --install-folder build
```

## UNIX (clang)

```console
$ conan install -s compiler.cppstd=17 -s compiler=clang -s compiler.version=<version> --build missing . --install-folder build
```

## UNIX (gcc)

```console
$ conan install -s compiler.cppstd=17 -s compiler=gcc -s compiler.version=<version> --build missing . --install-folder build
```

## Windows

```console
$ conan install -s compiler.cppstd=17 -s compiler=msvc -s compiler.version=<version> -s compiler.runtime=dynamic --build missing . --install-folder build
```

# AUDIT

```console
$ rez audit
```

# BUILD SNEK

```console
$ rez build
```

# BUILD SNEK DOCKER IMAGES

```console
$ rez docker-build
```

# LOAD SNEK DOCKER IMAGES

```console
$ rez docker-load
```

# PUBLISH SNEK DOCKER IMAGES

```console
$ rez docker-publish
```

# INSTALL

```console
$ rez [install]
```

# UNINSTALL

```console
$ rez uninstall
```

# LINT

```console
$ rez lint
```

# CLEAN

```console
$ rez clean
```
