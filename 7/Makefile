CC = gcc
CFLAGS = -ansi -O -c
LDFLAGS = -lm

all: a.out

a.out: main.o utils.o
	$(CC) main.o utils.o $(LDFLAGS) -o a.out

main.o: main.c student.h utils.h
	$(CC) $(CFLAGS) main.c

utils.o: utils.c student.h
	$(CC) $(CFLAGS) utils.c

%.o: %.c
	$(CC) $(CFLAGS) -o $@.o -c $<.c

clear:
	rm -rf *.o *.out

.PHONY: all clear
