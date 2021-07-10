# Makefile for Mico12

CC = gcc
CFLAGS = -O2 -DDEBUG -Wall

LIBS = -l ncurses

DEPS = screen.h

OBJ = mico12.o screen.o

all: mico

mico12.c : mico12.h screen.h
screen.c : screen.h

mico12.o : mico12.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCL)

screen.o : screen.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCL)

mico: mico12.o screen.o
	$(CC) -o $@ $^ $(LIBS)

clean:
	rm -f $(OBJ) core *~

realclean: clean
	rm -f mico a.out

