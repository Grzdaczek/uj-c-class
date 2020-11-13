#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "froot.h"
#include "mfunc.h"

int main(int argc, char *argv[]) {
	
	double x0, x1, x2, eps;
	char useSecant = 'n';
	int i;

	printf("> x1 = ");
	scanf("%lf", &x1);

	printf("> x2 = ");
	scanf("%lf", &x2);
	
	printf("> use secant? (y/n) ");
	scanf("%s", &useSecant);
	
	printf("> eps = ");
	scanf("%lf", &eps);
	
	if(i = froot(&x0, x1, x2, fabs(eps), fabs(eps), useSecant == 'y')) {
		printf("\nZnaleziono x:f(x)=0 w %d iteracjach.\n", i);
		printf("x = %e\n", x0);
		printf("f(x) = %e\n", f(x0));
	} else {
		printf("\nnie znaleziono x:f(x)=0\n");
	}

	return 0;
}
