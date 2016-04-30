#include <mpi.h>
#include <stdio.h>

#define NPROCS 8

int main(int argc, char *argv[]) {
	int rank;
	int newrank;
	int sendbuf;
	int recvbuf;

	int ranks1[4] = {0,1,2,3};
	int ranks2[4] = {4,5,6,7};

	MPI_Group orig_group;
	MPI_Group new_group;

	MPI_Comm new_comm;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	sendbuf = rank;

	/* Extract the original group handle */
	MPI_Comm_group(MPI_COMM_WORLD, &orig_group);
	if (rank < NPROCS / 2) {/* Split tasks into 2 distinct groups based on rank */
		MPI_Group_incl(orig_group, NPROCS / 2, ranks1, &new_group);
	} else {
		MPI_Group_incl(orig_group, NPROCS / 2, ranks2, &new_group);
	}

	/* Create new communicator and then perform collective communications */
	MPI_Comm_create(MPI_COMM_WORLD, new_group, &new_comm);

	MPI_Allreduce(&sendbuf, &recvbuf, 1, MPI_INT, MPI_SUM, new_comm);

	MPI_Group_rank(new_group, &newrank);
	printf("rank= %d newrank= %d recvbuf= %d\n", rank, newrank, recvbuf);
	MPI_Finalize();
}
