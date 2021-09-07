# BUILDTIME REQUIREMENTS

* a [C++](https://www.cplusplus.com/) compiler with C++17 support
* [cmake](https://cmake.org/) 3.4+
* [conan](https://conan.io/) 1.40+
* [Docker](https://www.docker.com/) 19+

## Recommended

* [clang](https://clang.llvm.org/) (UNIX) or [MSVC](https://gist.github.com/mcandre/5ceb67ad44f6b974d33bcddedcb16e89) (Windows)
* [clang-format](https://clang.llvm.org/docs/ClangFormat.html) (UNIX)
* [clang-tidy](https://clang.llvm.org/extra/clang-tidy/) (UNIX)
* [file](https://linux.die.net/man/1/file)
* [llvm](https://llvm.org/) (UNIX)
* [tree](https://linux.die.net/man/1/tree)

macOS users may need additional patches:

* [Grow](https://github.com/mcandre/dotfiles/blob/master/.profile.d/xcode.sh) Xcode PATH

# INSTALL DEPENDENCIES

## macOS

```console
$ conan install -s compiler.cppstd=17 -s compiler=apple-clang -s compiler.version=12.0 --build missing .
```

## UNIX (clang)

```console
$ conan install -s compiler.cppstd=17 -s compiler=clang -s compiler.version=10 --build missing .
```

## UNIX (gcc)

```console
$ conan install -s compiler.cppstd=17 -s compiler=gcc -s compiler.version=9 --build missing .
```

## Windows

```console
$ conan install -s compiler.cppstd=17 -s compiler=msvc -s compiler.version=19.28 -s compiler.runtime=dynamic --build missing .
```

# BUILD

```console
$ cmake .
$ cmake --build . --config Release
```

# INSTALL

```console
$ cmake --build . --target install
```

# UNINSTALL

```console
$ cmake --build . --target uninstall
```

# LINT

```console
$ cmake --build . --target lint
```

# CLEAN

```console
$ ./clean.sh
```
