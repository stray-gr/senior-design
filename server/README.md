# Table of Contents
1. [Set Up](#set-up)
    - [Prerequisites](#prerequisites)
    - [From Current Repo](#from-current-repo)
    - [From Scratch](#from-scratch)
3. [Protobuf Formats](#protobuf-formats)
4. [Separation of Roles](#separation-of-roles)
5. [TODO](#todo)

# Set Up
### Prerequisites
Make sure the following sofware is installed:
- Unix-like OS (preferably Ubuntu 24.04)
    > Make sure to install the WSL plugin for VS code if you're on Windows
- VS Code w/ the following plugins:
    - C/C++ Extension Pack
    - vscode-proto3
- Protobuf compiler (protoc)
    > This can be done via your OS package manager, such as `apt` or `brew`
- [Conan](https://conan.io/downloads)
    > This can be done via `pipx`, a cross-platform package manager

### From Current Repo
To set up the current project:
1. Open the *server* folder in VS Code
2. Run `conan profile detect --force` to set up Conan
3. Run `conan install . --output-folder=build --build=missing` to install the project's dependencies
4. `cd` into the newly created build/ folder and run `cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release` to configure CMake
5. Rename *example.env* to *.env* and update its environment variables
    > For the BOT_ID variable, refer to the [GroupMe Chat Bots](https://dev.groupme.com/bots) page
6. To build the project, run: `cmake --build . --config Release`
7. `cd` back into the server/ folder and run `chmod a+x run.sh`. This script can then be used to run one of the project's built executables (e.g. `./run.sh build/server`)

### From Scratch
To create your own CMake project from scratch, follow these steps:
1. Create the project folder and `cd` into it
2. Run `conan new cmake_exe` to create the boilerplate files needed for Conan to expose external project dependcies to CMake
3. Replace the generated *conanfile.py* with this repo's *conanfile.txt*. Then add your project's external dependcies and their configuration options
    > A listing of external dependencies can be found at the [Conan Center](https://conan.io/center)
4. Run `conan install . --output-folder=build --build=missing` to build your project's dependencies
    - If your project plans to use protobufs, make sure the Conan protobuf package version matches the same version as your local protoc 
5. `cd` into the newly created build/ folder and run `cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release` to configure CMake
6. Update your *CMakeLists.txt* to include your external dependencies and create executable targets for your project. An example can be seen with this repo's *CMakeLists.txt* 
    - If your project plans to use protobufs, make sure to put them in a subdirectory and to include the subdirectory in your *CMakeLists.txt*. Then add a *CMakeLists.txt* into the subdirectory that builds the protobuf definitions as a library for your project to use
7. Start developing your project's source, such that source files go into the src/ folder and header files go into the include/ folder
    - If your project plans on using sensitive environment variables, make sure to add these in a *.env* file  that is excluded via a *.gitignore*
8. When you're ready to build your project's executables, `cd` into the build/ folder and run `cmake --build . --config Release`
9. Run your executables via: `./build/exe_name`
    - If your project uses a *.env* file, the copy the contents of *run.sh*. This bash script will allow you to add your sensitive environment variables to the current shell's environment before running the executable passed by the first CLI argument 

# Protobuf Formats
### LWT Messages
- **Publishers:** Each ESP32
- **Subscriber:** Local Server "data/lwt" Topic
- **QoS:** 1
- **Special properties:** 1 minute delay, retained
- **Payload:**
    ```proto
    message LWT {
        string device = 1;  // Device username
    }
    ```

### Data Messages
- **Publishers:** Each ESP32
- **Subscriber:** Local Server "data/sensor" Topic
- **QoS:** 1
- **Special properties:** none
- **Payload:**
    ```proto
    message Data {
        string device = 1;   // Device username
        int32    temp = 2;   // Temperature
        float      rh = 3;   // Relative Humidity
        int64   epoch = 4;   // Unix Epoch (time_t seconds)
    }
    ```

# Separation of Roles
### Central Admin
- Create certs, users, and facility tables for the central DB 
- Create certs for the facility's broker, along with broker usernames and passwords
- Builds local server executables
    1. Pre-detmined values: 
        - cert names
        - broker usernames for clock and server
        - broker topics
    2. Runtime values (dotenv):
        - DB username, password, and table name 
        - broker passwords 

### Facility Admin
- Install mosquitto to deploy (broker needs hardware's domain name to circumvent localhost proxying)
- Uses Dockerfile and dotenv template to create and deploy facility's local server
- Uses platform.io and plain.txt to create and flash ESP binaries
- Deploys ESP devices

# TODO
1. ~~Create src and include folders for clock, client, and server~~
2. Add broker and server docker-compose services to one subnet
3. Create a PostgreSQL service that runs on another subnet
4. Test system using mqttx for clock pulses
5. Update server container to run clock and server
6. Finish updating docs
    - Explanation of Dockerfiles and compose.yml
    - Update diagrams