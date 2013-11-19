/*
* Distribute a global square NxN matrix (with N fixed) over P processors, so that each task has a local portion of it in its memory.
* Initialize such portion with the task's rank.
* Each task sends its first and last rows to its neighbours
* (i.e.: the first column/row to the left processor, the last column/row to the right processor).
* Note that each task has to actually allocate a larger portion of its submatrix (ghost cells), with two extra
*  rows at the extremities to hold the received values. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define N 9

int main (int argc, char * argv[]){

  int nprocs, me;
  /* Initialize MPI environment */
  MPI_Init(&argc, &argv) ;

  /* Get rank */
  MPI_Comm_rank(MPI_COMM_WORLD, &me);

  /* Get n processes */
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

  if(nprocs > N){
    printf("Rows number shuold be more than process number\n");
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  int localmatrix_size[nprocs];
  int i=0;

  int tmp = (int) N / nprocs;

  for(i=0; i < nprocs; i++){
    localmatrix_size[i] = tmp;
  }

  if (N % nprocs != 0){
    for(i=0; i < N % nprocs; i++){
      localmatrix_size[i]++;
    }
  }

  int j, matrix[localmatrix_size[me]+2][N];

  for(i=1; i <= localmatrix_size[me]; i++){
    for(j=0; j < N; j++){
      matrix[i][j]=me;
    }
  }

  return 0;
}
