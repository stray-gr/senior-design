#########################################################
# Inherit the Postgres 17 Debian Bookworm docker image #
#########################################################
FROM redis:7-bookworm

# Copy the Redis server's SSL certs and configuration file into the container 
COPY certs/ /certs/
COPY redis.conf /redis.conf

# Change permissions and ownership of the server's key to the 'redis' user
RUN chmod 600 /certs/redis.key
RUN chown redis:redis /certs/redis.key

# Set the default user to the 'redis' user
USER redis

# Open port 6379 on the container
EXPOSE 6379

# Start the server
CMD [ "redis-server", "/redis.conf" ]
