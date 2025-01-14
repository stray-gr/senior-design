FROM postgres:17-bookworm
# RUN useradd -ms /bin/bash postgres

USER postgres
WORKDIR /var/lib/postgresql

# chmod 0600 issue
COPY --chown=postgres:postgres certs/ certs/
COPY --chown=postgres:postgres postgres.conf /etc/postgres.conf

EXPOSE 5432
ENTRYPOINT ["postgres", "-c", "config_file=/etc/postgres.conf"]

# https://stackoverflow.com/a/41912295
