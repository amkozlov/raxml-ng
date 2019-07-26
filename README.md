# RAxML Next Generation with parallel computation of Transfer Bootstrap Expectation (TBE) scores and computation of TBE extra information

## Introduction

Greetings! If you are not here for parallel computation of TBE support or computation of the TBE extra information, we strongly advise you to use the most up-to-date version of RAxML-NG instead. It can be found here: https://github.com/amkozlov/raxml-ng

## Computing TBE support with extra information

Here is one example call which computes TBE support scores as well as the extra table and the extra array. It uses the cutoff value 0.3 for that. It uses 10 threads:
```
./raxml-ng --support --tree REF.nw --bs-trees BS.nw --bs-metric TBE --extra tbe_extra_table,tbe_extra_array,tbe-cutoff{0.3} --threads 10
```

If you don't understand what this is, please read our paper at (TODO: Insert DOI) and its supplementary text (TODO: Insert DOI).

## Installation instructions

* For most desktop Unix/Linux and macOS systems, the easiest way to install RAxML-NG is by using the pre-compiled binary:  
[**Download 64-bit Linux binary**](https://github.com/amkozlov/raxml-ng/releases/download/0.8.1/raxml-ng_v0.8.1_linux_x86_64.zip)  
[**Download 64-bit OSX/macOS binary**](https://github.com/amkozlov/raxml-ng/releases/download/0.8.1/raxml-ng_v0.8.1_macos_x86_64.zip)

* For clusters/supercomputers (i.e., if you want to use MPI), please use the following installation package which contains pre-built *libpll*. You will need `GCC 6.4+` and `CMake 3.0.2+` in order to compile RAxML-NG for your system.  
[**Download RAxML-NG-MPI for Linux**](https://github.com/amkozlov/raxml-ng/releases/download/0.8.1/raxml-ng_v0.8.1_linux_x86_64_MPI.zip)

* Binaries for Windows will become available later on

* If neither of the above options worked for you, please clone this repository and build RAxML-NG from scratch.

1. **Install the dependecies.** On Ubuntu (and other Debian-based systems), you can simply run:
```
sudo apt-get install flex bison libgmp3-dev
```
For other systems, please make sure you have following packages/libraries installed:  
[`GNU Bison`](http://www.gnu.org/software/bison/) [`Flex`](http://flex.sourceforge.net/) [`GMP`](https://gmplib.org/)

2. **Build RAxML-NG.**

PTHREADS version:

```
git clone --recursive https://github.com/amkozlov/raxml-ng
cd raxml-ng
mkdir build && cd build
cmake ..
make
```

MPI version:

```
git clone --recursive https://github.com/amkozlov/raxml-ng
cd raxml-ng
mkdir build && cd build
cmake -DUSE_MPI=ON ..
make
```

Portable PTHREADS version (static linkage, compatible with old non-AVX CPUs):

```
git clone --recursive https://github.com/amkozlov/raxml-ng
cd raxml-ng
mkdir build && cd build
cmake -DSTATIC_BUILD=ON -DENABLE_RAXML_SIMD=OFF -DENABLE_PLLMOD_SIMD=OFF ..
make
```


