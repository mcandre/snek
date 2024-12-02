FROM debian:bookworm-20240926-slim
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        cmake \
        g++-x86-64-linux-gnu \
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
ENV CXX="x86_64-linux-gnu-g++"
ENV CC="x86_64-linux-gnu-gcc"
ENV CPPFLAGS="-static"
ENV CPATH="/usr/x86_64-pc-linux-gnu/include:/usr/local/x86_64-pc-linux-gnu/usr/include"
WORKDIR /src
