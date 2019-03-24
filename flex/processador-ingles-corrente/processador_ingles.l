%{

#include <stdio.h>
#include <string.h>

%}

%x UNIDADE

%%

ain(’|')t		{ ECHO; }
gonna			{ printf( "going to" ); }
gotta			{ printf( "got to" ); }
shan(’|')t		{ printf( "shall not" ); }
won(’|')t	    { printf( "will not" ); }
y(’|')all		{ printf( "you all" ); }


n(’|')t 	{ printf( " not" ); }
(’|')ve		{ printf( " have" ); }
(’|')d		{ printf( " would" ); }
(’|')ll		{ printf( " will" ); }
(’|')s		{ printf( " is" ); }
(’|')m		{ printf( " am" ); }
(’|')re		{ printf( " are" ); }


[0-9]+\ *			{ ECHO;
					  BEGIN UNIDADE; }

<UNIDADE>m			{ printf( "metres" ); 
					  BEGIN INITIAL; }

<UNIDADE>dm			{ printf( "decimetres" ); 
					  BEGIN INITIAL; }

<UNIDADE>cm			{ printf( "centimetres" ); 
					  BEGIN INITIAL; }

<UNIDADE>mm			{ printf( "millimetres" ); 
					  BEGIN INITIAL; }

<UNIDADE>nm			{ printf( "nanometres" ); 
					  BEGIN INITIAL; }

<UNIDADE>g 			{ printf( "grams" ); 
					  BEGIN INITIAL; }

<UNIDADE>mg			{ printf( "milligrams" ); 
					  BEGIN INITIAL; }

<UNIDADE>kg			{ printf( "kilograms" ); 
					  BEGIN INITIAL; }

<UNIDADE>(s|sec)	{ printf( "seconds" ); 
					  BEGIN INITIAL; }

<UNIDADE>ms			{ printf( "milliseconds" ); 
					  BEGIN INITIAL; }

<UNIDADE>ns			{ printf( "nanoseconds" ); 
					  BEGIN INITIAL; }

<UNIDADE>min 		{ printf( "minutes" ); 
					  BEGIN INITIAL; }

<UNIDADE>h 			{ printf( "hours" ); 
					  BEGIN INITIAL; }

<UNIDADE>ml 		{ printf( "miles" ); 
					  BEGIN INITIAL; }

<UNIDADE>(in|\″)	{ printf( "inches" ); 
					  BEGIN INITIAL; }

<UNIDADE>(ft|\′)	{ printf( "feet" ); 
					  BEGIN INITIAL; }

<UNIDADE>yd 		{ printf( "yards" ); 
					  BEGIN INITIAL; }

<UNIDADE>ac			{ printf( "acres" ); 
					  BEGIN INITIAL; }

<UNIDADE>gal		{ printf( "gallons" ); 
					  BEGIN INITIAL; }

<UNIDADE>hp			{ printf( "horsepower" ); 
					  BEGIN INITIAL; }

<UNIDADE>gr 		{ printf( "grains" ); 
					  BEGIN INITIAL; }

<UNIDADE>oz 		{ printf( "ounces" ); 
					  BEGIN INITIAL; }

<UNIDADE>lb			{ printf( "pounds" ); 
					  BEGIN INITIAL; }

<UNIDADE>mph		{ printf( "miles per hour" ); 
					  BEGIN INITIAL; }

<UNIDADE>tsp		{ printf( "teaspoons" ); 
					  BEGIN INITIAL; }

<UNIDADE>tbsp		{ printf( "tablespoons" ); 
					  BEGIN INITIAL; }

.|\n 				{ ECHO; }

%%

int yywrap(){

	return 1;
}

int main(){

	yylex();
	return 0;

}