SHELL = /bin/sh

LIKWID_C = -DLIKWID_PERFMON -I${LIKWID_INCLUDE}
LIKWID_O = -L${LIKWID_LIB} -llikwid

FLAGS = -g -Wall -O3 -mavx2 -march=native $(LIKWID_C)
LIBS = -lm $(LIKWID_O)

# Funções gerais
all: invmat

clean: 
	-rm -f *.o

purge: clean
	-rm -f invmat

# Construção do executavel
invmat: invmat.o parser.o matrix.o utils.o error.o steps.o methods.o
	$(CC) $(FLAGS) invmat.o parser.o matrix.o utils.o error.o steps.o methods.o -o invmat $(LIBS)
	
# Construção dos Objetos
invmat.o: invmat.c
	$(CC) $(FLAGS) -c invmat.c

parser.o: parser.c
	$(CC) $(FLAGS) -c parser.c

matrix.o: matrix.c
	$(CC) $(FLAGS) -c matrix.c

utils.o: utils.c
	$(CC) $(FLAGS) -c utils.c

error.o: error.c
	$(CC) $(FLAGS) -c error.c

steps.o: steps.c
	$(CC) $(FLAGS) -c steps.c

methods.o: methods.c
	$(CC) $(FLAGS) -c methods.c
