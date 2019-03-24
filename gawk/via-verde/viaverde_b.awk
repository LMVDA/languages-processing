BEGIN {FS = "[><]" ; print "Locais de saida: \n"}

/<SAIDA>/ { saidas[$3] }

END { for(i in saidas) print "\t" i}