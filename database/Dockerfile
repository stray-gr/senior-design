#########################################################################
# Inherit the Postgres 17 Debian Bookworm (aka: Debian 12) docker image #
#########################################################################
FROM postgres:17-bookworm

# Copy the postgresql server's SSL certs and configuration file into the container 
COPY certs/ /var/lib/postgresql/certs/
COPY postgres.conf /etc/postgres.conf

# Change permissions and ownership of the server's key to the 'postgres' user
RUN chmod 600 /var/lib/postgresql/certs/server.key
RUN chown postgres:postgres /var/lib/postgresql/certs/server.key

# Set the default user to the 'postgres' user
# WARNING: Using the 'root' user will lead to errors
USER postgres

# Open port 5432 on the container
EXPOSE 5432

# WARNING: DO NOT ADD AN ENTRYPOINT OR CMD... ISSUES DOCKER VOLUMES WILL ARISE
