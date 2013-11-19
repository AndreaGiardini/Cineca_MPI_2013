/*
* Each process initializes a one-dimensional array by giving to all the elements the value of its rank+1.
* Then the root process (task 0) performs two reduce operations (sum and then product) to the arrays of all the processes.
* Finally, each process generates a random number and root process finds (and prints) the maximum value among these random values.
* Modify the code to perform a simple scalability test using MPI_Wtime. Notice what happens when you go up with the number of processes involved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#include <time.h>
#define DIM_ARRAY 10

int main (int argc, char * argv[]){

  int me, nprocs;
  int init_time = time(NULL);

  /* Initialize MPI environment */
  MPI_Init(&argc, &argv) ;

  /* Get the size of the MPI_COMM_WORLD communicator */
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs) ;

  /* Get my rank... */
  MPI_Comm_rank(MPI_COMM_WORLD, &me) ;

  int i, arr_send[DIM_ARRAY], arr_recv[DIM_ARRAY];

  /* Porc.... */
  srand(time(NULL)*(me+1));
  /* Initialize array with rank */
  for(i=0; i < DIM_ARRAY; i++){
    arr_send[i]=me+1;
  }

  MPI_Reduce(arr_send, arr_recv, DIM_ARRAY, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  /* Print Reduce sum */
  if(me==0){
    printf("Print Reduce sum\n");
    printf("arr_recv[0]: %d\n", arr_recv[0]);
  }

  MPI_Reduce(arr_send, arr_recv, DIM_ARRAY, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

  /* Print Reduce prod */
  if(me==0){
    printf("Print Reduce prod\n");
    printf("arr_recv[0]: %d\n", arr_recv[0]);
  }

  /* Generate random number */
  int int_send, int_recv;
  int_send = rand() % 100;
  printf("\nProcesso %d: Random number %d\n", me, int_send);

  /* Reduce Max */
  MPI_Reduce(&int_send, &int_recv, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

  /* Print max number */
  if(me==0){
    printf("Max Num received: %d\n", int_recv);
  }

  /* Print time for each process */
  printf("Process %d - Time elapsed: %.2f\n", me, MPI_Wtime() - init_time);

  /* Finalize MPI environment */
  MPI_Finalize() ;

  return 0;

}
