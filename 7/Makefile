C = gcc
CFLAGS = -ansi -O -c
LDFLAGS = -lm

all: main utils
	$(CC) main.o utils.o $(LDFLAGS)

main: main.c student.h utils.h
	$(CC) $(CFLAGS) main.c

utils: utils.c student.h
	$(CC) $(CFLAGS) utils.c

*.o: *.c
	$(CC) $(CFLAGS) *.c

clear:
	rm *.o && rm *.out
