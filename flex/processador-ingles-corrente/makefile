all: procIngles procVerbos

procIngles: ingles.yy.c 
	gcc -o procIngles ingles.yy.c

ingles.yy.c: processador_ingles.l
	flex -o ingles.yy.c processador_ingles.l


procVerbos: verb.yy.c avl.c avl.h module.c module.h
	gcc -o procVerbos verb.yy.c avl.c avl.h module.c module.h

verb.yy.c: processador_verbos.l
	flex -o verb.yy.c processador_verbos.l
	
clean:
	rm -f procIngles procVerbos *.yy.c



