FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y procps
COPY main-bin /main

ENTRYPOINT [ "bash" ]