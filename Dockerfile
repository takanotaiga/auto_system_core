FROM ubuntu:jammy

SHELL ["/bin/bash", "-c"]
ENV DEBIAN_FRONTEND=noninteractive
ENV DEBCONF_NOWARNINGS=yes
ENV PATH="/root/.cargo/bin:${PATH}"

RUN apt update && apt install -y curl build-essential git vim clang llvm lld lldb cmake

RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y && \
    rustup install nightly-2025-02-16 && \
    cargo +nightly-2025-02-16 install --git https://github.com/facebook/buck2.git buck2

WORKDIR /root/workspace
