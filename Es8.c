/*
* Task 0 initializes a one-dimensional array assigning to each cell the value of its index.
* This array is then divided into chunks and sent to other processes.
* After having received the proper chunk, each process updates it by adding its rank and then sends it back to root process.
* (Analyze the cases for equal and not equal chunks separately).
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define DIM_ARRAY 20

int main (int argc, char * argv[]){

  int me, nprocs, i;

  /* Initialize MPI environment */
  MPI_Init(&argc, &argv) ;

  /* Get the size of the MPI_COMM_WORLD communicator */
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs) ;

  /* Get my rank... */
  MPI_Comm_rank(MPI_COMM_WORLD, &me) ;

  int arr_send[DIM_ARRAY];
  int arr_receive[DIM_ARRAY/nprocs];

  if (me==0){
    /* Init array */
    for(i=0; i < DIM_ARRAY; i++){
      arr_send[i] = i;
    }
  }

  if (DIM_ARRAY % nprocs == 0){
    /* Equal chunks (gather/scatter) */
    MPI_Scatter(arr_send, DIM_ARRAY / nprocs, MPI_INT, arr_receive, DIM_ARRAY / nprocs, MPI_INT, 0, MPI_COMM_WORLD);
    /* print each process sub-array */{
    printf("Process %d: received ", me);
      for (i=0; i < DIM_ARRAY / nprocs ; i++){
           printf("%d ", arr_receive[i]);
      }
      printf("\n");
    }
    /* Increment */
    for (i=0; i < DIM_ARRAY / nprocs; i++){
      arr_receive[i] += me;
    }
    /* Send back to root */
    MPI_Gather(arr_receive, DIM_ARRAY / nprocs, MPI_INT, arr_send, DIM_ARRAY / nprocs, MPI_INT, 0, MPI_COMM_WORLD);
    /* Root prints */
    if(me == 0){
      for (i=0; i < DIM_ARRAY ; i++){
         printf("Final process: received %d\n", arr_send[i]);
      }
    }
  } else {
    /* Not equal chunks (gatherv/scatterv) */

    int ncells[nprocs];
    int tmp = (int) DIM_ARRAY / nprocs;
    int displs[nprocs];

    /* Cells for process */
    for(i=0; i < nprocs; i++){
      ncells[i] = tmp;
    }

    if (DIM_ARRAY % nprocs != 0){
      for(i=0; i < DIM_ARRAY % nprocs; i++){
        ncells[i]++;
      }
    }

    /* Displacements */
    displs[0] = 0;
    for(i=1;i<nprocs;i++){
      displs[i] = displs[i-1] + ncells[i-1];
    }

    /* Scatterv */
    MPI_Scatterv(arr_send, &ncells[me], &displs[me], MPI_INT, arr_receive, ncells[me], MPI_INT, 0, MPI_COMM_WORLD);

    /* print each process sub-array */{
    printf("Process %d: received ", me);
      for (i=0; i < ncells[me] ; i++){
           printf("%d ", arr_receive[i]);
      }
      printf("\n");
    }

    /* Increment */
    for (i=0; i < ncells[me]; i++){
      arr_receive[i] += me;
    }

    /* Send back to root */
    MPI_Gatherv(arr_receive, ncells[me], MPI_INT, arr_send, &ncells[me], &displs[me], MPI_INT, 0, MPI_COMM_WORLD);

    /* Root prints */
    if(me == 0){
      for (i=0; i < DIM_ARRAY ; i++){
         printf("Final process: received %d\n", arr_send[i]);
      }
    }
  }

  /* Finalize MPI environment */
  MPI_Finalize() ;

  return 0;

}
