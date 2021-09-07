# snek: a cross-compiler system

```text
                ~.
         Ya...___|__..ab.     .   .
          Y88b  \88b  \88b   (     )
           Y88b  :88b  :88b   `.xx'
           :888  |888  |888  ( (`{#}
  .---.    d88P  ;88P  ;88P   `.`.
 / .-._)  d8P-"""|"""'-Y8P      `.`.
( (`._) .-.  .-. |.-.  .-.  .-.   ) )
 \ `---( O )( O )( O )( O )( O )-' /
  `.    `-'  `-'  `-'  `-'  `-'  .'
    `---------------------------'
```

# SUMMARY

snek streamlines the process of cross-platform software builds. Enjoy preconfigured toolchains for common targets.

# EXAMPLE

```console
$ cd example

$ snek

bin
├── aarch64-linux-gnu
│   └── hello
├── arm-linux-gnueabi
│   └── hello
├── arm-linux-gnueabihf
│   └── hello
├── i686-pc-linux-gnu
│   └── hello
├── mips-linux-gnu
│   └── hello
├── mips64-linux-gnuabi64
│   └── hello
├── mips64el-linux-gnuabi64
│   └── hello
├── mipsel-linux-gnu
│   └── hello
├── x86_64-alpine-linux-musl
│   └── hello
└── x86_64-pc-linux-gnu
    └── hello
```

# LICENSE

FreeBSD

# REQUIREMENTS

* a [C++](https://www.cplusplus.com/) compiler with C++17 support
* [cmake](https://cmake.org/) 3.4+
* [conan](https://conan.io/) 1.40+
* [Docker](https://www.docker.com/) 19+

## Recommended

* [clang](https://clang.llvm.org/) (UNIX) or [MSVC](https://gist.github.com/mcandre/5ceb67ad44f6b974d33bcddedcb16e89) (Windows)
* [clang-format](https://clang.llvm.org/docs/ClangFormat.html) (UNIX)
* [clang-tidy](https://clang.llvm.org/extra/clang-tidy/) (UNIX)
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
