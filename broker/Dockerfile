###############################################
# Inherit Debian's Bookworm slim docker image #
###############################################
FROM debian:bookworm-slim

# Install Mosquitto 
# Add the 'broker' user via useradd
RUN apt-get update && apt-get install -y mosquitto
RUN useradd -ms /bin/bash broker

# Set the main user to the 'broker' user 
# Set the container's working directory to the 'broker' user's home folder
USER broker
WORKDIR /home/broker

# Copy the broker's certs, ACL, and passwords into the container
# Copy the broker's configuration file into the container
# NOTE: the --chown argument sets the 'broker' user as the owner of each copied resource
COPY --chown=broker:broker certs/ certs/
COPY --chown=broker:broker creds/ creds/
COPY --chown=broker:broker mosquitto.conf mosquitto.conf

# Open ports 1884 and 8885 on the container
# Port 1884 is used for unencrypted and authenticated traffic via docker's local network 
# Port 8885 is used for encrypted and authenticated traffic from external users
# WARNING: Never map 1884 to a port on the host machine. LOCAL TRAFFIC ONLY
EXPOSE 1884
EXPOSE 8885

# Run the broker with the copied configuration file
ENTRYPOINT ["mosquitto", "-c", "mosquitto.conf"]
