programName = exercicio21

flags = -Wall -O3
objects = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
objects += $(patsubst %.cpp, %.o, $(wildcard Exceptions/**/*.cpp))
objects += $(patsubst %.cpp, %.o, $(wildcard Src/**/*.cpp))

enums = $(wildcard Enums/*.hpp)

all: $(programName)

$(programName): $(objects)
	g++ -o $(programName) $(objects) $(enums) $(flags)

main.o: main.cpp
	g++ -c main.cpp $(flags)

%.o : %.cpp
	g++ -c $< -o $@ $(flags)

clean:
	rm -f *.o *.gch **/*.o Exceptions/**/*.o Src/**/*.o $(programName)
