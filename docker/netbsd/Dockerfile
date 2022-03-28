FROM debian:bookworm
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
    wget https://cdn.netbsd.org/pub/pkgsrc/packages/NetBSD/x86_64/9.2/All/libunwind-13.0.0.tgz && \
    wget https://cdn.netbsd.org/pub/pkgsrc/packages/NetBSD/x86_64/9.2/All/libcxxabi-13.0.0.tgz && \
    wget https://cdn.netbsd.org/pub/pkgsrc/packages/NetBSD/x86_64/9.2/All/libcxx-13.0.0.tgz && \
    mkdir /usr/local/x86_64-unknown-netbsd && \
    cd /usr/local/x86_64-unknown-netbsd && \
    tar -xvf /base.tar.xz ./lib/ ./usr/lib/ ./usr/include/ && \
    tar -xvf /comp.tar.xz ./usr/lib/ ./usr/include/ && \
    tar -xvf /libunwind-13.0.0.tgz include/ lib/ && \
    tar -xvf /libcxxabi-13.0.0.tgz lib/ && \
    tar -xvf /libcxx-13.0.0.tgz include/ lib/ && \
    rm -f \
        /libcxx-13.0.0.tgz \
        /libcxxabi-13.0.0.tgz \
        /libunwind-13.0.0.tgz \
        /comp.tar.xz \
        /base.tar.xz && \
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
