CC=gcc
OPT=-Wall

all: clean b c

b: barber.c lib.c queue.c
	$(CC) $^ -o $@ $(OPT)
c: client.c lib.c queue.c
	$(CC) $^ -o $@ $(OPT)

clean:
	rm -f c b
