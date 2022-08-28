FROM gcc:11.2.0

RUN apt-get update && apt-get -y install cmake

WORKDIR /usr/src/so-commons-library

COPY . ./

RUN make install

CMD [ "/bin/sh" ]
