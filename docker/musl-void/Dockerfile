FROM voidlinux/voidlinux-musl
RUN xbps-install -uSy \
        base-devel \
        clang \
        llvm && \
    ln -sf /usr/sbin/clang++ /usr/sbin/c++ && \
    ln -sf /usr/sbin/clang /usr/sbin/cc
WORKDIR /src
