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
WORKDIR /grpc_server
COPY CMakeLists.txt CMakeLists.txt
COPY CMakeUserPresets.json CMakeUserPresets.json
COPY conanfile.txt conanfile.txt

# Use Conan to build project dependencies (THIS WILL TAKE A WHILE)
RUN conan install /grpc_server --output-folder=build --build=missing

##################################################################################
# Inherit from the previous container, where we built the project's dependencies #
##################################################################################
FROM deps AS build

# Copy the project's source code into the container's /server folder
WORKDIR /grpc_server
COPY include/ include/
COPY src/ src/

# Set up the CMake toolchain, then build the project's executables
WORKDIR /grpc_server/build/ 
RUN cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
RUN cmake --build . --config Release

################################################################
# Inherit Debian's Bookworm (aka: Debian 12) slim docker image #
################################################################
FROM debian:bookworm-slim AS grpc-server

# TODO: Copy in certs

# Copy the server binary from the previous stage, then run it
COPY --from=build /grpc_server/build/main /main
ENTRYPOINT [ "/main" ]
