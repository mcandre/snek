FROM debian:12.4-slim
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        cmake \
        g++-arm-linux-gnueabi \
        gawk \
        git \
        make \
        python3-pip && \
    pip3 install --break-system-packages conan==1.62.0 && \
    rm -rf \
        /var/lib/apt/lists/* \
        /var/cache/apt/pkgcache.bin \
        /var/cache/apt/srcpkgcache.bin
COPY profile.ini /
ENV CXX="arm-linux-gnueabi-g++"
ENV CC="arm-linux-gnueabi-gcc"
ENV CPPFLAGS="-static"
ENV CPATH="/usr/arm-linux-gnueabi/include:/usr/local/arm-linux-gnueabi/usr/include"
WORKDIR /src
