# Table of Contents
1. [Prerequisites](#prerequisites)
2. [TLS Cert Creation](#tls-cert-creation)
3. [Database Set Up](#database-set-up)

# Prerequisites
Make sure to have the following software installed:
- Unix-like OS (preferrably Ubuntu 24.04)
- postgresql server (preferrably version 16+)
- Openssl

# TLS Cert Creation
1. Once you postgresql installed, run `sudo -u postgres bash`
2. Run `psql -c 'show data_directory;'` to find where the data directory for postgres is located
3. `cd` into the data directory and create the certs/ folder
4. `cd` into the certs/ folder and create the certificate authority's private key and cert. Make sure to set `<duration>` to the number of days the key and cert should be valid for: 
    ```
    openssl req -new -x509 -days <duration> -extensions v3_ca -keyout ca.key -out ca.crt
    ```
5. Create the postgresql server's private key: `openssl genrsa -out server.key 2048`
6. Create the server's certificate signing request (CSR): `openssl req -out server.csr -key server.key -new` 
    - Make sure to set **Common Name** to the message server's hostname (e.g. "My-PC-Name")
7. Sign the CSR using the certificate authority we initially created. Make sure to set `<duration>` to the number of days the broker's private key and cert should be valid for: 
    ```
    openssl x509 -req -in server.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out server.crt -days <duration>
    ```
8. Run `psql -c 'show config_file;'` to find where the config file for postgres is located
9. Update the following SSL variables in the config file for postgres. Make sure to set `<datadir>` with the postgres data directory's location:
    ```
    ssl = on
    ssl_ca_file = '<datadir>/certs/ca.crt'
    ssl_cert_file = '<datadir>/certs/server.crt'
    ssl_key_file = '<datadir>/certs/server.key'
    listen_addresses = '*'
    ```
10. Run `psql -c 'show hba_file;'` to find where the HBA (host-based authentication) file for postgres is located
11. Add the following entry to the HBA file for postgres to enforce SSL connections:
    ```
    hostssl all all 0.0.0.0/0 md5
    ```
12. Exit the postgres user shell and restart the postgres server
    - If you're on an Ubuntu-based system, restart the server by running: `sudo service postgresql restart` 

# Database Set Up
### Add Facility Schema and Tables
- sudo -u postgres createdb sddb
- sudo -u postgres psql sddb
- create schema data;
- create table data.facility_n (ID SERIAL primary key, device TEXT NOT NULL, temp INT, rh REAL, epoch BIGINT NOT NULL);
- create index idx_epoch on data.facility_n (epoch);
- select * from pg_tables where schemaname='data';
- \q

### Create Facility User
- Create user password using: `openssl rand -base64 40 | tr -d "=+/" | cut -c1-32`
- sudo -u postgres psql sddb
- create role facility_n with login password 'password';
- grant connect on database sddb to facility_n;
- grant usage on schema data to facility_n;
- grant insert on data.facility_n to facility_n;
- Find sequence_id using: `select pg_get_serial_sequence('data.facility_n', 'id');`
- grant usage on sequence sequence_id to facility_n;
- \q
- Test user connection using: `sudo -u postgres psql -h localhost -d sddb -U facility_n -W`

### Create API User
- Create user password using: `openssl rand -base64 40 | tr -d "=+/" | cut -c1-32`
- sudo -u postgres psql sddb
- create role api with login password 'password';
- grant connect on database sddb to api;
- grant usage on schema data to api;
- grant select on all tables in schema data to api;
- \q
- Test user connection using: `sudo -u postgres psql -h localhost -d sddb -U api -W`

### Other Useful Commands
- `SELECT current_user;` returns current user
- `DROP SCHEMA test CASCADE;` removes a schema and its tables
- `DROP ROLE user_name;` removes a user
- `ALTER ROLE user_name WITH PASSWORD 'new_password';` changes a user's password
- `\conninfo` lists connection info

### Useful links
- https://www.postgresql.org/docs/16/index.html
- https://www.geeksforgeeks.org/postgresql-create-schema/
- https://stackoverflow.com/a/41737829 OR https://stackoverflow.com/a/26726006
- https://www.slingacademy.com/article/grant-privileges-user-postgresql/
- https://stackoverflow.com/a/30509741
