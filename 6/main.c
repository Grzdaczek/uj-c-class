#include <stdlib.h>
#include <stdio.h>
#include "bitop.h"

void printb(unsigned int b) {
	int i;
	for(i = sizeof(i)*8-1; i >= 0 ; i--) {
		printf(i%8 ? "%d" : "%d ", getb(b, i));
	}
	printf(": 0x%X ", b);
	printf(": '%c'\n", b);
}

int main(int argc, char *argv[]) {
	int i;
	int d;
	printf("> int = ");
	scanf("%d", &d);
	printb(d);
}
