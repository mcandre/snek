FROM debian:12.9-slim
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        cmake \
        g++-arm-linux-gnueabihf \
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
ENV CXX="arm-linux-gnueabihf-g++"
ENV CC="arm-linux-gnueabihf-gcc"
ENV CPPFLAGS="-static"
ENV CPATH="/usr/arm-linux-gnueabihf/include:/usr/local/arm-linux-gnueabihf/usr/include"
WORKDIR /src
