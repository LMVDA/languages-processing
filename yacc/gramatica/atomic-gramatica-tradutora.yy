Atomic		-> Funcoes Start
Funcoes		-> Funcoes Funcao
			|

Funcao		-> VOID ID '('')' '{' Body '}'
			| ATOM ID '('')' '{' Body '}'

Body		-> ListaDeclars Insts Return
	  		
ListaDeclars -> ListaDeclars LinhaDeclar
			|

LinhaDeclar -> ATOM Declars ';'

Declars ->  Declars ',' Declar   
		| Declar

Declar -> ID
		| Atribuicao
		| ID '[' NUM ']'
		| ID '[' NUM ']' '[' NUM ']'


Insts -> Insts Inst
       |

Inst -> Condicional
      | Ciclica
      | Atribuicao
      | Invocacao
      | Leitura
      | Escrita

Condicional -> IF '(' Condicao ')' '{' Insts '}'
		 	|  IF '(' Condicao ')' '{' Insts '}' ELSE '{' Insts '}'


Ciclica -> WHILE '(' Condicao ')' '{' Insts '}'

Atribuicao -> ID AT Exp
           |  ID '[' NUM ']' AT Exp
           |  ID '[' NUM ']' '[' NUM ']' AT Exp


Invocacao -> ID '(' ')' ';'

Leitura -> ID AT READ '(' ')' ';'

Escrita -> PRINT '(' Exp ')' ';'
        |  PRINT '(' STRING ')' ';'

Condicao -> Condicao AND Condicao
		 | Condicao OR Condicao
		 | '!' Condicao
		 |	Exp '<' Exp
 		 |  Exp '>' Exp 
 		 |  Exp LEQ Exp 
 		 |  Exp GEQ Exp 
 		 |  Exp DIF Exp 
 		 |  Exp EQU Exp 
 		 |  Exp AND Exp 
 		 |  Exp OR Exp 
 		 |  '!' Exp 


Exp -> Termo
     | Exp '+' Termo
     | Exp '-' Termo


Termo -> Fator
	  |  Termo '*' Fator
	  |  Termo '/' Fator
	  |  Termo '%' Fator


Fator -> NUM
	  |  ID
	  |  ID '(' ')'
	  |  READ '(' ')'
      |  ID '[' NUM ']' 
      |  ID '[' NUM ']' '[' NUM ']'



Return -> RETURN Exp ';'
	   | 