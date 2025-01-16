###################################################################################################
# Inherit from Debian's Bookworm (aka: Debian 12) slim docker image to build project dependencies #
###################################################################################################
FROM debian:bookworm-slim AS deps

# Install the build-essential metapackage, which comes with most compilers and build tools needed
# Install CMake, another build tool dependency
# Install wget, which is then used to download Conan's Debian package
RUN apt-get update && apt-get install -y build-essential cmake wget
RUN wget https://github.com/conan-io/conan/releases/download/2.10.1/conan-2.10.1-amd64.deb

# Install Conan's Debian package, then create a build profile for Conan to use
RUN apt-get install -y ./conan-2.10.1-amd64.deb
RUN conan profile detect --force

# Copy files into the container's /server folder that are needed by Conan to build dependencies
WORKDIR /server
COPY CMakeLists.txt CMakeLists.txt
COPY CMakeUserPresets.json CMakeUserPresets.json
COPY conanfile.txt conanfile.txt

# Use Conan to build project dependencies (THIS WILL TAKE A WHILE)
RUN conan install /server --output-folder=build --build=missing

##################################################################################
# Inherit from the previous container, where we built the project's dependencies #
##################################################################################
FROM deps AS build

# Copy the project's source code into the container's /server folder
WORKDIR /server
COPY include/ include/
COPY msg_def/ msg_def/
COPY src/ src/
COPY msg.proto msg.proto

# Set up the CMake toolchain, then build the project's executables
WORKDIR /server/build/ 
RUN cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
RUN cmake --build . --config Release

################################################################
# Inherit Debian's Bookworm (aka: Debian 12) slim docker image #
################################################################
FROM debian:bookworm-slim AS server

# Install Debian's base SSL certificates, along with the ping CLI tool for debugging
# NOTE: The SSL certs are needed to send POST requests to GroupMe's chat bot API
RUN apt-get update && apt-get install -y ca-certificates iputils-ping 

# Copy the server binary from the previous stage, then run it
COPY --from=build /server/build/server /main
ENTRYPOINT [ "/main" ]

################################################################
# Inherit Debian's Bookworm (aka: Debian 12) slim docker image #
################################################################
FROM debian:bookworm-slim AS clock

# Copy the clock binary from the previous stage, then run it
COPY --from=build /server/build/clock /main
ENTRYPOINT [ "/main" ]
