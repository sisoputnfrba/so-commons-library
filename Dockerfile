FROM gcc:11.2.0

WORKDIR /usr/src/so-commons-library

RUN git clone https://github.com/mumuki/cspec \
    && cd cspec \
    && git reset --hard 396445c217b366fd3a41c33a38e9a8dd75c3f0e5 \
    && apt-get update -y \
    && apt-get install valgrind -y

COPY . ./

RUN make install

CMD [ "/bin/bash" ]
