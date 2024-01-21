FROM debian:12.4
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        cmake \
        g++ \
        gawk \
        git \
        llvm \
        make \
        mingw-w64 \
        python3-pip && \
    pip3 install --break-system-packages conan==1.62.0 && \
    rm -rf \
        /var/lib/apt/lists/* \
        /var/cache/apt/pkgcache.bin \
        /var/cache/apt/srcpkgcache.bin
WORKDIR /src
