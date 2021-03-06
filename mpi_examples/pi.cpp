#include <mpi.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#define INT_MAX_ 1000000000

using namespace std;

//int random();

int main(int argc, char *argv[]) {
	MPI_Init(&argc, &argv);
	int myid;
	int size;
	int inside = 0;
	int outside = 0;
	int points =10000;
	int i;

	double x;
	double y;
	double Pi_comp;
	double Pi_real = 3.141592653589793238462643;

	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(myid == 0) {
		int i;

		for(i = 1; i < size; i++)  {/* send out the value of points to all slaves */
			MPI_Send(&points, 1, MPI_INT, i, i, MPI_COMM_WORLD);
		}
	} else {
		MPI_Recv(&points, 1, MPI_INT, 0, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

	double rands[2 * points];

	for(i = 0; i < 2 * points; i++) {
		rands[i] = random();
	}

	for(i = 0; i < points; i++) {
		x =rands[2 * i] / INT_MAX_;
		y =rands[2 * i + 1] / INT_MAX_;
		if((x * x + y * y) < 1) {
			inside++; /* point is inside unit circle so incr var inside */
		}
	}

	//delete[] rands; //don't think this is needed

	if(myid == 0) {
		for(i = 1; i < size; i++) {
			int temp; /* master receives all inside values from slaves */
			MPI_Recv(&temp, 1, MPI_INT, i, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			inside += temp;
		} /* master sums all insides sent to it by slaves */
	} else {
		MPI_Send(&inside, 1, MPI_INT, 0, i, MPI_COMM_WORLD); /* send inside to master*/
	}

	if(myid == 0) {
		Pi_comp = 4 * (double) inside / (double)(size * points);
		cout << "Value obtained: " << Pi_comp << endl << "Pi:" << Pi_real << endl;
	}

	MPI_Finalize(); 
}
