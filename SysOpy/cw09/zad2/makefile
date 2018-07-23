CC=gcc
OPT=-Wall
LIBS=-lpthread

all: clean main

main: main.c squeue.c
	$(CC) $^ -o $@ $(OPT) $(LIBS)

clean:
	rm -f main
