FROM debian:12.4-slim
ENV PATH /usr/local/osxcross/bin:${PATH}
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        ca-certificates \
        clang \
        clang-tidy \
        cmake \
        file \
        gawk \
        git \
        libgmp-dev \
        libmpc-dev \
        libmpfr-dev \
        libssl-dev \
        libxml2-dev \
        llvm \
        lzma-dev \
        make \
        ninja-build \
        patch \
        python3-pip \
        wget \
        xz-utils \
        zlib1g-dev && \
    pip3 install --break-system-packages conan==1.62.0 && \
    git clone https://github.com/tpoechtrager/osxcross.git && \
    wget -O osxcross/tarballs/MacOSX11.3.sdk.tar.xz https://github.com/phracker/MacOSX-SDKs/releases/download/11.3/MacOSX11.3.sdk.tar.xz && \
    cd osxcross && \
    echo 'cd4f08a75577145b8f05245a2975f7c81401d75e9535dcffbb879ee1deefcbf4  tarballs/MacOSX11.3.sdk.tar.xz' | shasum -c && \
    mkdir -p /usr/local/osxcross && \
	env TARGET_DIR=/usr/local/osxcross UNATTENDED=1 ./build.sh && \
    cd / && \
    rm -rf osxcross && \
    apt-get remove --autoremove --purge -y \
        ca-certificates \
        file \
        libgmp-dev \
        libmpc-dev \
        libmpfr-dev \
        libssl-dev \
        lzma-dev \
        ninja-build \
        patch \
        wget \
        xz-utils \
        zlib1g-dev && \
    rm -rf /var/lib/apt/lists/* \
        /var/cache/apt/pkgcache.bin \
        /var/cache/apt/srcpkgcache.bin
ENV CXX "arm64e-apple-darwin20.4-clang++"
ENV CC "arm64e-apple-darwin20.4-clang"
ENV CROSSBUILD "arm64e-apple-darwin"
ENV CPPFLAGS "-mmacosx-version-min=10.15"
WORKDIR /src
