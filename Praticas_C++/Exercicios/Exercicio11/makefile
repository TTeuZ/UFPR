parametrosCompilacao = -Wall #-Wshadow
nomePrograma = exercicio11
objetos = main.o Console.o ConteudoMinistrado.o Curso.o Disciplina.o Pessoa.o SalaAula.o

all: $(nomePrograma)

$(nomePrograma): $(objetos)
	g++ -o $(nomePrograma) $(objetos) $(parametrosCompilacao)

main.o: main.cpp
	g++ -c main.cpp $(parametrosCompilacao)

%.o : %.cpp
	g++ -c $< -o $@ $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)
