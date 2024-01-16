FROM debian:12.4
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        clang \
        cmake \
        cppcheck \
        g++-aarch64-linux-gnu \
        g++-alpha-linux-gnu \
        g++-arm-linux-gnueabi \
        g++-arm-linux-gnueabihf \
        g++-m68k-linux-gnu \
        g++-mips-linux-gnu \
        g++-mips64-linux-gnuabi64 \
        g++-mips64el-linux-gnuabi64 \
        g++-mipsel-linux-gnu \
        g++-powerpc-linux-gnu \
        g++-powerpc64-linux-gnu \
        g++-powerpc64le-linux-gnu \
        g++-riscv64-linux-gnu \
        g++-s390x-linux-gnu \
        g++-sh4-linux-gnu \
        g++-sparc64-linux-gnu \
        llvm \
        make && \
    rm -rf \
        /var/lib/apt/lists/* \
        /var/cache/apt/pkgcache.bin \
        /var/cache/apt/srcpkgcache.bin && \
    update-alternatives --set c++ /usr/bin/clang++ && \
    update-alternatives --set cc /usr/bin/clang
WORKDIR /src
