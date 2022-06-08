SHELL = /bin/sh

FLAGS = -g -std=c99 -Wall

# Funções gerais
all: gps

clean: 
		-rm -f *.o

purge: clean
		-rm -f gps

# Construção do executavel
gps: gps.o bicycle.o bicycles.o parser.o reader.o
		$(CC) $(FLAGS) bicycle.o bicycles.o parser.o reader.o gps.o -o gps

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