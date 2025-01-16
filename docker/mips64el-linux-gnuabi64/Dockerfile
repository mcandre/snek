FROM debian:12.9-slim
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        cmake \
        g++-mips64el-linux-gnuabi64 \
        gawk \
        git \
        make \
        python3-pip && \
    pip3 install --break-system-packages conan==1.62.0 && \
    rm -rf \
        /var/lib/apt/lists/* \
        /var/cache/apt/pkgcache.bin \
        /var/cache/apt/srcpkgcache.bin
ENV CXX="mips64el-linux-gnuabi64-g++"
ENV CC="mips64el-linux-gnuabi64-gcc"
ENV CPPFLAGS="-static"
ENV CPATH="/usr/mips64el-linux-gnuabi64/include:/usr/local/mips64el-linux-gnuabi64/usr/include"
WORKDIR /src
