# RAxML Next Generation

[![Build Status](https://www.travis-ci.org/amkozlov/raxml-ng.svg?branch=master)](https://www.travis-ci.org/amkozlov/raxml-ng) [![DOI](https://zenodo.org/badge/75947982.svg)](https://zenodo.org/badge/latestdoi/75947982) [![License](https://img.shields.io/badge/license-AGPL-blue.svg)](http://www.gnu.org/licenses/agpl-3.0.en.html)

## Introduction

RAxML-NG is a phylogenetic tree inference tool which uses maximum-likelihood (ML) optimality criterion. Its search heuristic is based on iteratively performing a series of Subtree Pruning and Regrafting (SPR) moves, which allows to quickly navigate to the best-known ML tree. RAxML-NG is a successor of RAxML (Stamatakis 2014) and leverages the highly optimized likelihood computation implemented in [`coraxlib`](https://codeberg.org/Exelixis-Lab/coraxlib).

RAxML-NG offers improvements in speed, flexibility and user-friendliness over the previous RAxML versions. It also implements some of the features previously available in ExaML (Kozlov et al. 2015), including checkpointing and efficient load balancing for partitioned alignments (Kobert et al. 2014). RAxML-NG version 2.0 offers a plethora of new features such as [adaptive search heuristics](https://doi.org/10.1093/molbev/msad227), [automatic model selection](https://codeberg.org/amkozlov/raxml-ng/wiki/Automatic-model-selection-(MOOSE)), and [fast branch support metrics](https://codeberg.org/amkozlov/raxml-ng/wiki/Computing-branch-support-metrics).

Documentation: [github wiki](https://codeberg.org/amkozlov/raxml-ng/wiki)

## Installation instructions

* For most desktop Unix/Linux and macOS systems, the easiest way to install RAxML-NG is by using the pre-compiled binary:  
[**Download 64-bit Linux binary**](https://codeberg.org/amkozlov/raxml-ng/releases/download/2.0.1/raxml-ng_v2.0.1_linux_x86_64.zip)  
[**Download 64-bit macOS binary**](https://codeberg.org/amkozlov/raxml-ng/releases/download/2.0.1/raxml-ng_v2.0.1_macos.zip)   

* On Windows, you can use [linux binary](https://codeberg.org/amkozlov/raxml-ng/releases/download/2.0.1/raxml-ng_v2.0.1_linux_x86_64.zip) via [Windows Subsystem for Linux](https://ubuntu.com/wsl), but performance might be lower than with native Linux execution. 

* If neither of the above options worked for you, please clone this repository and build RAxML-NG from scratch.

**1. Install the dependecies (optional).** On Ubuntu and other Debian-based systems, you can simply run:
```
sudo apt-get install libgmp3-dev libhts-dev libhtscodecs-dev 
```
For other systems, please make sure you have following packages/libraries installed:  
- [`GMP`](https://gmplib.org/)
- [`htslib`](https://github.com/samtools/htslib)

If you do not want to use git submodules (e.g., for packaging), you also need to install:
- [`coraxlib`](https://codeberg.org/Exelixis-Lab/coraxlib) 
- [`terraphast`](https://github.com/amkozlov/terraphast-one) (optional)

**2. Build RAxML-NG.**

PTHREADS version:

```
git clone --recursive https://codeberg.org/amkozlov/raxml-ng
cd raxml-ng
mkdir build && cd build
cmake ..
make
```

MPI version:

```
git clone --recursive https://codeberg.org/amkozlov/raxml-ng
cd raxml-ng
mkdir build && cd build
cmake -DUSE_MPI=ON ..
make
```

Portable PTHREADS version (static linkage, compatible with old non-AVX CPUs):

```
git clone --recursive https://codeberg.org/amkozlov/raxml-ng
cd raxml-ng
mkdir build && cd build
cmake -DSTATIC_BUILD=ON -DPORTABLE_BUILD=ON ..
make
```

Latest **unstable** development version (`dev` branch):

```
git clone --recursive -b dev https://codeberg.org/amkozlov/raxml-ng raxml-ng-dev
cd raxml-ng-dev
mkdir build && cd build
cmake ..
make
```

## Documentation and Support

Documentation can be found in the [codeberg wiki](https://codeberg.org/amkozlov/raxml-ng/wiki). 
For a quick start, please check out the [hands-on tutorial](https://codeberg.org/amkozlov/raxml-ng/wiki/Tutorial).

Also please check the online help with `raxml-ng -h`.

If still in doubt, please feel free to post to the [RAxML google group](https://groups.google.com/forum/#!forum/raxml).

## Usage examples

  1. Perform single quick&dirty tree inference on DNA alignment 
     (auto-select best-fit model, simplified search heuristic with early stopping):

     `./raxml-ng --fast --msa testDNA.fa --model DNA`

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

  5. To run in `v1.1.0` compatibility mode (disable adaptive search, aggressive logLH thresholds etc.), use:

    ./raxml-ng --msa testDNA.fa --model GTR+G --extra compat-v11

## License and citation

The code is currently licensed under the GNU Affero General Public License version 3.

When using RAxML-NG, please cite [this paper](https://doi.org/10.1093/bioinformatics/btz305):

Alexey M. Kozlov, Diego Darriba, Tom&aacute;&scaron; Flouri, Benoit Morel, and Alexandros Stamatakis (2019)
**RAxML-NG: A fast, scalable, and user-friendly tool for maximum likelihood phylogenetic inference.** 
*Bioinformatics, 35 (21), 4453-4455* 
doi:[10.1093/bioinformatics/btz305](https://doi.org/10.1093/bioinformatics/btz305)

When using the **adaptive** tree search, please cite [(Togkousidis et al. 2023)](https://academic.oup.com/mbe/article/40/10/msad227/7296053)

When using **Educated Bootstrap Guesser (EBG)**, please cite [(Wiegert et al. 2024)](https://doi.org/10.1093/molbev/msae215)

When using **Pythia difficulty prediction**, please cite [(Haag & Stamatakis 2025)](https://doi.org/10.1101/2025.03.25.645182)

## Developer team

* Oleksiy Kozlov
* Alexandros Stamatakis
* Anastasis Togkousidis
* Christoph Stelz
* Ben Bettisworth

Former contributors: Diego Darriba, Tom&aacute;&scaron; Flouri, Julia Haag, Sarah Lutteropp, Benoit Morel. 

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

