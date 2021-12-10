CC=gcc

all: kilo.o
	$(CC) kilo.o -Wall -Wextra -pedantic -std=c99
	clear

kilo.o: kilo.c
	$(CC) -c kilo.c -Wall -Wextra -pedantic -std=c99

clean: kilo.o
	rm kilo.o