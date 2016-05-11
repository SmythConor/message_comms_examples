#include <mpi.h>
#include "omp.h"

void main(int argc, char *argv[]) {
	int i;
	int myid;
	int numprocs;

	long num_steps = 100000;

	double x;
	double pi;
	double my_steps;
	double step;
	double sum = 0.0;

	step = 1.0 / (double) num_steps;
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	my_steps = num_steps / numprocs;

	#pragma omp parallel for private (x) reduction(+:sum)
	for(i = myid * my_steps; i < (myid + 1) * my_steps; i++) {
		x = (i + 0.5) * step;
		sum += 4.0 / (1.0 + x * x);
	}

	sum *= step;

	MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
}
