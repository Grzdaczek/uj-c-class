#include <stdlib.h>
#include <stdio.h>
#include "bitop.h"

void printd(void *word, size_t size) {
	int i;
	for(i=size*8-1; i>=0; i--) 
		printf("%d", getb(word, i));
	printf("\n");
}

int main(int argc, char *argv[]) {
	char a = 0;
	short int b = 42;
	float c = 1;

	printf("%d \t", a); printd(&a, sizeof(a));
	setb(&a, 7);
	printf("%d \t", a); printd(&a, sizeof(a));
	notb(&a, 5);
	printf("%d \t", a); printd(&a, sizeof(a));
	clrb(&a, 7);
	printf("%d \t", a); printd(&a, sizeof(a));

	printf("%d \t", b); printd(&b, sizeof(b));
	setb(&b, 8);
	printf("%d \t", b); printd(&b, sizeof(b));
	notb(&b, 15);
	printf("%d \t", b); printd(&b, sizeof(b));
	clrb(&b, 1);
	printf("%d \t", b); printd(&b, sizeof(b));

	printf("%e \t", c); printd(&c, sizeof(c));
	setb(&c, 20);
	printf("%e \t", c); printd(&c, sizeof(c));
	notb(&c, 31);
	printf("%e \t", c); printd(&c, sizeof(c));
	notb(&c, 30);
	printf("%e \t", c); printd(&c, sizeof(c));
	clrb(&c, 20);
	printf("%e \t", c); printd(&c, sizeof(c));

}
