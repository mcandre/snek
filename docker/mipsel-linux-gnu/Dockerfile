FROM debian:12.9-slim
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        cmake \
        g++-mipsel-linux-gnu \
        gawk \
        git \
        make \
        python3-pip && \
    pip3 install --break-system-packages conan==1.62.0 && \
    rm -rf \
        /var/lib/apt/lists/* \
        /var/cache/apt/pkgcache.bin \
        /var/cache/apt/srcpkgcache.bin
ENV CXX="mipsel-linux-gnu-g++"
ENV CC="mipsel-linux-gnu-gcc"
ENV CPPFLAGS="-static"
ENV CPATH="/usr/mipsel-linux-gnu/include:/usr/local/mipsel-linux-gnu/usr/include"
WORKDIR /src
