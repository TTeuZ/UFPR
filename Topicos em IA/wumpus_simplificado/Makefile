    CC     = gcc
    CFLAGS = 
    LFLAGS =

      PROG = wumpus 
      OBJS = bc.o wumpus-simplificado.o agente-wumpus.o

.PHONY: clean purge show all

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

all: plain
show:   CFLAGS += -DSHOW

plain show: $(PROG)

$(PROG) : % :  $(OBJS) %.o
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean:
	@rm -f *~ *.bak *.o

purge:   clean
	@rm -f *.o core a.out
	@rm -f $(PROG)

