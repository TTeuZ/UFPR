SHELL = /bin/sh

FLAGS = -g -Wall

OBJECTS = escalona.o escalation.o graphs.o serializable.o equivalentView.o utils.o schedule.o

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

graphs.o: graphs.c
		$(CC) -c graphs.c $(FLAGS)

serializable.o: serializable.c
		$(CC) -c serializable.c $(FLAGS)

equivalentView.o: equivalentView.c
		$(CC) -c equivalentView.c $(FLAGS)

utils.o: utils.c
		$(CC) -c utils.c $(FLAGS)