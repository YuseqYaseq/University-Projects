CC=gcc
OPT=-Wall
LIBS=-lpthread

all: clean main

main: main.c mqueue.c
	$(CC) $^ -o $@ $(OPT) $(LIBS)

clean:
	rm -f main
