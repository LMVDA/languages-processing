BEGIN {FS = "[><]"; print "Valor total do desconto (euros):" ; conta = 0;}

/<VALOR_DESCONTO>/ 							    { valor = $3;
											     split(valor, a, ",");
												  valor = a[1] "." a[2];
												  conta += valor;}
END { print conta " euros"}
