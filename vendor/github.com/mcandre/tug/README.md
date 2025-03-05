# tug: Multi-platform Docker rescue ship

![logo](tug.png)

# ABOUT

tug streamlines Docker pipelines.

Spend less time managing buildx images. Enjoy more time developing your core application.

# EXAMPLE

```console
$ cd example

$ tug -t mcandre/tug-demo

$ tug -ls mcandre/tug-demo
Platform:  linux/386
Platform:  linux/amd64
Platform:  linux/amd64/v2
...

$ tug -t mcandre/tug-demo -load linux/amd64

$ docker run --rm mcandre/tug-demo cat /banner
Hello World!
```

# MOTIVATION

buildx is hard. tug is easy.

When Docker introduced the buildx subsystem, their goals included making buildx operationally successful. But not necessarily as straightforward, consistent, and intuitive as single-platform `docker` commands. (Assuming that you consider Docker *straightforward, consistent, and intuitive*, ha.) We have run extensive drills on what buildx has to offer, and wrapped this into a neat little package called tug.

We are not replacing buildx, we just provide a proven workflow for high level buildx operation. We hope tug helps you to jumpstart multi-platform projects and even learn some fundamental buildx commands along the way.

You can see more Docker gears turning, apply the `tug -debug` flag. tug respects your time, but also rewards curiosity.

# DOCUMENTATION

https://pkg.go.dev/github.com/mcandre/tug

# DOWNLOAD

https://github.com/mcandre/tug/releases

# INSTALL FROM SOURCE

```console
$ go install github.com/mcandre/tug/cmd/tug@latest
```

# LICENSE

BSD-2-Clause

# RUNTIME REQUIREMENTS

* [Docker](https://www.docker.com/) 27+

## Recommended

* [Docker First Aid Kit](https://github.com/mcandre/docker-first-aid-kit)
* Apply `DOCKER_DEFAULT_PLATFORM` = `linux/amd64` environment variable

Regardless of target application environment, we encourage an amd64 compatible build environment. This tends to improve build reliability.

In time, we may revisit this recommendation. For now, an amd64 compatible host affords better chances for successful cross-compilation than trying, for example, to build `mips64` targets from `s390x` hosts.

# CONTRIBUTING

For more information on developing tug itself, see [DEVELOPMENT.md](DEVELOPMENT.md).

# USAGE

`tug -get-platforms` lists available platforms.

`tug -ls <name>` lists cached buildx entries, for the given image name (format `name[:tag]`). Note that this lookup targets primarily remotely pushed images.

`tug -t <name>` builds multi-platform images with the given image name (format `name[:tag]`). This is the essential tug build command.

`tug -clean` cleans up after junk resources, including the buildx image cache and the tug buildx builder.

Notable options:

* `-debug` enables additional logging.
* `-exclude-os <list>` rejects image operating systems from builds. The list is comma delimited.
* `-exclude-arch <list>` rejects image architectures from builds. The list is comma delimited.
* `-load <os/arch>` copies an image of the given platform from the buildx cache to the local Docker registry as a side effect of the build. By default, multi-platform do not appear in the main local image cache. Mainly useful to prepare quick `docker run`... tests of `linux/amd64` platform images.
* `-push` uploads buildx cached images to the remote Docker registry, as a side effect of the build. Normally, multi-platform images cannot be pushed from the main local cache, because most platforms do not support loading into the main local cache.
* `.` or `<directory>` are optional trailing arguments for the Docker build directory. We default to the current working directory.

See `tug -help` for more options.

# FAQ

## How do I get started?

Practice basic, single-platform [Docker](https://www.docker.com/). As you gain confidence with Docker, you can extend this work into the realm of multi-platform images.

See the [example](example/) project, which can be built with plain `docker`, or with `docker buildx`, or with `tug`.

Apply the `tug -debug`... option to see more commands. Follow the basic, low level [buildx documentation](https://docs.docker.com/buildx/working-with-buildx/). For a more advanced illustration, see how the [snek](https://github.com/mcandre/snek) project builds its Docker images.

## Unsupported platform?

Depends on your particular base image. Each base image on Docker Hub, for example, is a little platform snowflake. A base image usually supports some smaller subset of the universe of platform combinations. When in doubt, grow your `-exclude-arch` list and retry the build.

## tug-in-docker?

Running tug itself within a Docker context, such as for CI/CD, would naturally require Docker-in-Docker privileges. See the relevant documentation for your particular cluster environment, such as Kubernetes.

# DOCKER HUB COMMUNITY

[Docker Hub](https://hub.docker.com/) provides an exceptional variety of base images, everything from Debian to Ubuntu to RHEL to glibc to musl to uClibC. If your base image lacks support for a particular platform, try searching for alternative base images. Or, build a new base image from scratch and publish it back to Docker Hub! The more we refine our base images, the easier it is to extend and use them.

# SEE ALSO

* [crit](https://github.com/mcandre/crit) generates Rust ports
* [factorio](https://github.com/mcandre/factorio) ports Go applications
* [gox](https://github.com/mitchellh/gox), an older Go cross-compiler wrapper
* [LLVM](https://llvm.org/) bitcode offers an abstract assembler format for C/C++ code
* [snek](https://github.com/mcandre/snek) ports native C/C++ applications
* [tonixxx](https://github.com/mcandre/tonixxx) ports applications of any programming language
* [WASM](https://webassembly.org/) provides a portable interface for C/C++ code
* [xgo](https://github.com/techknowlogick/xgo) supports Go projects with native cgo dependencies
