FLAGS := $(shell pkg-config --cflags --libs glib-2.0) -O2

compile: namedEntities.l utils.h utils.c
	flex namedEntities.l
	gcc -o namedEntities utils.c lex.yy.c $(FLAGS)

exemplo:
	./namedEntities exemplo-Enamex.xml exemplo.html

clean:
	rm -f *.yy.c namedEntities
