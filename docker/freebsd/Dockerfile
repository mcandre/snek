FROM debian:12.4
ENV DEBIAN_FRONTEND=noninteractive
ENV SYSROOT=/usr/local/x86_64-unknown-freebsd
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        awk \
        ca-certificates \
        clang \
        cmake \
        llvm \
        make \
        wget \
        xz-utils && \
    wget https://download.freebsd.org/ftp/releases/amd64/13.0-RELEASE/base.txz && \
    mkdir /usr/local/x86_64-unknown-freebsd && \
    cd /usr/local/x86_64-unknown-freebsd && \
    tar -xvf /base.txz ./lib/ ./usr/lib/ ./usr/include/ && \
    rm -f /base.txz && \
    cd usr/lib && \
    find . -xtype l | \
        xargs ls -l | \
        awk '{ system("ln -sf /usr/local/x86_64-unknown-freebsd" $11 " " $9) }' && \
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
