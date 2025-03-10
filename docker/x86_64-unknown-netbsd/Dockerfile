FROM debian:12.8-slim
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        ca-certificates \
        clang \
        clang-tidy \
        cmake \
        gawk \
        git \
        llvm \
        make \
        python3-pip \
        wget \
        xz-utils && \
    pip3 install --break-system-packages conan==1.62.0 && \
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
ENV CPPFLAGS="-static --sysroot /usr/local/x86_64-unknown-netbsd -target x86_64-unknown-netbsd"
ENV CXXFLAGS="-stdlib=libc++"
ENV CPATH="/usr/x86_64-unknown-netbsd/include:/usr/local/x86_64-unknown-netbsd/usr/include"
WORKDIR /src
