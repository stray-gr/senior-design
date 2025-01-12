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
2. In the postgres user bash shell, `cd` to ~/ and create the certs/ folder. Note that ~/ should translate to /var/lib/postgresql/
3. Create the certificate authority's private key and cert. Make sure to set `<duration>` to the number of days the key and cert should be valid for: 
    ```
    openssl req -new -x509 -days <duration> -extensions v3_ca -keyout ca.key -out ca.crt
    ```
4. Create the postgresql server's private key: `openssl genrsa -out server.key 2048`
5. Create the server's certificate signing request (CSR): `openssl req -out server.csr -key server.key -new` 
    - Make sure to set **Common Name** to the message server's hostname (e.g. "My-PC-Name")
6. Sign the CSR using the certificate authority we initially created. Make sure to set `<duration>` to the number of days the broker's private key and cert should be valid for: 
    ```
    openssl x509 -req -in server.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out server.crt -days <duration>
    ```
7. Update the following SSL variables in your /etc/postgresql/16/main/postgresql.conf:
    ```
    ssl = on
    ssl_ca_file = '/var/lib/postgresql/certs/ca.crt'
    ssl_cert_file = '/var/lib/postgresql/certs/server.crt'
    ssl_key_file = '/var/lib/postgresql/certs/server.key'
    ```
8. Add the following entry to your /etc/postgresql/16/main/pg_hba.conf to enforce SSL connections:
    ```
    hostssl all all 0.0.0.0/0 md5
    ```
9. Try restarting the server by exiting the postgres shell and running: `sudo service postgresql restart` 

# Database Set Up
### Useful links
- https://www.postgresql.org/docs/16/index.html
- https://www.geeksforgeeks.org/postgresql-create-schema/
- https://stackoverflow.com/a/41737829 OR https://stackoverflow.com/a/26726006
- https://www.slingacademy.com/article/grant-privileges-user-postgresql/
- https://stackoverflow.com/a/30509741

### Add Schema and Tables
- sudo -u postgres createdb sddb
- sudo -u postgres psql sddb
- create schema test;
- create table test.good (ID SERIAL primary key, ...Columns);
- create table test.bad (ID SERIAL primary key, ...);
- select * from pg_tables where schemaname='test';
- \q

### Create Facility User
- Create user password using: `openssl rand -base64 40 | tr -d "=+/" | cut -c1-32`
- sudo -u postgres psql sddb
- create role username with login password 'password'
- grant connect on database sddb to username;
- grant usage on schema test to username;
- grant insert on test.good to username;
- Find sequence_id using: `select pg_get_serial_sequence('test.good', 'id');`
- grant usage on sequence sequence_id to username;
- set role username;
- INSERT INTO test.good (...Columns) VALUES (...); -> allowed
- INSERT INTO test.bad (...Columns) VALUES (...); -> denied
- SELECT * FROM test.good; -> denied
- SELECT * FROM test.bad; -> denied
- \q

### Create API User
- Create user password using: `openssl rand -base64 40 | tr -d "=+/" | cut -c1-32`
- sudo -u postgres psql sddb
- create role api with login password 'password';
- grant connect on database sddb to api;
- grant usage on schema test to api;
- grant select on all tables in schema test to api;
- set role api;
- SELECT * FROM test.good; -> allowed
- SELECT * FROM test.bad; -> allowed
- INSERT INTO test.good (...Columns) VALUES (...); -> denied
- INSERT INTO test.bad (...Columns) VALUES (...); -> denied

### Other Useful Commands
- `SELECT current_user;` returns current user
- `DROP SCHEMA test CASCADE;` removes a schema and its tables
- `DROP ROLE user_name;` removes a user
- `ALTER ROLE user_name WITH PASSWORD 'new_password';` changes a user's password
- `\conninfo` lists connection info