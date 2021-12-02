SHELL = /bin/sh
#
# Makefile para o T2 -- Paulo Mateus Luza Alves
#

# Variavel com o nome do compilador utilizado pelo makefile
COMPILER = gcc

# Flags que vão ser utilizadas pelo compilador
# -g		Para trazer informação de debug com a compilação
# -Wall		Traz os warnigs de maneira verbosa
# -std=c90	Para utilizar a linguagem C90 na compilação
FLAGS = -g -std=c90 -Wall

mundo: libconjunto.o libfila.o liblef.o eventos.o mundo.o 
		$(COMPILER) $(FLAGS) libconjunto.o libfila.o liblef.o eventos.o mundo.o -lm -o mundo

libconjunto.o: libconjunto.c
		$(COMPILER) $(FLAGS) -c libconjunto.c

libfila.o: libfila.c
		$(COMPILER) $(FLAGS) -c libfila.c

liblef.o: liblef.c
		$(COMPILER) $(FLAGS) -c liblef.c

eventos.o: eventos.c
		$(COMPILER) $(FLAGS) -c eventos.c

mundo.o: mundo.c
		$(COMPILER) $(FLAGS) -c mundo.c

clean: 
		rm *.o mundo

