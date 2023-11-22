parametrosCompilacao=-Wall -std=c++20
nomePrograma=aula

all: $(nomePrograma)

$(nomePrograma): main.o
	g++ -o $(nomePrograma) main.o $(parametrosCompilacao)

main.o: main.cpp
	g++ -c main.cpp $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)
