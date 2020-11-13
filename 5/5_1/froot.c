#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mfunc.h"

int signCmp(double a, double b) {
	return (a>0 && b>0) || (a<0 && b<0) || (a==b) ? 1 : 0;
}

int froot(double *x0, double x1, double x2, double epsf, double epsx, int useSecant) {
	int i;
	int j=1;
	int k=0;

	printf("\n%-8s│ %-17s│ %-17s\n", "iter.", "f(x0)", "x0");
	printf("%s╪%s╪%s\n", "════════", "══════════════════", "══════════════════");

	for(i = 1; fabs(x1-x2) > epsx && fabs(f(*x0)) > epsf ;i++) {
		*x0 = useSecant ? x2-(x2-x1)*f(x2)/(f(x2)-f(x1)) : (x1+x2)/2;
		
		if(j==i) {
			printf("2^%-6d│ %-17e│ %-17e\n", k, f(*x0), *x0);
			k+=1;
			j*=2;
		}

		if(signCmp(f(x1), f(x2))) return 0;
		if(*x0 == x1 || *x0 == x2) { return i;}
		if(signCmp(f(*x0), f(x1))) x1=*x0; else x2=*x0;
	}

	return i;
}