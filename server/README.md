# Set-up From Scratch
1. conan new cmake_exe
2. Replace conanfile.py with conanfile.txt and add deps
3. conan install . --output-folder=build --build=missing
4. cd build && cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
5. Update CMakeLists.txt
7. cmake --build . --config Release
8. In a new terminal: ./run.sh ./build/server

# TODO
1. Update protobuf
2. Create data schema, along with a facility table and user
3. Add GroupMe integration using their [API](https://dev.groupme.com/tutorials/bots)
    - This replaces email and mailing list with a Discord server managed by a wider variety of community members
    - https://docs.libcpr.org/

# PSQL
### Useful links
- https://www.postgresql.org/docs/16/index.html
- https://www.geeksforgeeks.org/postgresql-create-schema/
- https://stackoverflow.com/a/41737829 OR https://stackoverflow.com/a/26726006
- https://www.slingacademy.com/article/grant-privileges-user-postgresql/
- https://stackoverflow.com/a/30509741

### Add Schema and Tables
- sudo apt install postgresql
- sudo -u postgres createdb sddb
- sudo -u postgres psql sddb
- create schema test;
- create table test.cats (ID SERIAL primary key, name TEXT, age INT);
- create table test.dogs (ID SERIAL primary key, name TEXT, age INT);
- select * from pg_tables where schemaname='test';

### Create Facility User
- password -> openssl rand -base64 40 | tr -d "=+/" | cut -c1-32
- create role gato with login password 'password'
- grant connect on database sddb to gato;
- grant usage on schema test to gato;
- grant insert on test.cats to gato;
- seq = select pg_get_serial_sequence('test.cats', 'id');
- grant usage on sequence seq to gato;
- set role gato;
- INSERT INTO test.cats (name, age) VALUES ('Zeke', 2); -> allowed
- INSERT INTO test.dogs (name, age) VALUES ('Zeke', 2); -> denied
- SELECT * FROM test.cats; -> denied
- SELECT * FROM test.dogs; -> denied
- sudo -u postgres psql -h localhost -d sddb -U gato

### Create Facility User
- password -> openssl rand -base64 40 | tr -d "=+/" | cut -c1-32
- CREATE ROLE api WITH LOGIN PASSWORD 'password';
- GRANT CONNECT ON DATABASE sddb TO api;
- GRANT USAGE ON SCHEMA test TO api;
- GRANT SELECT ON ALL TABLES IN SCHEMA test TO api;
- SET ROLE api;
- SELECT * FROM test.cats; -> allowed
- SELECT * FROM test.dogs; -> allowed
- INSERT INTO test.cats (name, age) VALUES ('Deigo', 7); -> denied
- INSERT INTO test.dogs (name, age) VALUES ('Deigo', 7); -> denied
- \q

### Other Useful Commands
- SELECT current_user;
- DROP SCHEMA test CASCADE;
- DROP ROLE user_name;
- ALTER ROLE user_name WITH PASSWORD 'new_password';
- \conninfo

# The N-Facility Problem
Central Admin:
- Create certs for DB and facility's DB user (mTLS)
- Create certs for facility's broker, along with broker usernames and passwords
- Server binary is built 
    1. Pre-detmined: 
        - cert names (corresponding certs get copied into server folder and renamed) 
        - broker usernames for clock and server
        - broker topics
    2. Dynamic (load dotenv):
        - DB username, password, and table name 
        - broker passwords 

Facility Admin:
- Install mosquitto to deploy (broker needs hardware's domain name to circumvent localhost proxying)
- Uses Dockerfile to create and deploy facility's server
- Uses platform.io and plain.txt to create and flash ESP binaries
- Deploys ESP devices