FROM alpine:3.20
RUN apk add -U \
        build-base \
        clang \
        clang-extra-tools \
        cmake \
        gawk \
        git \
        llvm \
        make \
        py3-pip && \
    ln -sf /usr/bin/clang++ /usr/bin/c++ && \
    ln -sf /usr/bin/clang /usr/bin/cc && \
    pip3 install --break-system-packages conan==1.62.0
COPY profile.ini /
ENV CPPFLAGS="-static -target x86_64-alpine-linux-musl"
ENV CPATH="/usr/x86_64-alpine-linux-musl/include:/usr/local/x86_64-alpine-linux-musl/usr/include"
WORKDIR /src
