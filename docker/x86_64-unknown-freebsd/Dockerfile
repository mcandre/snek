FROM debian:12.4-slim
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
    wget https://download.freebsd.org/ftp/releases/amd64/14.0-RELEASE/base.txz && \
    mkdir /usr/local/x86_64-unknown-freebsd && \
    cd /usr/local/x86_64-unknown-freebsd && \
    tar -xvf /base.txz ./lib/ ./usr/lib/ ./usr/include/ && \
    rm -f /base.txz && \
    cd usr/lib && \
    find . -xtype l -print0 | \
        xargs -0 ls -l | \
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
ENV CPPFLAGS "-static --sysroot /usr/local/x86_64-unknown-freebsd -target x86_64-unknown-freebsd"
ENV CXXFLAGS "-stdlib=libc++"
ENV CPATH "/usr/x86_64-unknown-freebsd/include:/usr/local/x86_64-unknown-freebsd/usr/include"
WORKDIR /src
