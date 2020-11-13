#include <stdlib.h>
#include <stdio.h>

int r_silnia(int n) {
	return n<=1 ? 1 : n * r_silnia(n-1);
}

int i_silnia(int n) {
	int m = n;
	while(n-- > 1) m *= n;
	return m;
}

int main(int argc, char *argv[]) {

	int nn;

	printf("> n = ");
	if(scanf("%d", &nn) != 1) return 1;

	printf("%d\n", r_silnia(nn));
	printf("%d\n", i_silnia(nn));

	return 0;
}