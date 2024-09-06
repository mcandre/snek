FROM debian:12.4-slim
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        cmake \
        g++-s390x-linux-gnu \
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
ENV CXX="s390x-linux-gnu-g++"
ENV CC="s390x-linux-gnu-gcc"
ENV CPPFLAGS="-static"
ENV CPATH="/usr/s390x-linux-gnu/include:/usr/local/s390x-linux-gnu/usr/include"
WORKDIR /src
