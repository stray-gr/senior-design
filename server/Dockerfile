FROM debian:bookworm-slim AS deps

RUN apt-get update && apt-get install -y build-essential cmake wget
RUN wget https://github.com/conan-io/conan/releases/download/2.10.1/conan-2.10.1-amd64.deb
RUN apt-get install -y ./conan-2.10.1-amd64.deb
RUN conan profile detect --force

WORKDIR /server
COPY CMakeLists.txt CMakeLists.txt
COPY CMakeUserPresets.json CMakeUserPresets.json
COPY conanfile.txt conanfile.txt
RUN conan install /server --output-folder=build --build=missing

FROM deps AS build
WORKDIR /server
COPY include/ include/
COPY msg_def/ msg_def/
COPY src/ src/
COPY msg.proto msg.proto

WORKDIR /server/build/ 
RUN cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
RUN cmake --build . --config Release

FROM debian:bookworm-slim AS server
RUN apt-get update && apt-get install -y ca-certificates iputils-ping 
COPY --from=build /server/build/server /main
ENTRYPOINT [ "/main" ]

FROM debian:bookworm-slim AS clock
COPY --from=build /server/build/clock /main
ENTRYPOINT [ "/main" ]
