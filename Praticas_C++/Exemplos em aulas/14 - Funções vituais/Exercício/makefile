parametrosCompilacao=-Wall #-Wshadow
nomeAula=aula

all: $(nomeAula)

$(nomeAula): main.o Ponto.o Trajeto.o
	g++ -o $(nomeAula) main.o Ponto.o Trajeto.o $(parametrosCompilacao)

main.o: main.cpp
	g++ -c main.cpp $(parametrosCompilacao)

Pessoa.o: Ponto.hpp Ponto.cpp
	g++ -c Ponto.cpp $(parametrosCompilacao)

Trajeto.o: Trajeto.hpp Trajeto.cpp
	g++ -c Trajeto.cpp $(parametrosCompilacao)
clean:
	rm -f *.o *.gch $(nomeAula)
