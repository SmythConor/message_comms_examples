#include <stdio.h>

int main(void) {
	#pragma omp parallel num_threads(2)
	printf("Hello, world.\n");
}
