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

$ snek

$ tree bin
bin
├── hello-0.0.1
│   ├── aarch64-linux-gnu
│   │   └── hello
│   ├── arm-linux-gnueabi
│   │   └── hello
│   ├── arm-linux-gnueabihf
│   │   └── hello
│   ├── arm64-apple-darwin
│   │   └── hello
...
```

# LICENSE

BSD-2-Clause

# RUNTIME REQUIREMENTS

* [Docker](https://www.docker.com/) 20.10.12+

## Recommended

* a host capable of running musl/Linux containers (e.g. a GNU/Linux, musl/Linux, macOS, or Windows host)
* [Docker First Aid Kit](https://github.com/mcandre/docker-first-aid-kit)
* Apply `DOCKER_DEFAULT_PLATFORM` = `linux/amd64` environment variable
* [cmake](https://cmake.org/) 3.5+
* [make](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/make.html) or [ninja](https://ninja-build.org/)
* [file](https://linux.die.net/man/1/file)
* [tree](https://linux.die.net/man/1/tree)
* [tug](https://github.com/mcandre/tug)
* POSIX compatible [tar](https://pubs.opengroup.org/onlinepubs/7908799/xcu/tar.html)
* a UNIX environment, such as macOS, Linux, BSD, [WSL](https://learn.microsoft.com/en-us/windows/wsl/), etc.

Non-UNIX environments may produce subtle adverse effects when linting or generating application ports.

# CONTRIBUTING

For more information on developing snek itself, see [DEVELOPMENT.md](DEVELOPMENT.md).

# CONFIGURATION

snek offers several preconfigured toolchain Docker ships, or you can specify your own custom ships.

snek automatically mounts the host current working directory as a guest `/src` directory.

## Standard Ships

snek curates a set of standard Docker image ships for easy porting of cmake/make projects to common POSIX-esque target environments. These are primarily [clang](https://clang.llvm.org/) / [gcc](https://gcc.gnu.org/) based, in order to support a wide variety of environments and C/C++ language features.

The standard images automatically set the guest working directory to `/src`.

The standard images aim to reduce their footprint, in order to keep the snek system fairly lean and fast on mediumish hardware. For example, snek may be run on a cheap laptop, or a beefy workstation, or an expensive CI/CD instance, or on a RAM-appropraite Raspberry Pi with sufficient patience.

The total size of the image collection is only bounded by your build host's disk space.

The Docker images for your ships are extensible and customizable. See [example/snek.yaml](example/snek.yaml) for more detail.

# CREDITS

* [chroot](https://en.wikipedia.org/wiki/Chroot) can assist with isolating compiler toolchains on UNIX hosts
* [crit](https://github.com/mcandre/crit) ports Rust applications
* [distcc](https://distcc.github.io/) can distribute compilations to remote servers
* [factorio](https://github.com/mcandre/factorio) ports Go applications
* [LLVM](https://llvm.org/) bitcode offers an abstract assembler format for C/C++ code.
* [osxcross](https://github.com/tpoechtrager/osxcross) provides patches to enable Darwin targets.
* [tug](https://github.com/mcandre/tug) automates multi-platform Docker image builds.
* [WASM](https://webassembly.org/) provides a portable interface for C/C++ code.
* [xgo](https://github.com/crazy-max/xgo) ports cgo applications
