#include <omp.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
	int th_id;
	int nthreads;
	#pragma omp parallel private(th_id) shared(nthreads)
	{
		th_id = omp_get_thread_num(); // returns thread id
		#pragma omp critical // only one thread can access this at a time!
		{
			cout << "Hello World from thread " << th_id << '\n';
		}
		#pragma omp barrier // one thread waits for all others
		#pragma omp master // master thread access only!
		{
			nthreads = omp_get_num_threads(); // returns number of thread
			cout << "There are " << nthreads << " threads" << '\n';
		}
	}
}
