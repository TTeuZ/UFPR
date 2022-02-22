SHELL = /bin/sh

FLAGS = -g -std=c90 -Wall
LIBS = -lm

# Funções gerais
all: pgmlbp pgmlimiar pgmmedia pgmmediana pgmnega pgmrotacao

clean:
		-rm -f *.o

purge: clean
		-rm -f pgmlbp pgmlimiar pgmmedia pgmmediana pgmnega pgmrotacao

# Construção dos executaveis
pgmlbp: pgmlbp.o core_functions.o image_functions.o
		$(CC) $(FLAGS) core_functions.o image_functions.o pgmlbp.o -o pgmlbp $(LIBS)

pgmlimiar: pgmlimiar.o core_functions.o image_functions.o
		$(CC) $(FLAGS) core_functions.o image_functions.o pgmlimiar.o -o pgmlimiar $(LIBS)

pgmmedia: pgmmedia.o core_functions.o image_functions.o
		$(CC) $(FLAGS) core_functions.o image_functions.o pgmmedia.o -o pgmmedia $(LIBS)

pgmmediana: pgmmediana.o core_functions.o image_functions.o
		$(CC) $(FLAGS) core_functions.o image_functions.o pgmmediana.o -o pgmmediana $(LIBS)

pgmnega: pgmnega.o core_functions.o image_functions.o
		$(CC) $(FLAGS) core_functions.o image_functions.o pgmnega.o -o pgmnega $(LIBS)

pgmrotacao: pgmrotacao.o core_functions.o image_functions.o
		$(CC) $(FLAGS) core_functions.o image_functions.o pgmrotacao.o -o pgmrotacao $(LIBS)

# Construção dos Objetos
core_functions.o: core_functions.c
		$(CC) $(FLAGS) -c core_functions.c

image_functions.o: image_functions.c
		$(CC) $(FLAGS) -c image_functions.c

pgmlbp.o: pgmlbp.c
		$(CC) $(FLAGS) -c pgmlbp.c

pgmlimiar.o: pgmlimiar.c
		$(CC) $(FLAGS) -c pgmlimiar.c

pgmmedia.o: pgmmedia.c
		$(CC) $(FLAGS) -c pgmmedia.c

pgmmediana.o: pgmmediana.c
		$(CC) $(FLAGS) -c pgmmediana.c

pgmnega.o: pgmnega.c
		$(CC) $(FLAGS) -c pgmnega.c

pgmrotacao.o: pgmrotacao.c
		$(CC) $(FLAGS) -c pgmrotacao.c