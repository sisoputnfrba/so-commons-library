FROM ubuntu:16.04
RUN apt-get update && apt-get install -y aptitude gcc gdb git vim libncurses5 valgrind tig make autotools-dev strace emacs nano libcunit1 libevent1-dev ssh libfuse-dev build-essential g++ libcunit1-dev curl htop tree wget libreadline6 libreadline6-dev
WORKDIR /usr/src/so-commons-library
COPY . .
RUN make clean && make
CMD [ "make", "test" ]