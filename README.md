# RAxML New Generation

[![License](https://img.shields.io/badge/license-AGPL-blue.svg)](http://www.gnu.org/licenses/agpl-3.0.en.html)

## Introduction

RAxML-NG is a phylogenetic tree inference tool which uses maximum-likelihood (ML) optimality criterion. Its search heuristic is based on iteratively performing a series of Subtree Pruning and Regrafting (SPR) moves, which allows to quickly navigate to the best-known ML tree. RAxML-NG is a successor of RAxML (Stamatakis 2014) and leverages the highly optimized likelihood computation implemented in [*libpll*](https://github.com/xflouris/libpll) (Flouri et al. 2014).

RAxML-NG offers improvements in speed, flexibility and user-friendliness over the previous RAxML versions. It also implements some of the features previously available in ExaML (Kozlov et al. 2015), including checkpointing and efficient load balancing for partitioned alignments (Kobert et al. 2014).

RAxML-NG is currently under active development, and the mid-term plan is to have most functionality of RAxML 8.x covered.
You can see some of the planned features [here](https://github.com/amkozlov/raxml-ng/issues).

## Installation instructions

* For most desktop Unix/Linux and macOS systems, the easiest way to install RAxML-NG is by using the pre-compiled binary:
  [**Download 64-bit Linux binary**](https://github.com/amkozlov/raxml-ng/releases/download/0.1.0/raxml-ng_v0.1.0b_linux_x86_64.zip)
  [**Download 64-bit OSX/macOS binary**](https://github.com/amkozlov/raxml-ng/releases/download/0.1.0/raxml-ng_v0.1.0b_macos_x86_64.zip)

* For clusters/supercomputers (i.e., if you want to use MPI), please use the following installation package which contains pre-built *libpll*. You will need `GCC 4.8+` and `CMake 2.8+` to compile RAxML-NG for your system.
  [**Download RAxML-NG-MPI for Linux**](https://github.com/amkozlov/raxml-ng/releases/download/0.1.0/raxml-ng_v0.1.0b_linux_x86_64_MPI.zip)

* Binaries for Windows will become available later on

* If neither of the above options worked for you, please clone this repository and build RAxML-NG from scratch:

```
git clone --recursive https://github.com/amkozlov/raxml-ng
cd raxml-ng
mkdir build && cd build
cmake ..
make
```

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

## License and third party licenses

The code is currently licensed under the GNU Affero General Public License version 3.

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

