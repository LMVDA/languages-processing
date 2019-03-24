BEGIN {FS = "[><]" ; print "Gasto Mensal (em euros)";}

/<IDENTIFICADOR/ { split($2, a, " ");
                    id = a[2];
                 }
/<MATRICULA>/ {matricula = $3;}

/<\/IDENTIFICADOR>/ {
                        id = null;
                    }

/<TOTAL>/        {
                    valor = $3;
                    if (id==null)
                        print  "Total \t\t\t" valor;
                    else
                        print matricula " \t\t" valor;
                 }
END{ }