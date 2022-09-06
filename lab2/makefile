CC = gcc
CFLAGS = -g -Wall

default: my_kill

my_kill: my_kill.o
	$(CC) $(CFLAGS) -o my_kill killme.o

my_kill.o: my_kill.c
	$(CC) $(CFLAGS) -c my_kill.c

clean:
	rm -f my_kill *.o
