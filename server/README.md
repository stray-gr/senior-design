# Table of Contents
1. [Set Up](#set-up)
    - [Prerequisites](#prerequisites)
    - [From Current Repo](#from-current-repo)
    - [From Scratch](#from-scratch)
3. [Protobuf Formats](#protobuf-formats)
4. [Dockerfile](#dockerfile)
5. [Separation of Roles](#separation-of-roles)
6. [TODO](#todo)

# Set Up
### Prerequisites
Make sure the following sofware is installed:
- Unix-like OS (preferably Ubuntu 24.04)
    > Make sure to install the WSL plugin for VS code if you're on Windows
- GCC and G++ (or equivalent compilers)
- The following build tools:
    - Make
    - CMake
    - Autoconf
    - Jinja2
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
4. Run `source build/conanbuild.sh` to add the project's version of protoc to the **current** shell's path
5. Compile the project's protobuf definition by running `protoc --cpp_out=. msg.proto`. Then move the generated C++ file into the src folder and the header file into the include folder
6. `cd` into the newly created build/ folder and run `cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release` to configure CMake
7. Rename *example.env* to *.env* and update its environment variables
    > For the BOT_ID variable, refer to the [GroupMe Chat Bots](https://dev.groupme.com/bots) page
8. To build the project, run: `cmake --build . --config Release`
9. `cd` back into the server/ folder and run `chmod a+x run.sh`. This script can then be used to run one of the project's built executables (e.g. `./run.sh build/server`)

### From Scratch
To create your own CMake project from scratch, follow these steps:
1. Create the project folder and `cd` into it
2. Run `conan new cmake_exe` to create the boilerplate files needed for Conan to expose external project dependcies to CMake
3. Replace the generated *conanfile.py* with this repo's *conanfile.txt*. Then add your project's external dependcies and their configuration options
    > A listing of external dependencies can be found at the [Conan Center](https://conan.io/center)
4. Run `conan install . --output-folder=build --build=missing` to build your project's dependencies
5. Run `source build/conanbuild.sh` to add your project's tool dependencies (e.g. protoc) to the **current** shell's path
6. Compile the project's protobuf definition by running `protoc --cpp_out=. msg.proto`. Then move the generated C++ file into the src folder and the header file into the include folder
7. Update your *CMakeLists.txt* to include your external dependencies and create executable targets for your project. An example can be seen with this repo's *CMakeLists.txt* 
8. `cd` into the build/ folder and run `cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release` to configure CMake
9. Open VS Code's command pallet by clicking CTRL+SHIFT+P, then select *CMAKE: Select Configure Preset*. Choose the `'conan release' config` to enable proper source code linting
10. Start developing your project's source, such that source files go into the src/ folder and header files go into the include/ folder
    - If your project plans on using sensitive environment variables, make sure to add these in a *.env* file  that is excluded via a *.gitignore*
11. When you're ready to build your project's executables, `cd` into the build/ folder and run `cmake --build . --config Release`
12. Run your executables via: `./build/exe_name`
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

# Dockerfile
### Purpose
- The local server's Dockerfile is to be used for:
    1. Deployment to facilities in an operating system agnostic way
    2. Building project executables without needing the toolchain installed locally

### Step-by-Step Explanation
- For a step-by-step explanation of each command in the Dockerfile, refer to the file's comments
- Any ports mapped from the container to the host machine can be found in the compose.yaml file at the repo's root 

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
