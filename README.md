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

# RUNTIME REQUIREMENTS

* [Docker](https://www.docker.com/) 19+

## Recommended

* [file](https://linux.die.net/man/1/file)
* [tree](https://linux.die.net/man/1/tree)

# CONTRIBUTING

For more information on developing snek itself, see [DEVELOPMENT.md](DEVELOPMENT.md).

# SEE ALSO

* [factorio](https://github.com/mcandre/factorio) ports Go applications
* [multiarch/crossbuild](https://hub.docker.com/r/multiarch/crossbuild) hosts Darwin images
* [tonixxx](https://github.com/mcandre/tonixxx) ports applications via Virtual Machines
* [trust](https://github.com/japaric/trust) ports Rust applications
* [xgo](https://github.com/karalabe/xgo) ports cgo applications
