SHELL = /bin/sh

# Variavel com o nome do compilador utilizado pelo makefile
COMPILER = gcc

FLAGS = -g -Wall
LIBS = -lm

# Construção dos Objetos
core_function.o: core_functions.c
		$(COMPILER) $(FLAGS) $(LIBS) -c core_functions.c

pgmlbp.o: pgmlbp.c
		$(COMPILER) $(FLAGS) $(LIBS) -c pgmlbp.c

pgmlimiar.o: pgmlimiar.c
		$(COMPILER) $(FLAGS) $(LIBS) -c pgmlimiar.c

pgmmedia.o: pgmmedia.c
		$(COMPILER) $(FLAGS) $(LIBS) -c pgmmedia.c

pgmmediana.o: pgmmediana.c
		$(COMPILER) $(FLAGS) $(LIBS) -c pgmmediana.c

pgmnega.o: pgmnega.c
		$(COMPILER) $(FLAGS) $(LIBS) -c pgmnega.c

pgmrotacao.o: pgmrotacao.c
		$(COMPILER) $(FLAGS) $(LIBS) -c pgmrotacao.c

# Construção dos executaveis
pgmlbp: pgmlbp.o
		$(COMPILER) $(FLAGS) $(LIBS) pgmlbp.o -o pgmlbp

pgmlimiar: pgmlimiar.o
		$(COMPILER) $(FLAGS) $(LIBS) pgmlimiar.o -o pgmlimiar

pgmmedia: pgmmedia.o
		$(COMPILER) $(FLAGS) $(LIBS) pgmmedia.o -o pgmmedia

pgmmediana: pgmmediana.o
		$(COMPILER) $(FLAGS) $(LIBS) pgmmediana.o -o pgmmediana

pgmnega: pgmnega.o
		$(COMPILER) $(FLAGS) $(LIBS) pgmmediana.o -o pgmlbp

pgmrotacao: pgmrotacao.o
		$(COMPILER) $(FLAGS) $(LIBS) pgmrotacao.o -o pgmrotacao

# Funções gerais
all: pgmlbp pgmlimiar pgmmedia pgmmediana pgmnega pgmrotacao

clean:
		-rm -f *.o

purge: clean
		-rm -f pgmlbp pgmlimiar pgmmedia pgmmediana pgmnega pgmrotacao