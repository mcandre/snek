FROM debian:12.4-slim
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        cmake \
        g++-x86-64-linux-gnux32 \
        gawk \
        git \
        make \
        python3-pip && \
    pip3 install --break-system-packages conan==1.62.0 && \
    rm -rf \
        /var/lib/apt/lists/* \
        /var/cache/apt/pkgcache.bin \
        /var/cache/apt/srcpkgcache.bin
ENV CXX="x86_64-linux-gnux32-g++"
ENV CC="x86_64-linux-gnux32-gcc"
ENV CPPFLAGS="-static"
ENV CPATH="/usr/x86_64-linux-gnux32/include:/usr/local/x86_64-linux-gnux32/usr/include"
WORKDIR /src
