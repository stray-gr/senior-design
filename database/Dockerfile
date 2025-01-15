FROM postgres:17-bookworm

COPY certs/ /var/lib/postgresql/certs/
COPY postgres.conf /etc/postgres.conf

RUN chmod 600 /var/lib/postgresql/certs/server.key
RUN chown postgres:postgres /var/lib/postgresql/certs/server.key

USER postgres
EXPOSE 5432
ENTRYPOINT ["postgres", "-c", "config_file=/etc/postgres.conf"]
