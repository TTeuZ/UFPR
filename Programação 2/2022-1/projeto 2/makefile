SHELL = /bin/sh

FLAGS = -std=c99 -g -Wall
LIBS = -lm
ALLEGRO = `pkg-config allegro-5\
				allegro_font-5\
				allegro_ttf-5\
				allegro_primitives-5\
				allegro_image-5\
				allegro_audio-5\
				allegro_acodec-5\
				--libs --cflags`

OBJECTS = ballz.o conditions.o display.o error.o keyboard.o mouse.o aim.o game.o pages.o player.o speeder.o audio.o fonts.o images.o addBall.o ball.o coin.o square.o

# Funções gerais
all: ballz

clean: 
		-rm -f *.o

purge: clean
		-rm -f ballz

# Construção do executavel
ballz: $(OBJECTS)
		$(CC) $(OBJECTS) -o ballz $(FLAGS) $(LIBS) $(ALLEGRO)

# Construção dos Objetos
ballz.o: ballz.c
		$(CC) -c ballz.c $(FLAGS)

conditions.o: ./src/functions/conditions/conditions.c
		$(CC) -c ./src/functions/conditions/conditions.c $(FLAGS)

display.o: ./src/functions/display/display.c
		$(CC) -c ./src/functions/display/display.c $(FLAGS)

error.o: ./src/functions/error/error.c
		$(CC) -c ./src/functions/error/error.c $(FLAGS)

keyboard.o: ./src/functions/keyboard/keyboard.c
		$(CC) -c ./src/functions/keyboard/keyboard.c $(FLAGS)

mouse.o: ./src/functions/mouse/mouse.c
		$(CC) -c ./src/functions/mouse/mouse.c $(FLAGS)

aim.o: ./src/game/aim/aim.c
		$(CC) -c ./src/game/aim/aim.c $(FLAGS)

game.o: ./src/game/game/game.c
		$(CC) -c ./src/game/game/game.c $(FLAGS)

pages.o: ./src/game/pages/pages.c
		$(CC) -c ./src/game/pages/pages.c $(FLAGS)

player.o: ./src/game/player/player.c
		$(CC) -c ./src/game/player/player.c $(FLAGS)

speeder.o: ./src/game/speeder/speeder.c
		$(CC) -c ./src/game/speeder/speeder.c $(FLAGS)

audio.o: ./src/loadables/audio/audio.c
		$(CC) -c ./src/loadables/audio/audio.c $(FLAGS)

fonts.o: ./src/loadables/fonts/fonts.c
		$(CC) -c ./src/loadables/fonts/fonts.c $(FLAGS)

images.o: ./src/loadables/images/images.c
		$(CC) -c ./src/loadables/images/images.c $(FLAGS)

addBall.o: ./src/objects/addBall/addBall.c
		$(CC) -c ./src/objects/addBall/addBall.c $(FLAGS)

ball.o: ./src/objects/ball/ball.c
		$(CC) -c ./src/objects/ball/ball.c $(FLAGS)

coin.o: ./src/objects/coin/coin.c
		$(CC) -c ./src/objects/coin/coin.c $(FLAGS)

square.o: ./src/objects/square/square.c
		$(CC) -c ./src/objects/square/square.c $(FLAGS)