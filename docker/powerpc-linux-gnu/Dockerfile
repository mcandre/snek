FROM debian:bookworm-20240926-slim
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        cmake \
        g++-powerpc-linux-gnu \
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
ENV CXX="powerpc-linux-gnu-g++"
ENV CC="powerpc-linux-gnu-gcc"
ENV CPPFLAGS="-static"
ENV CPATH="/usr/powerpc-linux-gnu/include:/usr/local/powerpc-linux-gnu/usr/include"
WORKDIR /src
