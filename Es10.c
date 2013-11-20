/*
* Each task initializes a square nxn matrix (n is the total number of the tasks) with 0s,
* except for the diagonal elements of the matrix that are initialized with the task's rank number.
*
* Each task sends to rank 0 an array containing all the elements of its diagonal.
* Task 0 overwrites the array sent by process i on the i-th row (column if Fortran) of its local matrix.
* At the end, task 0 prints its final matrix, on which each element should be the number of its row (or column).
*
* In order to send a diagonal, a proper vector datatype should be created and set for reading the diagonal
* elements of a matrix with the right displacement and stride. When you are communicating to rank 0,
* keep in mind that you are sending a single vector datatype, but you want to receive an array of n elements,
* that have to be stored contiguously in its matrix row (or column).
*/
