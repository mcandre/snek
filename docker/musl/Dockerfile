FROM alpine:3.14
RUN apk add -U \
        build-base \
        clang && \
    ln -sf /usr/bin/clang++ /usr/bin/c++ && \
    ln -sf /usr/bin/clang /usr/bin/cc
WORKDIR /src
