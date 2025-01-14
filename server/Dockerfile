FROM ubuntu:24.04

RUN apt-get update && apt-get install -y net-tools procps


COPY build/clock  /clock
COPY build/server /main

ENTRYPOINT [ "/main" ]
