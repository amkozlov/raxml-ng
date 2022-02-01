#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: build.sh <suffix> <build-type>"
    exit 1
fi

BUILD_DIR="build-$1"

rm -fr $BUILD_DIR
mkdir -p $BUILD_DIR
cd $BUILD_DIR

cmake -DCMAKE_BUILD_TYPE=$2 .. 2>&1 |tee cmake.out
make 2>&1 |tee make.out
