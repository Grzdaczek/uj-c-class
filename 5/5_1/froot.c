#include <stdlib.h>
#include <stdio.h>
#include "mfunc.h"

int froot(double *x0, double x1, double x2, double epsf, double epsx, int secant) {
	int i;
	for(i = 1; abs((x1+x2)/x1)>epsx && abs(f(*x0))>epsf ;i++) {
		if(f(x1)*f(x2) > 0) return 0;
		if(f(x1) == 0) { *x0 = x1; return i;}
		if(f(x2) == 0) { *x0 = x2; return i;}
		*x0 = !secant ? (x1+x2)/2 : (x2-x1)*(-f(x1))/(f(x2)-f(x1));
		if(f(*x0)*x1 > 0) x1=*x0; else x2=*x0;
		printf("i: %d\t x1: %e\t x2: %e\t x0: %e\t f(x0): %e\n", i, x1, x2, *x0, f(*x0));
	}
	return i;
}
