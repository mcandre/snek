FROM debian:12.4-slim
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        cmake \
        g++-mips-linux-gnu \
        gawk \
        git \
        make \
        python3-pip && \
    pip3 install --break-system-packages conan==1.62.0 && \
    rm -rf \
        /var/lib/apt/lists/* \
        /var/cache/apt/pkgcache.bin \
        /var/cache/apt/srcpkgcache.bin
ENV CXX "mips-linux-gnu-g++"
ENV CC "mips-linux-gnu-gcc"
ENV CPPFLAGS "-static"
ENV CPATH "/usr/mips-linux-gnu/include:/usr/local/mips-linux-gnu/usr/include"
WORKDIR /src
