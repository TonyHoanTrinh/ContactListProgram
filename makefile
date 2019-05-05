CC = gcc
CFLAGS = -Wall -ansi -g -I$(IDIR)

IDIR = ./includes/
SRCDIR = ./src/
BINDIR = ./bin/

all: $(BINDIR)contactList

$(BINDIR)contactList: $(BINDIR)main.o $(BINDIR)functions.o
	$(CC) $(BINDIR)main.o $(BINDIR)functions.o -o $@

$(BINDIR)main.o: $(SRCDIR)main.c
	$(CC) $(CFLAGS) -c $(SRCDIR)main.c -o $@

$(BINDIR)functions.o: $(SRCDIR)functions.c
	$(CC) $(CFLAGS) -c $(SRCDIR)functions.c -o $@

memtest: all
	valgrind ./bin/contactList

clean:
	rm bin/*.o ./bin/contactList