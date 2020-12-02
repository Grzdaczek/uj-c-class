C = gcc
CFLAGS = -ansi -O
LDFLAGS = -lm

all: main.o bitop.o
	$(CC) $(CFLAGS) main.o bitop.o $(LDFLAGS)

main: main.c bitop.h
	$(CC) $(CFLAGS) -c main.c

*.o: *.c
	$(CC) $(CFLAGS) -c *.c

clear:
	rm *.o && rm *.out
