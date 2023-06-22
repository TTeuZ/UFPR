CFLAGS =  -Wall -g -O2
OBJECTS = topology.o

all: toposort

toposort: $(OBJECTS) main.c
	$(CC) $(CFLAGS) $(OBJECTS) main.c -o toposort -l cgraph

topology.o: src/topology.c
	gcc -c src/topology.c

clean:
	rm -rf *.o

purge: clean
	rm -rf toposort