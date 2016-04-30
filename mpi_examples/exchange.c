#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int myid;
	int otherid;
	int myvalue;
	int othervalue;
	int size;
	int length = 1;
	int tag = 1;

	MPI_Status status;

	/* initialize MPI and get own id (rank) */
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (size != 2) {
		printf("use exactly two processes\n");
		exit(1);
	} if (myid == 0) {
		otherid = 1;
		myvalue = 14;
	} else {
		otherid = 0;
		myvalue = 25;
	}

	printf("process %d sending %d to process %d\n", myid, myvalue, otherid);

	/* Send one integer to the other node (i.e. "otherid") */
	MPI_Send(&myvalue,1,MPI_INT,otherid,tag,MPI_COMM_WORLD);

	/* Receive one integer from any other node */
	MPI_Recv(&othervalue,1,MPI_INT,MPI_ANY_SOURCE, MPI_ANY_TAG,MPI_COMM_WORLD, 
		&status);

	printf("process %d received a %d\n", myid, othervalue);

	MPI_Finalize(); /* Terminate MPI */
}
