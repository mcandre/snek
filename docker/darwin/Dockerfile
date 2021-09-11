FROM ubuntu:20.04
ENV PATH /usr/local/osxcross/target/bin:${PATH}
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        build-essential \
        ca-certificates \
        clang \
        cmake \
        file \
        git \
        libgmp-dev \
        libmpc-dev \
        libmpfr-dev \
        libssl-dev \
        libxml2-dev \
        lzma-dev \
        ninja-build \
        python \
        python3 \
        unzip \
        wget \
        zlib1g-dev && \
    update-alternatives --set c++ /usr/bin/clang++ && \
    update-alternatives --set cc /usr/bin/clang && \
    git clone https://github.com/apple/llvm-project.git && \
    git clone https://github.com/tpoechtrager/osxcross.git /usr/local/osxcross && \
    wget -O /usr/local/osxcross/tarballs/MacOSX11.3.sdk.tar.xz https://github.com/phracker/MacOSX-SDKs/releases/download/11.3/MacOSX11.3.sdk.tar.xz && \
    echo 'cd4f08a75577145b8f05245a2975f7c81401d75e9535dcffbb879ee1deefcbf4  /usr/local/osxcross/tarballs/MacOSX11.3.sdk.tar.xz' | shasum -c && \
    cd /llvm-project && \
    cmake \
        -S ./llvm \
        -B build \
        -G Ninja \
        -DLLVM_ENABLE_PROJECTS="clang;libcxx;libcxxabi;lld" \
        -DCMAKE_BUILD_TYPE=Release \
        -DLLVM_INCLUDE_EXAMPLES=OFF \
        -DLLVM_INCLUDE_TESTS=OFF \
        -DLLVM_INCLUDE_BENCHMARKS=OFF \
        -DLLVM_ENABLE_LIBPFM=OFF \
        -DLLVM_ENABLE_DIA_SDK=OFF && \
    cmake --build build && \
    cmake --install build --prefix /usr/local/apple-clang && \
    cd / && \
    rm -rf /llvm-project && \
    update-alternatives --install /usr/bin/c++ c++ /usr/local/apple-clang/bin/clang++ 100 && \
    update-alternatives --install /usr/bin/cc cc /usr/local/apple-clang/bin/clang 100 && \
    update-alternatives --set c++ /usr/local/apple-clang/bin/clang++ && \
    update-alternatives --set cc /usr/local/apple-clang/bin/clang && \
    cd /usr/local/osxcross && \
	UNATTENDED=1 ./build.sh && \
    cd / && \
    apt-get remove --autoremove --purge -y \
        ca-certificates \
        cmake \
        file \
        git \
        libgmp-dev \
        libmpc-dev \
        libmpfr-dev \
        libssl-dev \
        libxml2-dev \
        lzma-dev \
        ninja-build \
        python \
        python3 \
        unzip \
        wget \
        zlib1g-dev && \
    rm -rf /var/lib/apt/lists/* \
        /var/cache/apt/pkgcache.bin \
        /var/cache/apt/srcpkgcache.bin
WORKDIR /src
