#include <stdio.h>

int main(int argc, char **argv) {
	int a[100];
	int i;
	#pragma omp parallel for
	for(i = 0; i < 100; i++) {
		a[i] = 2 * i;
	}
}
