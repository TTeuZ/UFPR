objects = $(patsubst %.c, %.o, $(wildcard src/*.c))
flags = -ll -ly -lc

.PHONY: compiler clean purge removeMEPA

# ----------------------------------------------------------------------

compiler: lex.yy.c compiler.tab.c $(objects) src/compiler.h
	gcc lex.yy.c compiler.tab.c $(objects) -o compiler $(flags)

lex.yy.c: compiler.l src/compiler.h
	flex compiler.l

compiler.tab.c: compiler.y src/compiler.h
	bison compiler.y -d -v

%.o: %.c
	gcc -c $< -o $@

# ----------------------------------------------------------------------

clean:
	rm -f compiler.tab.* lex.yy.c compiler.output src/*.o

purge:
	rm -f compiler.tab.* lex.yy.c compiler.output src/*.o compiler

removeMEPA:
	rm MEPA