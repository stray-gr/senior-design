FROM ubuntu:24.04

RUN apt-get update && apt-get install -y iputils-ping iproute2 procps


COPY build/clock  /clock
COPY build/server /main

ENTRYPOINT [ "/main" ]
