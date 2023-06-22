CFLAGS =  -Wall -g -O2
OBJECTS = topology.o utils.o

all: toposort

toposort: $(OBJECTS) main.c
	$(CC) $(CFLAGS) $(OBJECTS) main.c -o toposort -l cgraph

topology.o: src/topology.c
	gcc -c src/topology.c

utils.o: src/utils.c
	gcc -c src/utils.c

clean:
	rm -rf *.o

purge: clean
	rm -rf toposort