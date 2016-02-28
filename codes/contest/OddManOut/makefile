CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LDFLAGS = -Wall $(DEBUG)

OddManOut : testOddManOut.c
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	\rm OddManOut
