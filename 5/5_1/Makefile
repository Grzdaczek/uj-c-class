CC = gcc
CFLAGS = -ansi -O
LDFLAGS = -lm

all: main.o froot.o mfunc.o
	$(CC) $(CFLAGS) main.o froot.o mfunc.o $(LDFLAGS)

main: main.c froot.h mfunc.h
	$(CC) $(CFLAGS) -c main.c

froot: froot.c mfunc.h
	$(CC) $(CFLAGS) -c froot.c

*.o: *.c
	$(CC) $(CFLAGS) -c *.c

clear:
	rm *.o && rm *.out
