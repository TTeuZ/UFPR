SHELL = /bin/sh

all:
	as ./assembly/mallocBestFit.s -o mallocBestFit.o -g
	as ./assembly/mallocFirstFit.s -o mallocFirstFit.o -g
	as ./assembly/mallocNextFit.s -o mallocNextFit.o -g
	as ./assembly/mallocWorstFit.s -o mallocWorstFit.o -g
	gcc -c ./testes/testBest.c -g
	gcc -c ./testes/testFirst.c -g
	gcc -c ./testes/testNext.c -g
	gcc -c ./testes/testWorst.c -g
	gcc -static testBest.o mallocBestFit.o -o best -g
	gcc -static testFirst.o mallocFirstFit.o -o first -g 
	gcc -static testNext.o mallocNextFit.o -o next -g 
	gcc -static testWorst.o mallocWorstFit.o -o worst -g 

clear:
	rm  *.o

purge: clear
	rm best first next worst