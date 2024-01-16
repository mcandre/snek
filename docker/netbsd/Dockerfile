FROM debian:12.4
ENV DEBIAN_FRONTEND=noninteractive
ENV SYSROOT=/usr/local/x86_64-unknown-netbsd
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        ca-certificates \
        clang \
        cmake \
        cppcheck \
        llvm \
        make \
        wget \
        xz-utils && \
    wget https://cdn.netbsd.org/pub/NetBSD/NetBSD-9.3/amd64/binary/sets/base.tar.xz && \
    wget https://cdn.netbsd.org/pub/NetBSD/NetBSD-9.3/amd64/binary/sets/comp.tar.xz && \
    wget https://cdn.netbsd.org/pub/pkgsrc/packages/NetBSD/x86_64/9.3/All/libunwind-16.0.6.tgz && \
    wget https://cdn.netbsd.org/pub/pkgsrc/packages/NetBSD/x86_64/9.3/All/libcxxabi-16.0.6.tgz && \
    wget https://cdn.netbsd.org/pub/pkgsrc/packages/NetBSD/x86_64/9.3/All/libcxx-16.0.6.tgz && \
    mkdir /usr/local/x86_64-unknown-netbsd && \
    cd /usr/local/x86_64-unknown-netbsd && \
    tar -xvf /base.tar.xz ./lib/ ./usr/lib/ ./usr/include/ && \
    tar -xvf /comp.tar.xz ./usr/lib/ ./usr/include/ && \
    tar -xvf /libunwind-16.0.6.tgz include/ lib/ && \
    tar -xvf /libcxxabi-16.0.6.tgz lib/ && \
    tar -xvf /libcxx-16.0.6.tgz include/ lib/ && \
    rm -f \
        /libcxx-16.0.6.tgz \
        /libcxxabi-16.0.6.tgz \
        /libunwind-16.0.6.tgz \
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
