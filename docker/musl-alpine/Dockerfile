FROM alpine:3.15
RUN apk add -U \
        build-base \
        clang \
        cmake \
        llvm \
        make && \
    ln -sf /usr/bin/clang++ /usr/bin/c++ && \
    ln -sf /usr/bin/clang /usr/bin/cc
WORKDIR /src
