CFLAGS = -Wall
OBJECTS = linear_program.o utils.o

all: producao

producao: $(OBJECTS)
	gcc $(CFLAGS) $(OBJECTS) main.c -o producao

linear_program.o: src/linear_program.c
	gcc -c src/linear_program.c

utils.o: src/utils.c
	gcc -c src/utils.c

clean:
	rm -rf *.o

purge: clean
	rm -rf producao