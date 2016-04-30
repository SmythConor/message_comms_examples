#include <stdio.h>
int main() {
	int a;
	int b = 0;
	#pragma omp parallel for private(a) shared(b)
	for(a = 0; a < 50; ++a) {
		#pragma omp atomic // means that either happens or doesn't.
		b += a; // one thread can't interrupt another here
	}
}
