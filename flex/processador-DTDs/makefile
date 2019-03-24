CFLAGS=$(shell pkg-config --cflags glib-2.0)
LFLAGS=$(shell pkg-config --libs glib-2.0)
INSTALL_PATH?=/usr/local
MAN_PATH=/usr/share/man/man1
F=procDTD

$F: procDTD.fl lex.yy.c
	cc $(CFLAGS) -c module.c
	cc -g $(CFLAGS) -c lex.yy.c
	cc -o $F lex.yy.o module.o $(LFLAGS)

lex.yy.c : $F.fl
	flex $F.fl

clean :
	rm -f *.o
	rm -f lex.yy.c
	rm -f $F