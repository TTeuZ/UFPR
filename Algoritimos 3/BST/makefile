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

bst: bst.o index.o
		$(COMPILER) $(FLAGS) bst.o index.o -o bst

bst.o: bst.c
		$(COMPILER) $(FLAGS) -c bst.c

index.o: index.c
		$(COMPILER) $(FLAGS) -c index.c

clean: 
		rm *.o bst