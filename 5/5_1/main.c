#include <stdlib.h>
#include <stdio.h>
#include "froot.h"
#include "mfunc.h"

int main(int argc, char *argv[]) {
	
	double x0, x1, x2, epsf, epsx;
	int i;

	/* wyczytywanie danych do x1, x2 */
	x1 = 5.4;
	x2 = -1.1;
	epsf = 0.001;
	epsx = 0.001;

	if(i = froot(&x0, x1, x2, epsf, epsx, 0)) {
		printf("znaleziono x:f(x)=0 w %d iteracjach\n", i);
		printf("x = %f\n", x0);
	} else {
		printf("nie znaleziono x0\n");
	}

	return 0;
}
