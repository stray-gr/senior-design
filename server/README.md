# Set-up From Scratch
1. conan new cmake_exe
2. Replace conanfile.py with conanfile.txt and add deps
3. conan install . --output-folder=build --build=missing
4. Update CMakeLists.txt
5. cd build 
6. cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
8. cmake --build . --config Release
8. cd ../
9. ./run.sh ./build/server

# TODO
1. Add [postgres](https://conan.io/center/recipes/libpqxx?version=7.10.0) integration. Make sure to stream inserts
    - Schema for testing (uses cat protobuf toy example)
    - Schema for sensor data
    - Schema for API users
    - How to specify schema via exec: https://stackoverflow.com/a/34098414
2. Add [D++](https://conan.io/center/recipes/dpp?version=10.0.35) integration
    - This replaces email and mailing list with a Discord server managed by a wider variety of community members
3. Bazel build :all

# PSQL
### Useful links
- https://www.postgresql.org/docs/16/index.html
- https://www.geeksforgeeks.org/postgresql-create-schema/
- https://stackoverflow.com/a/41737829 OR https://stackoverflow.com/a/26726006
- https://www.slingacademy.com/article/grant-privileges-user-postgresql/
- https://stackoverflow.com/a/30509741

### Set up
- sudo apt install postgresql
- sudo -u postgres bash
- createdb sddb
- psql sddb
- CREATE SCHEMA IF NOT EXISTS test;
- CREATE TABLE test.cats (ID SERIAL primary key, Name CHARACTER (8), Age INT);
- CREATE TABLE test.dogs (ID SERIAL primary key, Name CHARACTER (8), Age INT);
- SELECT tablename FROM pg_tables WHERE schemaname='test';
- password = openssl rand -base64 40 | tr -d "=+/" | cut -c1-32
- CREATE ROLE gato WITH LOGIN PASSWORD 'password';
- GRANT CONNECT ON DATABASE sddb TO gato;
- GRANT USAGE ON SCHEMA test TO gato;
- GRANT INSERT ON test.cats TO gato;
- seq = SELECT pg_get_serial_sequence('test.cats', 'id');
- GRANT USAGE ON SEQUENCE seq TO gato;
- SET ROLE gato;
- INSERT INTO test.cats (name, age) VALUES ('Zeke', 2); -> allowed
- INSERT INTO test.dogs (name, age) VALUES ('Zeke', 2); -> denied
- SELECT * FROM test.cats; -> denied
- SELECT * FROM test.dogs; -> denied
- SET ROLE postgres;
- password = openssl rand -base64 40 | tr -d "=+/" | cut -c1-32
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