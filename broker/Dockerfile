FROM debian:bookworm-slim
RUN apt-get update && apt-get install -y mosquitto
RUN useradd -ms /bin/bash broker

USER broker
WORKDIR /home/broker

COPY --chown=broker:broker certs/ certs/
COPY --chown=broker:broker creds/ creds/
COPY --chown=broker:broker mosquitto.conf mosquitto.conf

EXPOSE 8885
ENTRYPOINT ["mosquitto", "-c", "mosquitto.conf"]

# https://stackoverflow.com/a/40869934
# docker build -t broker .
# docker run --rm -p 1883:1883 -it broker