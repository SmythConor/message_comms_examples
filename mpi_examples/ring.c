#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int rank;
	int value;
	int size;

	int typeCheck;
	char ret;

	MPI_Status status;

	/* initialize MPI and get own id (rank) */
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	do {
		if (rank == 0) {
			typeCheck = scanf("%d%c", &value, &ret);

			if(typeCheck != 2) {
				printf("Enter valid integer");
				exit(1);
			} else {
				/* Master Node sends out the value */
				MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
			}
		} else {
			/* Slave Nodes block on receive the send on the value */
			MPI_Recv(&value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);

			if(rank < size - 1) {
				MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
			}
		}

		printf("process %d got %d\n", rank, value);
	} while (value >= 0);

	/* Terminate MPI */
	MPI_Finalize();
}
