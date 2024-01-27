# BUILDTIME REQUIREMENTS

* GNU [awk](https://www.gnu.org/software/gawk/manual/gawk.html) 5+
* [clang](https://clang.llvm.org/) 14+ or [g++](https://gcc.gnu.org/) 12+
* [clang-format](https://clang.llvm.org/docs/ClangFormat.html)
* [clang-tidy](https://clang.llvm.org/extra/clang-tidy/)
* [cmake](https://cmake.org/) 3.5+
* [Docker](https://www.docker.com/) 20.10.12+
* [git](https://git-scm.com/) 2.39+
* [Go](https://go.dev/) 1.21.5+
* GNU [make](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/make.html) 3.81+
* [Node.js](https://www.npmjs.com/) 20.10.0+
* [Python](https://www.python.org/) 3.12.1+
* [Rust](https://www.rust-lang.org/en-US/) 1.68.2+
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
* [file](https://linux.die.net/man/1/file)
* [tree](https://linux.die.net/man/1/tree)
* POSIX compatible [tar](https://pubs.opengroup.org/onlinepubs/7908799/xcu/tar.html)
* a UNIX environment, such as macOS, Linux, BSD, [WSL](https://learn.microsoft.com/en-us/windows/wsl/), etc.

Non-UNIX environments may produce subtle adverse effects when linting or generating application ports.

# AUDIT

```console
$ make audit
```

# BUILD

```console
$ make [build]
```

# LOAD DOCKER IMAGES

```console
$ make docker-load
```

# PUBLISH DOCKER IMAGES

```console
$ make docker-publish
```

# INSTALL

```console
$ make install
```

# UNINSTALL

```console
$ make uninstall
```

# LINT

```console
$ make lint
```

# CLEAN

```console
$ make clean
```
