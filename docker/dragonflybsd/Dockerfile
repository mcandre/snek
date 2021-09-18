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
        xorriso
RUN wget http://mirror-master.dragonflybsd.org/iso-images/dfly-x86_64-6.0.0_REL.iso.bz2
RUN bunzip2 dfly-x86_64-6.0.0_REL.iso.bz2
RUN mkdir -p dfly-x86_64-6.0.0_REL && \
    osirrox -indev dfly-x86_64-6.0.0_REL.iso -extract / dfly-x86_64-6.0.0_REL
RUN mkdir -p /usr/local/x86_64-unknown-dragonflybsd && \
    cp -r dfly-x86_64-6.0.0_REL/usr/include /usr/local/x86_64-unknown-dragonflybsd/
RUN cp -r dfly-x86_64-6.0.0_REL/usr/lib /usr/local/x86_64-unknown-dragonflybsd/
# RUN apt-get remove --autoremove --purge -y \
#         bzip2 \
#         ca-certificates \
#         git \
#         wget \
#         xorriso && \
#     rm -rf \
#         dfly-x86_64-6.0.0_REL \
#         dfly-x86_64-6.0.0_REL.iso \
#         dfly-x86_64-6.0.0_REL.iso.bz2 \
#         /var/lib/apt/lists/* \
#         /var/cache/apt/pkgcache.bin \
#         /var/cache/apt/srcpkgcache.bin && \
#     update-alternatives --set c++ /usr/bin/clang++ && \
#     update-alternatives --set cc /usr/bin/clang
WORKDIR /src
