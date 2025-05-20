# syntax=docker/dockerfile:1
FROM docker.io/debian:bookworm AS build
WORKDIR /src
COPY . /src
RUN apt update && apt install -y libopenmpi-dev build-essential git bison flex cmake pkg-config python3
RUN cmake -B build -S . \
        -DCMAKE_BUILD_TYPE=Release \
        -DUSE_MPI=ON -DREPRODUCIBLE=ON -DUSE_TERRAPHAST=OFF
RUN cmake --build build

FROM docker.io/debian:bookworm
    RUN apt update && apt install -y libopenmpi3 openmpi-bin
COPY --from=build /src/build/bin/raxml-ng-mpi /usr/bin/raxml-ng-mpi
