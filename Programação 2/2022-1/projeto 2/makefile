SHELL = /bin/sh

FLAGS = -std=c99 -g -Wall
ALLEGRO = `pkg-config allegro-5\
				allegro_font-5\
				allegro_primitives-5\
				--libs --cflags`

# Funções gerais
all: ballz

clean: 
		-rm -f *.o

purge: clean
		-rm -f ballz

# Construção do executavel
ballz: ballz.o 
		$(CC) ballz.o -o ballz $(FLAGS) $(ALLEGRO)

# Construção dos Objetos
ballz.o: ballz.c
		$(CC) -c ballz.c $(FLAGS)
