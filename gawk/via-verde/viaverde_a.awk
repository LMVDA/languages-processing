BEGIN {FS = "[><]" ; print "Data\t\tNr Ocorrencias"}

/<DATA_ENTRADA>/ && $3!="null"		{ entradasDia[$3]++;}

END { for(dia in entradasDia) {print dia " :\t\t " entradasDia[dia] }}





