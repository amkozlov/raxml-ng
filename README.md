# Repro-RAxML-NG

This variant of [RAxML-NG](https://github.com/amkozlov/raxml-ng) uses a novel reduction algorithm to ensure identical results even when executed with a varying degree of parallelism (different CPU core counts).


### Restrictions
* Execution of same binary and shared libraries (see [Containerization](#containerization)) with identical input files, command line arguments, SIMD level (e.g. `AVX2`) and random seed.
* Unpartitioned data
* MPI parallelization only
* some optimizations disabled (site repeats, pattern compression, tip-inner)

Under these circumstances, the core count can be varied freely and will not affect the end result. Furthermore will the likelihood value be bitwise identical.

## Containerization

To ensure that the exact same machine code is executed, we recommend to run RAxML-NG inside a container. You can build a docker image from source as follows:

```console
docker build -f Dockerfile -t reproraxmlng .
```

Then either use mpirun inside the container:
```console
docker run \
    --interactive --tty \
    --volume=/path/to/data:/data \
    --workdir=/data \
    mpirun -np $(nproc) \
    raxml-ng-mpi --msa /data/msa.fa --model DNA
```

or use an OpenMPI 4 compatible `mpirun` to launch the containerized MPI processes. This is useful when working with a workload manager such as SLURM running on a compute cluster. See our [benchmarking repository](https://github.com/stelzch/reproducible-reduce-benchmark) for an example of this.

## Reduction algorithms

This RAxML-NG version also serves as a testbed for different reproducible reduction algorithms. See [reprored](https://github.com/stelzch/reprored) for the underlying library and options.
