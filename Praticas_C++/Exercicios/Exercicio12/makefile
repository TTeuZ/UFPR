FLAGS = -Wall #-Wshadow
PROGRAM = Exercicio12

all: $(PROGRAM)

$(PROGRAM): main.o CircularList.hpp
	g++ -o $(PROGRAM) main.o CircularList.hpp $(FLAGS)

main.o: main.cpp
	g++ -c main.cpp $(FLAGS)
clean:
	rm -f *.o *.gch $(PROGRAM)
