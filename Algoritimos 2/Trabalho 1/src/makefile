MODULOS = biblioteca \
	selecao \
	insercao \
	particiona \
	quicksort \
	quicksort-insercao \
	quicksort-mediana

OBJETOS = teste.o $(addsuffix .o,$(MODULOS))

.PHONY : all clean

all : teste
	./$<

teste : $(OBJETOS)

clean : 
	$(RM) $(OBJETOS)
