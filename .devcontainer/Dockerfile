# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.245.2/containers/ubuntu/.devcontainer/base.Dockerfile

# [Choice] Ubuntu version (use ubuntu-22.04 or ubuntu-18.04 on local arm64/Apple Silicon): ubuntu-22.04, ubuntu-20.04, ubuntu-18.04
ARG VARIANT="jammy"
FROM mcr.microsoft.com/vscode/devcontainers/base:0-${VARIANT}

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
    build-essential \
    cmake \
    ninja-build \
    tig \
    valgrind

RUN wget "https://launchpad.net/~ubuntu-toolchain-r/+archive/ubuntu/ppa/+build/23606523/+files/gdb_12.1-0ubuntu1~22.04_$(dpkg --print-architecture).deb" \
    && apt-get install -y ./gdb_12.1-0ubuntu1~22.04_$(dpkg --print-architecture).deb \
    && rm ./gdb_12.1-0ubuntu1~22.04_$(dpkg --print-architecture).deb

RUN echo "alias g='git'" >> /etc/bash.bashrc
