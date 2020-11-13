#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#define READ_BUFFER_SIZE 100

int fail() {
	printf("\nNie współpracowałeś. Twoja strata.\n");
	return 1;
}

/**
 * Parser for an 'a' coefficient
 * in case the input can be parsed and is valid, returns 0.
 */
int parse_a(char *word, void *_target) { 
	double *target = _target;
	if (sscanf(word ,"%lf", target) == 1 && 
		*target!=0 && 
		!isinf(*target) && 
		!isnan(*target)) return 0;
	else return 1;
}

/**
 * Parser for an 'a' or 'b' coefficient,
 * in case the input can be parsed and is valid, returns 0.
 */
int parse_b_or_c(char *word, void *_target) {
	double *target = _target;
	if (sscanf(word ,"%lf", target) == 1 && 
		!isinf(*target) && 
		!isnan(*target)) return 0;
	else return 1;
}

/**
 * Checks for prefix in given string,
 * returns 0 when found.
 */
int is_prefixed(char *string, char *prefix) {
	int i;
	if (strlen(string) < strlen(prefix)) return 0;
	for (i=0; prefix[i] != '\0'; i++) if (prefix[i] != string [i]) return 0;
	return 1;
}

/**
 * Attempts to obtain an argument from user, firs checks in argv[].
 * When not found, prompts the user for input,
 * until the appropriate value is obtained or error occurs.
 */
int obtain_arg(int argc, char* argv[], void *target, char *prefix, int (*parse)(char*, void*)) {
	
	int i;
	for (i=1; i<argc; i++) {
		char *arg = argv[i];
		if (strlen(arg) < strlen(prefix)+1) continue;
		if (!is_prefixed(arg, prefix)) continue;
		char *word = arg + strlen(prefix);
		if (!parse(word, target)) return 0;
		else break;
	}
	
	char word[READ_BUFFER_SIZE];
	while(1) {
		printf("> %s", prefix);
		if (!fgets(word, READ_BUFFER_SIZE, stdin)) return 1;
		if (!parse(word, target)) return 0;
	}

}

/* --------------------------------------------------------------------------------------------------- */

int main(int argc, char *argv[]) {

	double a;
	double b;
	double c;

	printf("obliczanie rozwiązania dla równania w postaci: ax^2 + bx + c = 0\n");
	if(obtain_arg(argc, argv, &a, "a=", parse_a)) return fail();
	if(obtain_arg(argc, argv, &b, "b=", parse_b_or_c)) return fail();
	if(obtain_arg(argc, argv, &c, "c=", parse_b_or_c)) return fail();
	printf("\n");

	double delta = (b*b) - (4*a*c);
	double p = -b/2*a;
	double q = -sqrt(fabs(delta))/2*a;
	
	if (delta == 0) {
		printf("równianie %.*fx^2 + %.*fx + %.*f = 0 ma jedno rozwiązanie rzeczywiste:\n", 2, a, 2, b, 2, c);
		printf("x = %f\n", p + q);
	}
	else if (delta > 0) {
		printf("równianie %.*fx^2 + %.*fx + %.*f = 0 ma dwa rozwiązania rzeczywiste:\n", 2, a, 2, b, 2, c);
		printf("x1 = %f\n", p + q);
		printf("x2 = %f\n", p - q);
	} 
	else if (delta < 0) {
		printf("równianie %.*fx^2 + %.*fx + %.*f = 0 ma dwa rozwiązania zespolone:\n", 2, a, 2, b, 2, c);
		printf("x1 = %f + %fi\n", p, q);
		printf("x2 = %f + %fi\n", p, -q);
	}

}