BEGIN {FS = "[><]" ; print "Datas de debito:"}

/<DATA_DEBITO>/ { datadeb[$3] }

END { for(i in datadeb) print i}
