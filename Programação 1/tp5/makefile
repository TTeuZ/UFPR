#
# Makefile para o TP4 -- Paulo Mateus Luza Alves
#

# Variavel com o nome do compilador utilizado pelo makefile
COMPILER = gcc

# Flags que vão ser utilizadas pelo compilador
# -g		Para trazer informação de debug com a compilação
# -Wall		Traz os warnigs de maneira verbosa
# -std=c90	Para utilizar a linguagem C90 na compilação
FLAGS = -g -std=c90 -Wall

teste: libconjunto.o testa.o 
		$(COMPILER) $(FLAGS) libconjunto.o testa.o -o testa
	
libconjunto.o: libconjunto.c
		$(COMPILER) $(FLAGS) -c libconjunto.c

teste.o: teste.c
		$(COMPILER) $(FLAGS) -c testa.c

clean: 
		rm *.o testa