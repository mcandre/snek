FROM ubuntu:20.04
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        build-essential \
        clang && \
    rm -rf /var/lib/apt/lists/* && \
    update-alternatives --set c++ /usr/bin/clang++ && \
    update-alternatives --set cc /usr/bin/clang
WORKDIR /src
