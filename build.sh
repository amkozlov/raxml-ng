#!/bin/bash
binarytreesummation_version=2ceac66c9269a3dfe8956403d8e4edb8b86e62c4
${CMAKE:-cmake} -B cmake-build-release -S . -DUSE_MPI=ON -DBUILD_TESTS=OFF \
    -DREPRODUCIBLE=ON \
    -Dbinarytreesummation_version=$binarytreesummation_version \
    -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=YES \
    "$@"
