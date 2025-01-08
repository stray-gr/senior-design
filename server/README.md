# Prerequisites
- Rancher desktop
- VS code

# Dev container instructions
- 

# Sever Build instructions
1. Run `make` from server/ folder. To rebuild specific binary, run `make <binary name>`. For example: `make server`
2. Run any binary in server/bin/ from repo root folder. Make sure the message broker is running

# TODO
- add mariadb with test database/schema
- add emails with libcurl
- migrate to dev container and deploy server binaries to container (docker-in-docker needed)