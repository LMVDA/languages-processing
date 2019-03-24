BEGIN {FS = "[><]"; print "Gasto Mensal Parques(em euros)" ; contaId = 0; contaTotal = 0;}

/<MATRICULA>/ {matricula = $3;}
/<IMPORTANCIA>/                                 { valor = $3;}
/<TIPO>/ && $3 =="Parques de estacionamento"    { split(valor, a, ",");
                                                  valor = a[1] "." a[2];
                                                  contaId += valor;
                                                }
/<\/IDENTIFICADOR>/ { print matricula " \t\t" contaId;
                      contaTotal += contaId;
                      contaId = 0;
                    }
END { print "Total \t\t\t" contaTotal;}