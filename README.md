# RAxML Next Generation

[![DOI](https://zenodo.org/badge/75947982.svg)](https://zenodo.org/badge/latestdoi/75947982) [![License](https://img.shields.io/badge/license-AGPL-blue.svg)](http://www.gnu.org/licenses/agpl-3.0.en.html)

## Introduction

RAxML-NG is a phylogenetic tree inference tool which uses maximum-likelihood (ML) optimality criterion. Its search heuristic is based on iteratively performing a series of Subtree Pruning and Regrafting (SPR) moves, which allows to quickly navigate to the best-known ML tree. RAxML-NG is a successor of RAxML (Stamatakis 2014) and leverages the highly optimized likelihood computation implemented in [*libpll*](https://github.com/xflouris/libpll) (Flouri et al. 2014).

RAxML-NG offers improvements in speed, flexibility and user-friendliness over the previous RAxML versions. It also implements some of the features previously available in ExaML (Kozlov et al. 2015), including checkpointing and efficient load balancing for partitioned alignments (Kobert et al. 2014).

RAxML-NG is currently under active development, and the mid-term goal is to have most functionality of RAxML 8.x covered.
You can see some of the planned features [here](https://github.com/amkozlov/raxml-ng/issues).

Documentation: [github wiki](https://github.com/amkozlov/raxml-ng/wiki)

## Installation instructions

* For most desktop Unix/Linux and macOS systems, the easiest way to install RAxML-NG is by using the pre-compiled binary:  
[**Download 64-bit Linux binary**](https://github.com/amkozlov/raxml-ng/releases/download/0.5.0/raxml-ng_v0.5.0b_linux_x86_64.zip)  
[**Download 64-bit OSX/macOS binary**](https://github.com/amkozlov/raxml-ng/releases/download/0.5.0/raxml-ng_v0.5.0b_macos_x86_64.zip)

* For clusters/supercomputers (i.e., if you want to use MPI), please use the following installation package which contains pre-built *libpll*. You will need `GCC 4.8+` and `CMake 2.8+` in order to compile RAxML-NG for your system.  
[**Download RAxML-NG-MPI for Linux**](https://github.com/amkozlov/raxml-ng/releases/download/0.5.0/raxml-ng_v0.5.0b_linux_x86_64_MPI.zip)

* Binaries for Windows will become available later on

* If neither of the above options worked for you, please clone this repository and build RAxML-NG from scratch.

1. **Install the dependecies.** On Ubuntu (and other Debian-based systems), you can simply run:
```
sudo apt-get install autotools-dev autoconf libtool flex bison libgmp3-dev
```
For other systems, please make sure you have following packages/libraries installed:  
[`autoconf`](https://www.gnu.org/software/autoconf/autoconf.html) [`automake`](https://www.gnu.org/software/automake/) [`libtool`](https://www.gnu.org/software/libtool/) [`GNU Bison`](http://www.gnu.org/software/bison/) [`Flex`](http://flex.sourceforge.net/) [`GMP`](https://gmplib.org/)

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

## Documentation and Support

Documentation can be found in the [github wiki](https://github.com/amkozlov/raxml-ng/wiki) (work in progress).

Also please check the online help with `raxml-ng -h`.

If still in doubt, please feel free to post to the [RAxML google group](https://groups.google.com/forum/#!forum/raxml).

## Usage examples

  1. Perform single tree inference on DNA alignment 
     (random starting tree, general time-reversible model, ML estimate of substitution rates and
      nucleotide frequencies, discrete GAMMA model of rate heterogeneity with 4 categories):

     `./raxml-ng --msa testDNA.fa --model GTR+G`

  2. Perform an all-in-one analysis (ML tree search + non-parametric bootstrap) 
     (10 randomized parsimony starting trees, fixed empirical substitution matrix (LG),
      empirical aminoacid frequencies from alignment, 8 discrete GAMMA categories,
      200 bootstrap replicates):

     `./raxml-ng --all --msa testAA.fa --model LG+G8+F --tree pars{10} --bs-trees 200`


  3. Optimize branch lengths and free model parameters on a fixed topology
     (using multiple partitions with proportional branch lengths)

     `./raxml-ng --evaluate --msa testAA.fa --model partitions.txt --tree test.tree --brlen scaled`

  4. Map support values from existing set of replicate trees:

     `./raxml-ng --support --tree bestML.tree --bs-trees bootstraps.tree`

## License and citation

The code is currently licensed under the GNU Affero General Public License version 3.

Pending the publication, you can cite this code as [DOI:10.5281/zenodo.492245](https://doi.org/10.5281/zenodo.492245)

## The team

* Alexey Kozlov
* Alexandros Stamatakis
* Diego Darriba
* Tom&aacute;&scaron; Flouri
* Benoit Morel

## References

* Stamatakis A. (2014)
**RAxML version 8: a tool for phylogenetic analysis and post-analysis of large phylogenies.**
*Bioinformatics*, 30(9): 1312-1313.
doi:[10.1093/bioinformatics/btu033](http://dx.doi.org/10.1093/bioinformatics/btu033)

* Flouri T., Izquierdo-Carrasco F., Darriba D., Aberer AJ, Nguyen LT, Minh BQ, von Haeseler A., Stamatakis A. (2014)
**The Phylogenetic Likelihood Library.**
*Systematic Biology*, 64(2): 356-362.
doi:[10.1093/sysbio/syu084](http://dx.doi.org/10.1093/sysbio/syu084)

* Kozlov A.M., Aberer A.J., Stamatakis A. (2015)
**ExaML version 3: a tool for phylogenomic analyses on supercomputers.**
*Bioinformatics (2015) 31 (15): 2577-2579.*
doi:[10.1093/bioinformatics/btv184](https://doi.org/10.1093/bioinformatics/btv184)

* Kobert K., Flouri T., Aberer A., Stamatakis A. (2014)
**The divisible load balance problem and its application to phylogenetic inference.**
*Brown D., Morgenstern B., editors. (eds.) Algorithms in Bioinformatics, Vol. 8701 of Lecture Notes in Computer Science. Springer, Berlin, pp. 204–216*

