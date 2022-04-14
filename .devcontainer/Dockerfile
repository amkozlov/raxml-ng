# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.187.0/containers/cpp/.devcontainer/base.Dockerfile

# [Choice] Debian / Ubuntu version: debian-10, debian-9, ubuntu-20.04, ubuntu-18.04
ARG VARIANT="buster"
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

RUN apt-get update \
 && export DEBIAN_FRONTEND=noninteractive \
 && apt-get -y install --no-install-recommends \
      bison \
      cmake \
      flex \
      libgmp3-dev \
      libgtest-dev \
      libopenmpi-dev \
      ninja-build \
      openmpi-bin \
      openmpi-common \
      python3-dev \
      python3-pip \
      python3-pip \
      python3-setuptools \
      vim \
 && apt-get clean \
 && rm -rf /var/lib/apt/lists/*

RUN pip install \
    cmake==3.20.3

RUN git clone https://github.com/jeetsukumaran/DendroPy.git \
 && cd DendroPy \
 && python3 setup.py install \
 && cd .. \
 && rm -rf DendroPy

RUN useradd --uid 1026 -m user
USER user
