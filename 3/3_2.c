#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define READ_BUFFER_SIZE 100

int read_double(char *prompt, double *number) {
	double temp;
	char line[READ_BUFFER_SIZE];
	while (1) {
		printf("%s", prompt);
		if (!fgets(line, READ_BUFFER_SIZE, stdin)) return 0;
		if (sscanf(line, "%lf", &temp) == 1 && !isinf(temp) && !isnan(temp)) {
			*number = temp;
			return 1;
		}
	}
}

int main() {
	
	double a = 0;
	double b = 0;
	double c = 0;

	printf("obliczanie rozwiązania dla równania w postaci: ax^2 + bx + c = 0\n\n");

	while (!a) if(!read_double("podaj (różny od 0) współczynnik a: ", &a)) return;
	if(!read_double("podaj współczynnik b: ", &b)) return;
	if(!read_double("podaj wyraz wolny c: ", &c)) return;
	
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