/*
* Write a code that performs a circular sum of the tasks' ranks.
* Let A be a float initialized to the rank of the task, and B a float used as a buffer for the receive call.
* Then, let SUM be a variable for storing the partial sum. The code should execute a series of send/receive calls, and, at each step:
*   SUM is updated with the just received buffer B;
*   the send buffer A is set to the just received buffer B.
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main (int argc, char* argv[]){

  float A, B, SUM;
  int i,me, nprocs, right, left;
  MPI_Status status;

  /* Initialize MPI environment */
  MPI_Init(&argc, &argv) ;

  /* Get rank */
  MPI_Comm_rank(MPI_COMM_WORLD, &me);

  /* Get n processes */
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

  /* Find destination (right) and source (left) */
  right = me + 1;
  left = me - 1;
  if(right==nprocs){
    right=0;
  }
  if(left==-1){
    left=nprocs-1;
  }

  /* Initialize A and SUM */
  A = me;
  SUM = 0;

  /* Send and receive */
  for(i=0; i < nprocs; i++){
    MPI_Sendrecv(&A, 1, MPI_INT, right, 0, &B, 1, MPI_INT, left, 0, MPI_COMM_WORLD, &status);
    A=B;
    SUM += B;
  }

  /* ...and print it. */
  printf("\tHello, I am task %d : SUM = %.2f\n", me, SUM);

  /* Finalize MPI environment */
  MPI_Finalize() ;

  return 0;
}
