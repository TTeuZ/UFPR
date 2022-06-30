SHELL = /bin/sh

FLAGS = -std=c99 -g -Wall
LIBS = -lm

# Funções gerais
all: gps

clean: 
		-rm -f *.o

purge: clean
		-rm -f gps

# Construção do executavel
gps: gps.o bicycle.o bicycles.o parser.o reader.o utils.o
		$(CC) $(FLAGS) bicycle.o bicycles.o parser.o reader.o utils.o gps.o -o gps $(LIBS)

# Construção dos Objetos
gps.o: gps.c
		$(CC) $(FLAGS) -c gps.c

bicycle.o: bicycle.c
		$(CC) $(FLAGS) -c bicycle.c

bicycles.o: bicycles.c
		$(CC) $(FLAGS) -c bicycles.c

parser.o: parser.c
		$(CC) $(FLAGS) -c parser.c

reader.o: reader.c
		$(CC) $(FLAGS) -c reader.c

utils.o: utils.c
		$(CC) $(FLAGS) -c utils.c