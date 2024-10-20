FROM debian:bookworm-20240926-slim
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        cmake \
        g++-m68k-linux-gnu \
        gawk \
        git \
        make \
        python3-pip && \
    pip3 install --break-system-packages conan==1.62.0 && \
    rm -rf \
        /var/lib/apt/lists/* \
        /var/cache/apt/pkgcache.bin \
        /var/cache/apt/srcpkgcache.bin
ENV CXX="m68k-linux-gnu-g++"
ENV CC="m68k-linux-gnu-gcc"
ENV CPATH="/usr/m68k-linux-gnu/include:/usr/local/m68k-linux-gnu/usr/include"
WORKDIR /src
