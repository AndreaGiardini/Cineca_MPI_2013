/*
* Task 0 initializes a variable to a given value,then modifies the variable
* (for example, by calculating the square of its value) and finally broadcasts it to all the others tasks. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>
#include <math.h>

int main (int argc, char * argv[]){

  int me, nprocs;
  double value;

  /* Initialize MPI environment */
  MPI_Init(&argc, &argv) ;

  /* Get the size of the MPI_COMM_WORLD communicator */
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs) ;

  /* Get my rank... */
  MPI_Comm_rank(MPI_COMM_WORLD, &me) ;

  /* Parameters check */
  if(argc != 2){
    if(me==0){
      printf("\nThis program needs one parameter\n\n");
      MPI_Abort(MPI_COMM_WORLD, 1);
    }
    return 1;
  }

  if(me==0){
    /* Rank 0 process */
    value = atof(argv[1]);
    value = sqrt(value);
  } else {
    value=0;
  }

  printf("Process %d: had %f\n", me, value);
  MPI_Bcast(&value, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD );
  printf("Process %d: received %f\n", me, value);

  /* Finalize MPI environment */
  MPI_Finalize() ;

  return 0;
}
