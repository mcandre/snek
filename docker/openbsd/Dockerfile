FROM ubuntu:20.04
ENV DEBIAN_FRONTEND=noninteractive
ENV SYSROOT=/usr/local/x86_64-unknown-openbsd
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        ca-certificates \
        clang \
        cmake \
        llvm \
        make \
        wget \
        xz-utils && \
    wget https://cloudflare.cdn.openbsd.org/pub/OpenBSD/6.9/amd64/base69.tgz && \
    wget https://cloudflare.cdn.openbsd.org/pub/OpenBSD/6.9/amd64/comp69.tgz && \
    mkdir /usr/local/x86_64-unknown-openbsd && \
    cd /usr/local/x86_64-unknown-openbsd && \
    tar -xzvf /base69.tgz ./usr/include/ ./usr/lib/ && \
    tar -xzvf /comp69.tgz ./usr/include/ ./usr/lib/ && \
    rm -f \
        /comp69.tgz \
        /base69.tgz && \
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
