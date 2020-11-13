#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main() {
	
	int zero = 0;
	int i = 2;
	float f = 5.5;
	double d = 11.1;

	printf("i = %d\n", i);
	printf("f = %f\n", f);
	printf("d = %f\n", d);
	printf("i / f = %f\n", i / f);
	printf("i + f = %f\n", i + f);
	printf("f * d = %f\n", f + d);
	printf("f / d = %f\n", f / d);
	printf("f * d = %f\n", f * d);
	printf("i / zero = %f\n", d / zero);

	printf("sqrt(i) = %f\n", sqrt(i));
	printf("sqrt(f) = %f\n", sqrt(f));
	printf("sqrt(d) = %f\n", sqrt(d));
	printf("sqrt(0) = %f\n", sqrt(0));
	printf("sqrt(-i) = %f\n", sqrt(-i));
	printf("pow(i, 2) = %f\n", pow(i, 2));
	printf("sqrt(pow(-i, 2)) = %f\n", sqrt(pow(-i, 2)));

}