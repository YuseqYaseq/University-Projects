CC=gcc
OPT=-Wall

all: clean s c

s: s_test.c lib.c queue.c
	$(CC) $^ -o $@ $(OPT)
c: c_test.c lib.c queue.c
	$(CC) $^ -o $@ $(OPT)

clean:
	rm -f c s
