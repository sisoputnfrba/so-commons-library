FROM docker.io/library/ubuntu:22.04

ARG CSPEC_VERSION=396445c217b366fd3a41c33a38e9a8dd75c3f0e5

RUN apt-get update -y \
    && apt-get install make git valgrind gcc gdb libc6-dev -y --no-install-recommends \
    && git config --global --add safe.directory /workspaces/so-commons-library \
    && git config --global --add safe.directory /workspaces/so-commons-library/cspec

WORKDIR /workspaces

ADD https://github.com/mumuki/cspec/archive/${CSPEC_VERSION}.tar.gz cspec.tar.gz

RUN tar -xzf cspec.tar.gz \
    && rm cspec.tar.gz \
    && make -C cspec-${CSPEC_VERSION} install \
    && rm -rf cspec

WORKDIR /workspaces/so-commons-library

CMD [ "/bin/bash" ]
