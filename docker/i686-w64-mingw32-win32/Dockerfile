FROM debian:12.4-slim
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        cmake \
        g++-mingw-w64-i686-win32 \
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
ENV CXX="i686-w64-mingw32-g++-win32"
ENV CC="i686-w64-mingw32-gcc-win32"
ENV CPPFLAGS="-static"
ENV SNEK_EXECUTABLE_FILE_EXTENSION=".exe"
WORKDIR /src
