#!/bin/bash
binarytreesummation_version=e1e3b5d2f5142fdc450b29ce811002f838dee1e8
${CMAKE:-cmake} -B cmake-build-release -S . -DUSE_MPI=ON -DBUILD_TESTS=OFF \
    -DREPRODUCIBLE=ON \
    -Dbinarytreesummation_version=$binarytreesummation_version \
    -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=YES \
    "$@"
