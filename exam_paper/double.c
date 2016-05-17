#include "mpi.h"
#include <stdio.h>

int main(int argc, char **argv) {
	/* initialise variables */
	int rank; //rank of this process
	int size; //number of processes
	int value = 1; //value to send
	MPI_Request request; //request for sending
	MPI_Status status; //status for receiving

	MPI_Init(&argc, &argv); //initialise MPI
	MPI_Comm_size(MPI_COMM_WORLD, &size); //store the number of processes in size
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); //store the rank of this process in rank

	if(rank == 0) {
		/* if we are the first process, send the data to the second process */
		MPI_Isend(&value, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &request);
	} else {
		/* otherwise wait to receive data */
		MPI_Recv(&value, 1, MPI_INT, rank - 1, 1, MPI_COMM_WORLD, &status);

		/* print that we got data */
		printf("Value %i received\n", value);

		/* dobule the data */
		value *= 2;

		/* Send the data to the next process, unless we are the last process then do nothing */
		if(rank + 1 != size) {
			MPI_Isend(&value, 1, MPI_INT, rank + 1, 1, MPI_COMM_WORLD, &request);
		}
	}

	/* finalize MPI */
	MPI_Finalize();
}
