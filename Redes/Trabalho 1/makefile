clientName = Client
serverName = Server

flags = -Wall -O3
objects = $(patsubst %.cpp, %.o, $(wildcard exceptions/**/*.cpp))
objects += $(patsubst %.cpp, %.o, $(wildcard src/**/*.cpp))

enums = $(wildcard enums/*.hpp)

libs = -lboost_program_options

.PHONY: all client server clean purge

# ----------------------------------------------------------------------

all: $(clientName) $(serverName)

client: $(clientName)

server: $(serverName)

# ----------------------------------------------------------------------

$(clientName): client.o $(objects) 
	g++ -o $(clientName) client.o $(objects) $(enums) $(flags) $(libs)

$(serverName): server.o $(objects)
	g++ -o $(serverName) server.o $(objects) $(enums) $(flags) $(libs)

client.o: client.cpp
	g++ -c client.cpp $(flags)

server.o: server.cpp
	g++ -c server.cpp $(flags)

%.o : %.cpp
	g++ -c $< -o $@ $(flags)

# ----------------------------------------------------------------------

clean:
	rm -f *.o exceptions/**/*.o src/**/*.o

purge:
	rm -f *.o exceptions/**/*.o src/**/*.o $(clientName) $(serverName)