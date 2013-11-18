/*
* Write a code using point to point communication that makes two processes send each other an array of floats containing their rank.
* Each of the processes will declare two float arrays, A and B, of a fixed dimension (10000).
* All of the elements of the array A will be initialized with the rank of the process.
* Then, A and B will be used as the buffers for SEND and RECEIVE, respectively.
* The program terminates with each process printing out one element of the array B.
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define DIM 10000

int main (int argc, char * argv[]){

  int me, nprocs, i;
  MPI_Status status;
  float A[DIM], B[DIM];

  /* Initialize MPI environment */
  MPI_Init(&argc, &argv) ;

  /* Get rank */
  MPI_Comm_rank(MPI_COMM_WORLD, &me);
  
  /* Checks n processes */
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  if(nprocs != 2 && me==0){
    printf("\nThis program requires 2 processors\n\n");
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  /* Fill A array with rank */
  for(i=0; i < DIM; i++){
    A[i]=me;
  }

  if(me==0){
    /*Task 0*/
    MPI_Send(A, DIM, MPI_REAL, 1, 0, MPI_COMM_WORLD);
    MPI_Recv(B, DIM, MPI_REAL, 1, 0, MPI_COMM_WORLD, &status);
  } else {
    /*Task 1 */
    MPI_Recv(B, DIM, MPI_REAL, 0, 0, MPI_COMM_WORLD, &status);
    MPI_Send(A, DIM, MPI_REAL, 0, 0, MPI_COMM_WORLD);
  }

  /* ...and print it. */
  printf("\tHello, I am task %d : I received %.2f\n", me, B[0]);
  
  /* Finalize MPI environment */
  MPI_Finalize() ;

  return 0;
}
