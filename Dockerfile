FROM gcc:9.2 as build

COPY . /usr/src/app

WORKDIR /usr/src/app

RUN apt-get update &&\
  apt-get -y upgrade &&\
  apt-get -y install libglib2.0-dev &&\
  apt-get -y clean

RUN make



FROM ubuntu:xenial

RUN apt-get update &&\
  apt-get -y upgrade &&\
  apt-get -y install libglib2.0 &&\
  apt-get -y clean

WORKDIR /home/app

COPY --from=build /usr/src/app/bin/matrix /usr/bin/matrix

USER daemon

CMD [ "matrix" ]
