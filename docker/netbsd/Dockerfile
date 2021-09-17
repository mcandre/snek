FROM ubuntu:20.04
ENV DEBIAN_FRONTEND=noninteractive
ENV SYSROOT=/usr/local/x86_64-unknown-netbsd
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        ca-certificates \
        clang \
        cmake \
        llvm \
        make \
        wget \
        xz-utils && \
    wget https://cdn.netbsd.org/pub/NetBSD/NetBSD-9.2/amd64/binary/sets/base.tar.xz && \
    wget https://cdn.netbsd.org/pub/NetBSD/NetBSD-9.2/amd64/binary/sets/comp.tar.xz && \
    mkdir /usr/local/x86_64-unknown-netbsd && \
    cd /usr/local/x86_64-unknown-netbsd && \
    tar -xvf /base.tar.xz ./lib/ ./usr/lib/ ./usr/include/ && \
    tar -xvf /comp.tar.xz ./usr/lib/ ./usr/include/ && \
    rm -f /comp.tar.xz && \
    rm -f /base.tar.xz && \
    apt-get remove --autoremove --purge -y \
        ca-certificates \
        wget \
        xz-utils && \
    rm -rf \
        /var/lib/apt/lists/* \
        /var/cache/apt/pkgcache.bin \
        /var/cache/apt/srcpkgcache.bin && \
    update-alternatives --set c++ /usr/bin/clang++ && \
    update-alternatives --set cc /usr/bin/clang
WORKDIR /src
