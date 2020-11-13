#include <stdlib.h>
#include <stdio.h>

double r_fib(double a, double b, double n) {
	return n<3 ? b : r_fib(b, a+b, n-1);
}

double i_fib(double a, double b, double n) {
	for(n; n>=3; n--) {
		double temp = a+b;
		a = b;
		b = temp;
	}
	return b;
}

int main(int argc, char *argv[]) {
	double n;
	printf("podaj ile wyrazów ciągu policzyć :");
	if(scanf("%lf", &n) != 1) return 1;
	printf("iretacyjnie:\t%f\n", i_fib(1, 1, n));
	printf("rekurencyjnie:\t%f\n", r_fib(1, 1, n));
	return 0;
}