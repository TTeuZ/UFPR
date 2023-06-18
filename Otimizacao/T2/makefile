CFLAGS= -Wall
OBJECTS= interface.o heroes.o optimize.o main.o

all: main

debug: CFLAGS += -DDEBUG -g 
debug: main

main: $(OBJECTS)
	gcc $(CFLAGS) $(OBJECTS) -o separa

interface.o:  ./src/interface.c
	gcc -c ./src/interface.c -o interface.o $(CFLAGS)

heroes.o:  ./src/heroes.c
	gcc -c ./src/heroes.c -o heroes.o $(CFLAGS)

optimize.o:  ./src/optimize.c
	gcc -c ./src/optimize.c -o optimize.o $(CFLAGS)

main.o: ./main.c
	gcc -c ./main.c -o main.o $(CFLAGS)

clean:
	rm -rf *.o

purge: clean
	rm -rf separa