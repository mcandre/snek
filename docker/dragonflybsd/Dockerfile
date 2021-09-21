FROM ubuntu:20.04
ENV DEBIAN_FRONTEND=noninteractive
ENV SYSROOT=/usr/local/x86_64-unknown-dragonflybsd
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        bzip2 \
        ca-certificates \
        clang \
        cmake \
        git \
        llvm \
        make \
        wget \
        xorriso && \
    wget http://mirror-master.dragonflybsd.org/iso-images/dfly-x86_64-6.0.0_REL.iso.bz2 && \
    bunzip2 dfly-x86_64-6.0.0_REL.iso.bz2 && \
    mkdir -p dfly-x86_64-6.0.0_REL && \
    osirrox \
        -indev dfly-x86_64-6.0.0_REL.iso \
        -extract / \
        dfly-x86_64-6.0.0_REL
RUN mkdir -p /usr/local/x86_64-unknown-dragonflybsd/usr/local && \
    cp -r \
        dfly-x86_64-6.0.0_REL/lib \
        /usr/local/x86_64-unknown-dragonflybsd/ && \
    cp -r \
        dfly-x86_64-6.0.0_REL/libexec \
        /usr/local/x86_64-unknown-dragonflybsd/ && \
    cp -r \
        dfly-x86_64-6.0.0_REL/usr/include \
        /usr/local/x86_64-unknown-dragonflybsd/usr/ && \
    cp -r \
        dfly-x86_64-6.0.0_REL/usr/lib \
        /usr/local/x86_64-unknown-dragonflybsd/usr/ && \
    cp -r \
        dfly-x86_64-6.0.0_REL/usr/libdata \
        /usr/local/x86_64-unknown-dragonflybsd/usr/ && \
    cp -r \
        dfly-x86_64-6.0.0_REL/usr/libexec \
        /usr/local/x86_64-unknown-dragonflybsd/usr/ && \
    cp -r \
        dfly-x86_64-6.0.0_REL/usr/local/libdata \
        /usr/local/x86_64-unknown-dragonflybsd/usr/local/ && \
    cp -r \
        dfly-x86_64-6.0.0_REL/usr/local/libexec \
        /usr/local/x86_64-unknown-dragonflybsd/usr/local/ && \
    apt-get remove --autoremove --purge -y \
        bzip2 \
        ca-certificates \
        git \
        wget \
        xorriso && \
    rm -rf \
        dfly-x86_64-6.0.0_REL \
        dfly-x86_64-6.0.0_REL.iso \
        dfly-x86_64-6.0.0_REL.iso.bz2 \
        /var/lib/apt/lists/* \
        /var/cache/apt/pkgcache.bin \
        /var/cache/apt/srcpkgcache.bin && \
    update-alternatives --set c++ /usr/bin/clang++ && \
    update-alternatives --set cc /usr/bin/clang

RUN apt-get update && \
    apt-get install -y \
        wget \
        xz-utils
RUN wget https://avalon.dragonflybsd.org/dports/dragonfly:6.2:x86:64/LATEST/All/cxxfs_gcc8-8.0.txz
RUN cd /usr/local/x86_64-unknown-dragonflybsd && \
    tar -xvf /cxxfs_gcc8-8.0.txz /usr/local/cxxfs_gcc8/ && \
    apt-get remove --autoremove --purge -y \
        wget \
        xz-utils && \
    rm -f \
        /cxxfs_gcc8-8.0.txz
WORKDIR /src
