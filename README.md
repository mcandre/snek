# snek: the toolchain armada

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

snek simplifies the process of porting software to multiple platforms.

_VM's are slow. snek is fast._

_Hardware is expensive. snek is free._

# EXAMPLE

```console
$ cd example

$ tree bin
bin
├── aarch64-linux-gnu
│   └── hello
├── aarch64-linux-musl
│   └── hello
├── arm-linux-gnueabi
│   └── hello
├── arm-linux-gnueabihf
│   └── hello
├── arm-linux-musleabi
│   └── hello
├── arm-linux-musleabihf
│   └── hello
├── armv7l-linux-musleabihf
│   └── hello
├── i386-apple-darwin
│   └── hello
├── i686-linux-musl
│   └── hello
├── i686-pc-linux-gnu
│   └── hello
├── i686-pc-windows-gnu
│   └── hello.exe
├── mips-linux-gnu
│   └── hello
├── mips-linux-musl
│   └── hello
├── mips-linux-muslhf
│   └── hello
├── mips64-linux-gnuabi64
│   └── hello
├── mips64el-linux-gnuabi64
│   └── hello
├── mipsel-linux-gnu
│   └── hello
├── powerpc-linux-gnu
│   └── hello
├── powerpc-linux-musl
│   └── hello
├── powerpc64-linux-gnu
│   └── hello
├── powerpc64-linux-musl
│   └── hello
├── powerpc64le-linux-gnu
│   └── hello
├── powerpc64le-linux-musl
│   └── hello
├── powerpcle-linux-musl
│   └── hello
├── riscv64-linux-gnu
│   └── hello
├── s390x-linux-gnu
│   └── hello
├── sparc64-linux-gnu
│   └── hello
├── x86_64-alpine-linux-musl
│   └── hello
├── x86_64-apple-darwin
│   └── hello
├── x86_64-pc-linux-gnu
│   └── hello
├── x86_64-pc-windows-gnu
│   └── hello.exe
├── x86_64-unknown-linux-musl
│   └── hello
└── x86_64h-apple-darwin
    └── hello
```

# CONFIGURATION

snek offers several preconfigured toolchain ships, or you can specify your own custom ships. See [example/snek.yaml](example/snek.yaml) for more detail.

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

# SEE ALSO

* [factorio](https://github.com/mcandre/factorio) ports Go applications
* [multiarch/crossbuild](https://hub.docker.com/r/multiarch/crossbuild) hosts Darwin images
* [tonixxx](https://github.com/mcandre/tonixxx) ports applications via Virtual Machines
* [trust](https://github.com/japaric/trust) ports Rust applications
* [xgo](https://github.com/karalabe/xgo) ports cgo applications
