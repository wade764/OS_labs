CC = gcc
CFLAGS = -g -Wall

default: killme

killme: killme.o
	$(CC) $(CFLAGS) -o killme killme.o

killme.o: killme.c
	$(CC) $(CFLAGS) -c killme.c

clean:
	rm -f killme *.o
