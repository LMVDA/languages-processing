CFLAGS=$(shell pkg-config --cflags glib-2.0)
LFLAGS=$(shell pkg-config --libs glib-2.0)
F=atomic
C=atoc

atomic : y.tab.c lex.yy.c
	cc $(CFLAGS) -c mapa_vars.c
	cc $(CFLAGS) -c auxiliarGramatica.c
	cc $(CFLAGS) -c y.tab.c
	cc -o $C y.tab.o mapa_vars.o auxiliarGramatica.o $(LFLAGS)
	@rm *.o 
	@rm y.tab.c 
	@rm y.tab.h 
	@rm y.output 
	@rm lex.yy.c 

y.tab.c : $F.yy
	yacc -d -v $F.yy

lex.yy.c : $F.l
	flex $F.l

clean:
	@rm -f $C
	@rm -f *.o 
	@rm -f y.tab.c 
	@rm -f y.tab.h 
	@rm -f y.output 
	@rm -f lex.yy.c 