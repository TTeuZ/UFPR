SHELL = /bin/sh

FLAGS = -g -Wall

OBJECTS = escalona.o escalation.o schedule.o

all: escalona

clean:
		-rm -f *.o

purge: clean
		-rm -f escalona

escalona: $(OBJECTS)
	$(CC) $(OBJECTS) -o escalona $(FLAGS)

escalona.o: escalona.c
		$(CC) -c escalona.c $(FLAGS)

schedule.o: schedule.c
		$(CC) -c schedule.c $(FLAGS)

escalation.o: escalation.c
		$(CC) -c escalation.c $(FLAGS)