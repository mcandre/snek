FROM voidlinux/voidlinux-musl
RUN xbps-install -uSy \
        base-devel \
        clang \
        cross-aarch64-linux-musl \
        cross-arm-linux-musleabi \
        cross-arm-linux-musleabihf \
        cross-armv7l-linux-musleabihf \
        cross-i686-linux-musl \
        cross-mips-linux-musl \
        cross-mips-linux-muslhf \
        cross-mipsel-linux-musl \
        cross-mipsel-linux-muslhf \
        cross-powerpc-linux-musl \
        cross-powerpc64-linux-musl \
        cross-powerpc64le-linux-musl \
        cross-powerpcle-linux-musl \
        llvm && \
    ln -sf /usr/sbin/clang++ /usr/sbin/c++ && \
    ln -sf /usr/sbin/clang /usr/sbin/cc
WORKDIR /src
