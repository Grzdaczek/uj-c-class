#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main() {
	
	double a = 0;
	double b = 0;
	double c = 0;

	printf("obliczanie rozwiązania dla równania w postaci: ax^2 + bx + c = 0\n\n");

	do {
		printf("podaj (różny od 0) współczynnik a: ");
		scanf("%lf", &a);
	} while (!a);
	
	printf("podaj współczynnik b: ");
	scanf("%lf", &b);
	printf("podaj wyraz wolny c: ");
	scanf("%lf", &c);
	printf("\n");

	double delta = (b*b) - (4*a*c);
	double p = -b/2*a;
	double q = -sqrt(fabs(delta))/2*a;

	if (delta == 0) {
		printf("równianie %.*fx^2 + %.*fx + %.*f ma jedno rozwiązanie rzeczywiste:\n", 2, a, 2, b, 2, c);
		printf("x = %f\n", p + q);
	}
	else if (delta > 0) {
		printf("równianie %.*fx^2 + %.*fx + %.*f ma dwa rozwiązania rzeczywiste:\n", 2, a, 2, b, 2, c);
		printf("x1 = %f\n", p + q);
		printf("x2 = %f\n", p - q);
	} 
	else if (delta < 0) {
		printf("równianie %.*fx^2 + %.*fx + %.*f ma dwa rozwiązania zespolone:\n", 2, a, 2, b, 2, c);
		printf("x1 = %f + %fi\n", p, q);
		printf("x2 = %f + %fi\n", p, -q);
	}

}