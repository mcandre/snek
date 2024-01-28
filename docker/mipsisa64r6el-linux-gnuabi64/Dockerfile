FROM debian:12.4-slim
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        clang \
        clang-tidy \
        cmake \
        g++-mipsisa64r6el-linux-gnuabi64 \
        gawk \
        git \
        llvm \
        make \
        python3-pip && \
    pip3 install --break-system-packages conan==1.62.0 && \
    rm -rf \
        /var/lib/apt/lists/* \
        /var/cache/apt/pkgcache.bin \
        /var/cache/apt/srcpkgcache.bin && \
    update-alternatives --set c++ /usr/bin/clang++ && \
    update-alternatives --set cc /usr/bin/clang
ENV CPPFLAGS "-static -target mipsisa64r6el-linux-gnuabi64"
ENV CPATH "/usr/mipsisa64r6el-linux-gnuabi64/include:/usr/local/mipsisa64r6el-linux-gnuabi64/usr/include"
WORKDIR /src
