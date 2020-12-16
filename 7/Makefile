C = gcc
CFLAGS = -ansi -O
LDFLAGS = -lm

all: main.o
	$(CC) main.o $(LDFLAGS)

*.o: *.c
	$(CC) $(CFLAGS) -c *.c

clear:
	rm *.o && rm *.out
