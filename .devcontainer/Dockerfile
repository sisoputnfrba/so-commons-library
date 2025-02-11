FROM docker.io/library/ubuntu:22.04

RUN apt-get update -y \
    && apt-get install make git valgrind gcc gdb libc6-dev -y --no-install-recommends \
    && git config --global --add safe.directory /workspaces/so-commons-library \
    && git config --global --add safe.directory /workspaces/so-commons-library/cspec

WORKDIR /workspaces/so-commons-library

CMD [ "/bin/bash" ]
