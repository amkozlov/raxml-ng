#!/bin/bash

ver=${1:-1.2.2}

echo "Building raxml-ng v$ver"

docker build -t amkozlov/raxml-ng:$ver --build-arg VERSION=$ver .
