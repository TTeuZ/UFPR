SHELL = /bin/sh

FLAGS = -std=c99 -g -Wall
ALLEGRO = `pkg-config allegro-5\
				allegro_font-5\
				allegro_ttf-5\
				allegro_primitives-5\
				allegro_image-5\
				--libs --cflags`

OBJECTS = ballz.o display.o mouse.o game.o home.o player.o utils.o addBall.o ball.o coin.o square.o

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

mouse.o: ./src/functions/mouse/mouse.c
		$(CC) -c ./src/functions/mouse/mouse.c $(FLAGS)

utils.o: ./src/functions/utils/utils.c
		$(CC) -c ./src/functions/utils/utils.c $(FLAGS)

game.o: ./src/game/game/game.c
		$(CC) -c ./src/game/game/game.c $(FLAGS)

home.o: ./src/game/home/home.c
		$(CC) -c ./src/game/home/home.c $(FLAGS)

player.o: ./src/game/player/player.c
		$(CC) -c ./src/game/player/player.c $(FLAGS)

addBall.o: ./src/objects/addBall/addBall.c
		$(CC) -c ./src/objects/addBall/addBall.c $(FLAGS)

ball.o: ./src/objects/ball/ball.c
		$(CC) -c ./src/objects/ball/ball.c $(FLAGS)

coin.o: ./src/objects/coin/coin.c
		$(CC) -c ./src/objects/coin/coin.c $(FLAGS)

square.o: ./src/objects/square/square.c
		$(CC) -c ./src/objects/square/square.c $(FLAGS)