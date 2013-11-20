Cineca MPI 2013
===============

http://www.hpc.cineca.it/content/introduction-to-parallel-computing


Setup

sudo apt-get install mpi-default-dev mpi-default-bin libcr-dev mpich2 mpich2-doc



this should do the trick



To compile:

mpicc -Wall -o [Output File] [Source File.c]


To run:

mpirun -np [number of processes] [File To Run]
