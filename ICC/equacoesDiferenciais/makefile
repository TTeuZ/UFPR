SHELL = /bin/sh

FLAGS = -g -Wall
LIBS = -lm

# Funções gerais
all: labEdo

clean: 
		-rm -f *.o

purge: clean
		-rm -f labEdo

# Construção do executavel
labEdo: labEdo.o edo.o sisLin.o coefficients.o metods.o utils.o
		$(CC) $(FLAGS) labEdo.o edo.o sisLin.o coefficients.o metods.o utils.o -o labEdo $(LIBS)

# Construção dos Objetos
labEdo.o: labEdo.c
		$(CC) $(FLAGS) -c labEdo.c

edo.o: edo.c
		$(CC) $(FLAGS) -c edo.c

sisLin.o: sisLin.c
		$(CC) $(FLAGS) -c sisLin.c

coefficients.o: coefficients.c
		$(CC) $(FLAGS) -c coefficients.c

metods.o: metods.c
		$(CC) $(FLAGS) -c metods.c

utils.o: utils.c
		$(CC) $(FLAGS) -c utils.c