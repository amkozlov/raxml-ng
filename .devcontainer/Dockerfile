# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.187.0/containers/cpp/.devcontainer/base.Dockerfile

# [Choice] Debian / Ubuntu version: debian-10, debian-9, ubuntu-20.04, ubuntu-18.04
ARG VARIANT="buster"
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

RUN apt-get update \
    && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
       ninja-build \
       python-dev \
       python3-dev \
       python3-pip \
       vim \
       flex \
       bison \
       libgmp3-dev \
       libgtest-dev

RUN pip install \
    cmake==3.20.3 \
    conan==1.37.2

RUN useradd --uid 1026 -m user
USER user

RUN conan remote add braintwister https://braintwister.jfrog.io/artifactory/api/conan/braintwister-conan \
 && conan config set general.revisions_enabled=1 \
 && conan profile new default --detect \
 && conan profile update settings.compiler=clang default \
 && conan profile update settings.compiler.libcxx=libstdc++11 default \
 && conan profile update env.CC=/usr/bin/clang default \
 && conan profile update env.CXX=/usr/bin/clang++ default
