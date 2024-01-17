# hello

# EXAMPLE

```console
$ hello
Hello World!
```

# REQUIREMENTS

* a [C](https://en.wikipedia.org/wiki/C_(programming_language)) compiler with C17 support (e.g. clang 9+, gcc 9+, MSVC 19+)
* [Docker](https://www.docker.com/) 20.10.12+
* [GNU make](https://www.gnu.org/software/make/) 3.81+
* POSIX compatible [sh](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/sh.html)
* [snek](https://github.com/mcandre/snek)

## Recommended

* POSIX compatible [tar](https://pubs.opengroup.org/onlinepubs/7908799/xcu/tar.html)
* a UNIX environment, such as macOS, Linux, BSD, [WSL](https://learn.microsoft.com/en-us/windows/wsl/), etc.

Non-UNIX environments may produce subtle adverse effects when linting or generating application ports.

# BUILD

```console
$ make
```

# PORT

```console
$ snek
$ sh -c "cd bin && tar czf hello-0.0.1.tgz hello-0.0.1"
```

# CLEAN

```console
$ make clean
```
