CC=gcc
CFLAGS=-I.

prompt: prompt.c parser.c
	$(CC) -o prompt prompt.c parser.c $(CFLAGS)
