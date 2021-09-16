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
├── arm-linux-gnueabi
│   └── hello
├── arm-linux-gnueabihf
│   └── hello
├── arm64-apple-darwin
│   └── hello
├── arm64e-apple-darwin
│   └── hello
├── i686-pc-linux-gnu
│   └── hello
├── i686-w64-mingw32
│   └── hello.exe
├── mips-linux-gnu
│   └── hello
├── mips64-linux-gnuabi64
│   └── hello
├── mips64el-linux-gnuabi64
│   └── hello
├── mipsel-linux-gnu
│   └── hello
├── powerpc-linux-gnu
│   └── hello
├── powerpc64-linux-gnu
│   └── hello
├── powerpc64le-linux-gnu
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
├── x86_64-w64-mingw32
│   └── hello.exe
└── x86_64h-apple-darwin
    └── hello
```

# LICENSE

FreeBSD

# RUNTIME REQUIREMENTS

* [Docker](https://www.docker.com/) 19+

## Recommended

* [file](https://linux.die.net/man/1/file)
* [tree](https://linux.die.net/man/1/tree)

# CONTRIBUTING

For more information on developing snek itself, see [DEVELOPMENT.md](DEVELOPMENT.md).

# CONFIGURATION

snek offers several preconfigured toolchain Docker ships, or you can specify your own custom ships.

snek automatically mounts the host current working directory as a guest `/src` directory.

## Standard Ships

snek curates a set of standard Docker image ships for easy porting of cmake/make projects to common POSIX-esque target environments. These are primarily [clang](https://clang.llvm.org/) / [gcc](https://gcc.gnu.org/) based, in order to support a wide variety of environments and C/C++ language features.

The standard images automatically set the guest working directory to `/src`.

The standard images are restricted in size (<4GB), in order to keep the snek system fairly lean and fast on mediumish hardware. For example, snek may be run on a cheap laptop, or a beefy workstation, or an expensive CI/CD instance, or on a RAM-appropraite Raspberry Pi with sufficient patience.

The total size of the image collection is only bounded by your build host's disk space.

The Docker images for your ships are extensible and customizable. See [example/snek.yaml](example/snek.yaml) for more detail.

# SEE ALSO

* [factorio](https://github.com/mcandre/factorio) ports Go applications
* [LLVM](https://llvm.org/) bitcode offers an abstract assembler format for C/C++ code.
* [osxcross](https://github.com/tpoechtrager/osxcross) provides patches to enable Darwin targets.
* [tonixxx](https://github.com/mcandre/tonixxx) ports applications via Virtual Machines
* [trust](https://github.com/japaric/trust) ports Rust applications
* [WASM](https://webassembly.org/) provides a portable interface for C/C++ code.
* [xgo](https://github.com/karalabe/xgo) ports cgo applications
