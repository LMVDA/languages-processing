BEGIN { 
    FS = "[><]"; 
    print "Parques "; 
    tempoMinutosId = 0;
    tempoMinutosTotal = 0;
}
/<MATRICULA>/ {matricula = $3;}

/<HORA_ENTRADA>/                               { horaentrada = $3;}

/<HORA_SAIDA>/                                  { horasaida = $3;}

/<TIPO>/ && $3 =="Parques de estacionamento"    { split(horaentrada, a, ":");
                                                  minutosEntrada = a[1]*60 + a[2];
                                                  split(horasaida, b, ":");
                                                  minutosSaida = b[1]*60 + b[2];
                                                  tempoMinutosId += (minutosSaida - minutosEntrada);
                                                  }

/<\/IDENTIFICADOR>/  { print matricula "\t\t" int(tempoMinutosId/60) " horas e " (tempoMinutosId%60) " minutos";
                       tempoMinutosTotal += tempoMinutosId;
                       tempoMinutosId = 0;
        
                     }
END {
    print "Total\t\t\t" int(tempoMinutosTotal/60) " horas e " (tempoMinutosTotal%60) " minutos";
}
