SHELL = /bin/sh
#
# Makefile para o Trabalho de construção da AVL -- Paulo Mateus Luza Alves
#

# Variavel com o nome do compilador utilizado pelo makefile
COMPILER = gcc

# Flags que vão ser utilizadas pelo compilador
# -g		Para trazer informação de debug com a compilação
# -Wall		Traz os warnigs de maneira verbosa
# -std=c90	Para utilizar a linguagem C90 na compilação
FLAGS = -g -std=c90 -Wall

myht: hash.o myht.o
		$(COMPILER) $(FLAGS) hash.o myht.o -o myht -lm

hash.o: hash.c
		$(COMPILER) $(FLAGS) -c hash.c

myht.o: myht.c
		$(COMPILER) $(FLAGS) -c myht.c

clean: 
		rm *.o myht