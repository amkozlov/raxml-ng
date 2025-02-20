#!/bin/bash
binarytreesummation_version=0e2cd01960c808942314867f7f73b24ead8e558d
${CMAKE:-cmake} -B cmake-build-release -S . -DUSE_MPI=ON -DBUILD_TESTS=OFF \
    -DREPRODUCIBLE=ON \
    -Dbinarytreesummation_version=$binarytreesummation_version \
    -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=YES \
    "$@"
