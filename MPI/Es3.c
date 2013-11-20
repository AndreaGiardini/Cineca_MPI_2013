/*
* Each task will declare two float arrays, A and B, of a fixed dimension (10000).
* Every element of A will be initialized with the rank of the process.
* Then, A and B will be used as the buffers for SEND and RECEIVE, respectively.
* Each process sends only to the process on its right and receives only from the process on its left.
* As you can see from the picture the last process will send its array A to the first task. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define DIM 10000

int main (int argc, char * argv[]){

  int me, nprocs, i, right, left;
  float A[DIM], B[DIM];
  MPI_Status status;
  MPI_Request request;

  /* Initialize MPI environment */
  MPI_Init(&argc, &argv) ;

  /* Get rank */
  MPI_Comm_rank(MPI_COMM_WORLD, &me);

  /* Get n processes */
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

  /* Fill A array with rank */
  for(i=0; i < DIM; i++){
    A[i]=me;
  }

  /* Find destination (right) and source (left) */
  right = me + 1;
  left = me - 1;
  /* Special cases (left of 0 / right of nprocs) */
  if(right==nprocs){
    right=0;
  }
  if(left==-1){
    left=nprocs-1;
  }

  /* Async send and sync receive */
  MPI_Isend(A, DIM, MPI_REAL, right, 0, MPI_COMM_WORLD, &request);
  MPI_Recv(B, DIM, MPI_REAL, left, 0, MPI_COMM_WORLD, &status);

  /* and print it. */
  printf("\tHello, I am task %d : I received %.2f\n", me, B[0]);

  /* Finalize MPI environment */
  MPI_Finalize() ;

  return 0;
}
