CC=gcc
OPT=-Wall
LIBS=-lpthread -lm

all: clean main

main: main.c
	$(CC) $^ -o $@ $(OPT) $(LIBS)

clean:
	rm -f main
