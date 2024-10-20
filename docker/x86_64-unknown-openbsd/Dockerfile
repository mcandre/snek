FROM debian:bookworm-20240926-slim
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
    wget https://cloudflare.cdn.openbsd.org/pub/OpenBSD/7.4/amd64/base74.tgz && \
    wget https://cloudflare.cdn.openbsd.org/pub/OpenBSD/7.4/amd64/comp74.tgz && \
    mkdir /usr/local/x86_64-unknown-openbsd && \
    cd /usr/local/x86_64-unknown-openbsd && \
    tar -xzvf /base74.tgz ./usr/include/ ./usr/lib/ && \
    tar -xzvf /comp74.tgz ./usr/include/ ./usr/lib/ && \
    rm -f \
        /comp74.tgz \
        /base74.tgz && \
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
ENV CPPFLAGS="--sysroot /usr/local/x86_64-unknown-openbsd -target x86_64-unknown-openbsd-pthread"
ENV CPATH="/usr/x86_64-unknown-openbsd/include:/usr/local/x86_64-unknown-openbsd/usr/include"
WORKDIR /src
