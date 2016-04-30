#include <stdio.h>
#include <mpi.h>

void main (int argc, char *argv[]) {
	int i;
	int my_id;
	int numprocs;

	long num_steps = 100000;

	double x;
	double pi;
	double my_steps;
	double step;
	double sum = 0.0;

	step = 1.0 /( double) num_steps;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	my_steps = num_steps / numprocs; // divides num_steps among numprocs
	// each will get a bit of the range to do in its part of for loop
	for(i = my_id * my_steps; i < (my_id + 1) * my_steps; i++) {
		x = (i + 0.5) * step;
		sum += 4.0 / (1.0 + x * x);
	}

	sum *= step;
	MPI_Reduce(&sum,&pi,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

	if(my_id == 0) {
		printf("%f\n", pi);
	}
}
