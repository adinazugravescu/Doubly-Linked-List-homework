CC=gcc
CFLAGS=-Wall


build: mtema1.c tema1.h
	$(CC) $(CFLAGS) mtema1.c -o tema1

run: build
	./tema1

clean:
	rm -f *.o exec
