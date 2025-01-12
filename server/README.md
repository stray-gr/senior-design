# Set-up From Scratch
1. conan new cmake_exe
2. Replace conanfile.py with conanfile.txt and add deps
3. conan install . --output-folder=build --build=missing
4. cd build && cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
5. Update CMakeLists.txt
7. cmake --build . --config Release
8. In a new terminal: ./run.sh ./build/{executable name}

# TODO
1. Update protobuf
2. Create data schema, along with a facility table and user
3. Add GroupMe integration using their [API](https://dev.groupme.com/tutorials/bots)
    - This replaces email and mailing list with a Discord server managed by a wider variety of community members
    - https://docs.libcpr.org/


# The N-Facility Problem
### Central Admin
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

### Facility Admin
- Install mosquitto to deploy (broker needs hardware's domain name to circumvent localhost proxying)
- Uses Dockerfile to create and deploy facility's server
- Uses platform.io and plain.txt to create and flash ESP binaries
- Deploys ESP devices