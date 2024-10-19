FROM debian:bookworm-20240926-slim
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        cmake \
        g++-mingw-w64-x86-64-posix \
        gawk \
        git \
        make \
        python3-pip && \
    pip3 install --break-system-packages conan==1.62.0 && \
    rm -rf \
        /var/lib/apt/lists/* \
        /var/cache/apt/pkgcache.bin \
        /var/cache/apt/srcpkgcache.bin
COPY profile.ini /
ENV CXX="x86_64-w64-mingw32-g++-posix"
ENV CC="x86_64-w64-mingw32-gcc-posix"
ENV CPPFLAGS="-static"
ENV SNEK_EXECUTABLE_FILE_EXTENSION=".exe"
WORKDIR /src
