CC=gcc

all: kilo.o
	clear
	$(CC) kilo.o -Wall -Wextra -pedantic -std=c99

kilo.o: kilo.c
	$(CC) -c kilo.c -Wall -Wextra -pedantic -std=c99

clean: kilo.o
	rm kilo.o