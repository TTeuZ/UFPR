SHELL = /bin/sh

FLAGS = -std=c99 -g -Wall
ALLEGRO = `pkg-config allegro-5\
				allegro_font-5\
				allegro_primitives-5\
				--libs --cflags`

OBJECTS = ballz.o display.o game.o utils.o addBall.o ball.o coin.o square.o

# Funções gerais
all: ballz

clean: 
		-rm -f *.o

purge: clean
		-rm -f ballz

# Construção do executavel
ballz: $(OBJECTS)
		$(CC) $(OBJECTS) -o ballz $(FLAGS) $(ALLEGRO)

# Construção dos Objetos
ballz.o: ballz.c
		$(CC) -c ballz.c $(FLAGS)

display.o: ./src/functions/display/display.c
		$(CC) -c ./src/functions/display/display.c $(FLAGS)

game.o: ./src/functions/game/game.c
		$(CC) -c ./src/functions/game/game.c $(FLAGS)

utils.o: ./src/functions/utils/utils.c
		$(CC) -c ./src/functions/utils/utils.c $(FLAGS)

addBall.o: ./src/objects/addBall/addBall.c
		$(CC) -c ./src/objects/addBall/addBall.c $(FLAGS)

ball.o: ./src/objects/ball/ball.c
		$(CC) -c ./src/objects/ball/ball.c $(FLAGS)

coin.o: ./src/objects/coin/coin.c
		$(CC) -c ./src/objects/coin/coin.c $(FLAGS)

square.o: ./src/objects/square/square.c
		$(CC) -c ./src/objects/square/square.c $(FLAGS)