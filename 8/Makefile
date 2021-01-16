CC		= gcc
CFLAGS	+= -ansi -Wall

CFILES		= main.c
OUTFILE		= a.out
BENCHFILE	= benchmark.csv

all: main.c
	$(CC) $(CFLAGS) main.c -o $(OUTFILE)

benchmark:
	rm -f $(BENCHFILE)
	./$(OUTFILE) 1e1 10 >> $(BENCHFILE)
	./$(OUTFILE) 1e2 10 >> $(BENCHFILE)
	./$(OUTFILE) 1e3 10 >> $(BENCHFILE)
	./$(OUTFILE) 1e4 10 >> $(BENCHFILE)
	./$(OUTFILE) 1e5 10 >> $(BENCHFILE)
	./$(OUTFILE) 1e6 10 >> $(BENCHFILE)
	./$(OUTFILE) 1e7 10 >> $(BENCHFILE)
	./$(OUTFILE) 1e8 10 >> $(BENCHFILE)
	./$(OUTFILE) 1e9 10 >> $(BENCHFILE)
	./$(OUTFILE) 1e10 10 >> $(BENCHFILE)

.PHONY: all benchmark