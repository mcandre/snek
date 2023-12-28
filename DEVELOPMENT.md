# BUILDTIME REQUIREMENTS

* a [C++](https://www.cplusplus.com/) compiler with C++17 support (e.g. clang 9+, g++ 9+, MSVC 19+)
* [cmake](https://cmake.org/) 3.4+
* [rez](https://github.com/mcandre/rez) 0.0.11
* a POSIX compliant [make](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/make.html) implementation (e.g. GNU make, BSD make, etc.)
* [Docker](https://www.docker.com/) 20.10.12+
* [Go](https://go.dev/) 1.21.5+
* [Node.js](https://www.npmjs.com/) 20.10.0+
* [Python](https://www.python.org/) 3.12.1+
* [Rust](https://www.rust-lang.org/en-US/) 1.68.2+
* a POSIX compliant [sh](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/sh.html) implementation (e.g. bash, ksh, zsh)
* [sail](https://github.com/mcandre/sail) 0.0.1
* Provision additional dev tools with `make -f install.mk`

## Recommended

* [ASDF](https://asdf-vm.com/) 0.10 (run `asdf reshim` after provisioning)
* [direnv](https://direnv.net/) 2
* [clang](https://clang.llvm.org/) (UNIX) or [MSVC](https://gist.github.com/mcandre/5ceb67ad44f6b974d33bcddedcb16e89) (Windows)
* [clang-format](https://clang.llvm.org/docs/ClangFormat.html)
* [clang-tidy](https://clang.llvm.org/extra/clang-tidy/)
* [ninja](https://ninja-build.org/) 1.11.1+
* [file](https://linux.die.net/man/1/file)
* [tree](https://linux.die.net/man/1/tree)

macOS users may need additional patches:

* [Grow](https://github.com/mcandre/dotfiles/blob/master/.profile.d/xcode.sh) Xcode PATH

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
$ rez load
```

# PUBLISH SNEK DOCKER IMAGES

```console
$ rez publish
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
