programName = crazyguitar

flags = -Wall -O3
objects = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
objects += $(patsubst %.cpp, %.o, $(wildcard Src/**/*.cpp))
objects += $(patsubst %.cpp, %.o, $(wildcard Src/Functionals/**/*.cpp))

all: $(programName)

$(programName): $(objects)
	g++ -o $(programName) $(objects) $(flags)

main.o: main.cpp
	g++ -c main.cpp $(flags)

%.o : %.cpp
	g++ -c $< -o $@ $(flags)

clean:
	rm -f *.o *.gch Src/**/*.o Src/Functionals/**/*.o  $(programName)