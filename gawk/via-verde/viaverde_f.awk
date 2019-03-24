BEGIN { FS = "[><]"; 
        valorIdPortagens = 0; 
        valorIdParques = 0; 
        valorTotalIdParques = 0; 
        valorTotalIdPortagens = 0
        nrOcorrenciasIdPortagens = 0;
        nrOcorrenciasTotalIdPortagens = 0; 
        nrOcorrenciasIdParques = 0;
        nrOcorrenciasTotalIdParques=0; 
        nrOcorrenciasTotal = 0; 
        print "Media de Pagamento"; 
        print"\t\t\t\t\Portagens(euros/mes)\t\tParques(euros/mes)";
    }

/<MATRICULA>/ {matricula = $3;}

/<IMPORTANCIA>/ {importancia = $3;}

/<TIPO>/ && $3 =="Portagens" { split(importancia, a,",");
                               importancia = a[1] "." a[2];
                               valorIdPortagens += importancia;
                               nrOcorrenciasIdPortagens++;
                             }

/<TIPO>/ && $3 =="Parques de estacionamento" { split(importancia, a,",");
                                               importancia = a[1] "." a[2];
                                               valorIdParques += importancia;
                                               nrOcorrenciasIdParques++;   
                                             }
                                            
/<\/IDENTIFICADOR>/ {   printf matricula "\t\t\t %.2f \t\t\t\t %.2f\n", (valorIdPortagens/nrOcorrenciasIdPortagens), (valorIdParques/nrOcorrenciasIdParques);
                        
                        valorTotalIdPortagens += valorIdPortagens;
                        nrOcorrenciasTotalIdPortagens += nrOcorrenciasIdPortagens;

                        valorTotalIdParques += valorIdParques;
                        nrOcorrenciasTotalIdParques += nrOcorrenciasIdParques;

                        valorTotal += valorIdPortagens+valorIdParques;
                        nrOcorrenciasTotal += nrOcorrenciasIdPortagens + nrOcorrenciasIdParques;

                        valorIdPortagens = 0;
                        valorIdParques = 0
                        nrOcorrenciasIdPortagens = 0;
                        nrOcorrenciasIdParques = 0;
                    }


END { printf "Media Parcial\t\t\t %.2f \t\t\t\t %.2f\n", (valorTotalIdPortagens/nrOcorrenciasTotalIdPortagens), (valorTotalIdParques/nrOcorrenciasTotalIdParques); 
      printf "\nMedia Total: %.2f euros/mes\n", (valorTotal/nrOcorrenciasTotal);}