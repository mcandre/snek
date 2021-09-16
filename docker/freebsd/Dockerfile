FROM ubuntu:20.04
ENV DEBIAN_FRONTEND=noninteractive
ENV SYSROOT=/usr/local/x86_64-unknown-freebsd13
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        ca-certificates \
        clang \
        cmake \
        llvm \
        make \
        perl \
        wget \
        xz-utils && \
    wget http://ftp.plusline.de/FreeBSD/releases/amd64/13.0-RELEASE/base.txz && \
    echo 'be7ab3c21ca650b3763ad3605edd18c39d570abd40b0aad3058df64c3e38fb51  base.txz' | shasum -c && \
    mkdir /usr/local/x86_64-unknown-freebsd13 && \
    cd /usr/local/x86_64-unknown-freebsd13 && \
    tar -xvf /base.txz ./lib/ ./usr/lib/ ./usr/include/ && \
    rm -f /base.txz && \
    cd usr/lib && \
    find . -xtype l | \
        xargs ls -l | \
        awk '{ system("ln -sf /usr/local/x86_64-unknown-freebsd13" $11 " " $9) }' && \
    apt-get remove --autoremove --purge -y \
        ca-certificates \
        perl \
        wget \
        xz-utils && \
    rm -rf \
        /var/lib/apt/lists/* \
        /var/cache/apt/pkgcache.bin \
        /var/cache/apt/srcpkgcache.bin && \
    update-alternatives --set c++ /usr/bin/clang++ && \
    update-alternatives --set cc /usr/bin/clang
WORKDIR /src
