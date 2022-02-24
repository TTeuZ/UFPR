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

myavl: avl.o myavl.o
		$(COMPILER) $(FLAGS) avl.o myavl.o -o myavl

avl.o: avl.c
		$(COMPILER) $(FLAGS) -c avl.c

myavl.o: myavl.c
		$(COMPILER) $(FLAGS) -c myavl.c

clean: 
		rm *.o myavl