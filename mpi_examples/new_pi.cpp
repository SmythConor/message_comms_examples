#include <mpi.h>
#include <iostream>
#include <stdlib.h>

#define INT_MAX_ 1000000000

using namespace std;

int main(int argc, char *argv[]) {
	MPI_Init(&argc, &argv);

	int myid;
	int size;
	int inside = 0;
	int outside = 0;
	int points = 10000;
	int total;

	double x;
	double y;
	double Pi_comp;
	double Pi_real = 3.141592653589793238462643;

	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	/* Again send/receive replaced by MPI_Bcast */
	MPI_Bcast(&points, 1, MPI_INT, 0, MPI_COMM_WORLD);

	double rands[2 * points];

	for(int i = 0; i < 2 * points; i++) {
		rands[i] = random();
	}

	for(int i = 0; i < points;i++) {
		x=rands[2 * i] / INT_MAX_;
		y=rands[2 * i + 1] / INT_MAX_;
		if((x * x + y * y) < 1) {
			inside++; /* point is inside unit circle so incr var inside */
		}
	}

	int i;
	if(myid == 0) {
		for(i = 1; i < size; i++) {
			int temp; /* master gets all inside values from slaves */

			MPI_Recv(&temp, 1, MPI_INT, i, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			inside += temp; 
		} /* master sums all insides sent to it by slaves */
	} else {
		MPI_Send(&inside, 1, MPI_INT, 0, i, MPI_COMM_WORLD); /* send inside to master */
	}

	MPI_Reduce(&inside, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if(myid == 0) {
		Pi_comp = 4 * (double) inside / (double) (size * points);
		cout << "Value obtained: " << Pi_comp << endl << "Pi:" << Pi_real << endl;}
	MPI_Finalize();
}
