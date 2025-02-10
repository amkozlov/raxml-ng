#!/bin/bash
binarytreesummation_version=ae0f58394902813ba4d86ecb0a5e0d26e47f93c5
${CMAKE:-cmake} -B cmake-build-release -S . -DUSE_MPI=ON -DBUILD_TESTS=OFF \
    -DREPRODUCIBLE=ON \
    -Dbinarytreesummation_version=$binarytreesummation_version \
    -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=YES \
    "$@"
