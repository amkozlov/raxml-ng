FROM ubuntu:24.04

MAINTAINER Oleksiy Kozlov alexey.kozlov@h-its.org

# install required packages
RUN apt-get update \ 
    && apt-get install -y cmake g++ git libgmp-dev libbz2-dev libhts-dev libhtscodecs-dev flex bison  \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

ARG VERSION=master

RUN cd /opt && git clone -b ${VERSION} --recursive https://github.com/amkozlov/raxml-ng.git

# build raxml-ng
RUN cd /opt/raxml-ng && mkdir build && cd build \
    && cmake -DRAXML_BINARY_NAME=raxml-ng  -DSTATIC_BUILD=ON -DPORTABLE_BUILD=ON -DUSE_TERRAPHAST=ON -DUSE_VCF=ON .. \ 
    && make \
    && make install

# Multi-stage build
FROM alpine:latest

LABEL org.opencontainers.image.source https://github.com/amkozlov/raxml-ng
LABEL org.opencontainers.image.description "RAxML-NG: A fast, scalable, and user-friendly tool for maximum likelihood phylogenetic inference"
LABEL org.opencontainers.image.licenses AGPL

COPY --from=0  /opt/raxml-ng/bin/* /usr/local/bin/

RUN mkdir /data

ENV PATH=/usr/local/bin:/home/raxng:$PATH

CMD ["/usr/local/bin/raxml-ng"]
