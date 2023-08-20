parametrosCompilacao=-Wall #-Wshadow
nomePrograma=exercicio6

all: $(nomePrograma)

$(nomePrograma): main.o Pessoa.o Disciplina.o Curso.o
	g++ -o $(nomePrograma) main.o Pessoa.o Disciplina.o Curso.o $(parametrosCompilacao)

main.o: main.cpp
	g++ -c main.cpp $(parametrosCompilacao)

Pessoa.o: Pessoa.hpp Pessoa.cpp
	g++ -c Pessoa.cpp $(parametrosCompilacao)

Disciplina.o: Disciplina.hpp Disciplina.cpp
	g++ -c Disciplina.cpp $(parametrosCompilacao)

Curso.o: Curso.hpp Curso.cpp
	g++ -c Curso.cpp $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)
