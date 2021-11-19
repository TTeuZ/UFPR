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


testa: libconjunto.o testa_conjunto.o liblista.o testa_lista.o libfila.o testa_fila.o
		$(COMPILER) $(FLAGS) libconjunto.o testa_conjunto.o -o testa_conjunto
		$(COMPILER) $(FLAGS) liblista.o testa_lista.o -o testa_lista
		$(COMPILER) $(FLAGS) libfila.o testa_fila.o -o testa_fila

# make para o teste de conjunto
testa_conjunto: libconjunto.o testa_conjunto.o 
		$(COMPILER) $(FLAGS) libconjunto.o testa_conjunto.o -o testa_conjunto
	
libconjunto.o: libconjunto.c
		$(COMPILER) $(FLAGS) -c libconjunto.c

testa_conjunto.o: testa_conjunto.c
		$(COMPILER) $(FLAGS) -c testa_conjunto.c
# make para o teste de conjunto

# make para o teste de lista
testa_lista: liblista.o testa_lista.o 
		$(COMPILER) $(FLAGS) liblista.o testa_lista.o -o testa_lista
	
liblista.o: liblista.c
		$(COMPILER) $(FLAGS) -c liblista.c

testa_lista.o: testa_lista.c
		$(COMPILER) $(FLAGS) -c testa_lista.c
# make para o teste de lista

# make para o teste de fila
testa_fila: libfila.o testa_fila.o 
		$(COMPILER) $(FLAGS) libfila.o testa_fila.o -o testa_fila
	
libfila.o: libfila.c
		$(COMPILER) $(FLAGS) -c libfila.c

testa_fila.o: testa_fila.c
		$(COMPILER) $(FLAGS) -c testa_fila.c
# make para o teste de fila

clean: 
		rm *.o testa_conjunto testa_lista testa_fila

clean_conjunto: 
		rm *.o testa_conjunto 

clean_lista: 
		rm *.o testa_lista

clean_fila: 
		rm *.o testa_fila
