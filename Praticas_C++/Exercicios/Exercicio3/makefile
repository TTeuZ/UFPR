FLAGS=-Wall #-Wshadow
PROGRAM=exercicio3

all: $(PROGRAM)

$(PROGRAM): main.o Rectangle.o
	g++ -o $(PROGRAM) main.o Rectangle.o $(FLAGS)

main.o: main.cpp
	g++ -c main.cpp $(FLAGS)

Rectangle.o: Rectangle.hpp Rectangle.cpp
	g++ -c Rectangle.cpp $(FLAGS)

clean:
	rm -f *.o *.gch $(PROGRAM)
