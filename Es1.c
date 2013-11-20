/*
* Using MPI try to print out:
* "Hello world, I am proc X of total Y"
* with a total number of tasks Y = 4 and X ranging from 0 to 3.
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main (int argc, char * argv[]) {
  int me, nprocs;

  /* Initialize MPI environment */
  MPI_Init(&argc, &argv) ;

  /* Get the size of the MPI_COMM_WORLD communicator */
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs) ;

  /* Get my rank */
  MPI_Comm_rank(MPI_COMM_WORLD, &me) ;

  /* Print the rank */
  printf("Hello, I am task %d of %d.\n", me, nprocs);

  /* Finalize MPI environment */
  MPI_Finalize() ;

  return 0;
}
