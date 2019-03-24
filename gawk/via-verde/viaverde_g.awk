BEGIN {FS = "[><]" ; print "Operador\t\t\t\t\tNr Ocorrencias"}

/<OPERADOR>/    		{ operadores[$3]++;}

END { for(op in operadores) {print op "\t\t\t\t\t" operadores[op] }}