SHELL = /bin/sh

all:
	as ./assembly/mallocBestFit.s -o mallocBestFit.o -g
	as ./assembly/mallocBestJuntando.s -o mallocBestJuntando.o -g
	gcc -c ./testes/avalia.c -g
	gcc -static avalia.o mallocBestFit.o -o best -g
	gcc -static avalia.o mallocBestJuntando.o -o juntando -g 

clear:
	rm  *.o

purge: clear
	rm best juntando