FROM debian:12.4-slim
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        cmake \
        g++-riscv64-linux-gnu \
        gawk \
        git \
        make \
        python3-pip && \
    pip3 install --break-system-packages conan==1.62.0 && \
    rm -rf \
        /var/lib/apt/lists/* \
        /var/cache/apt/pkgcache.bin \
        /var/cache/apt/srcpkgcache.bin
ENV CXX="riscv64-linux-gnu-g++"
ENV CC="riscv64-linux-gnu-gcc"
ENV CPPFLAGS="-static"
ENV CPATH="/usr/riscv64-linux-gnu/include:/usr/local/riscv64-linux-gnu/usr/include"
WORKDIR /src
