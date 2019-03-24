BEGIN { 
	FS = "[><]";
	path = "http://npmp.epl.di.uminho.pt/images/galleryInterviews/" 

	templateDataInicio = "<li class='work'> <input class='radio' id='work5' name='works' type='radio' checked> <div class='relative'> <span class='date'>%s</span> <span class='circle'></span> </div> <div class='content'>";
	templateDataFim = "</div> </li>";

	templateFotoF = "<p>%s - %s</p> <img src='%s' alt=''/>";
	
	cabecalho = "<!DOCTYPE html> <html> <head> <title>Album</title> <style>@import url(http://fonts.googleapis.com/css?family=Noto+Sans); body { max-width: 1200px; margin: 0 auto; padding: 0 5%; font-size: 100%; font-family: 'Noto Sans', sans-serif; color: #eee9dc; background: #48b379; } h2 { margin: 3em 0 0 0; font-size: 1.5em; letter-spacing: 2px; text-transform: uppercase; } /* ------------------------------------- * timeline * ------------------------------------- */ #timeline { list-style: none; margin: 50px 0 30px 120px; padding-left: 30px; border-left: 8px solid #eee9dc; } #timeline li { margin: 40px 0; position: relative; } #timeline p { margin: 0 0 15px; } .date { margin-top: -10px; top: 50%; left: -158px; font-size: 0.95em; line-height: 20px; position: absolute; } .circle { margin-top: -10px; top: 50%; left: -44px; width: 10px; height: 10px; background: #48b379; border: 5px solid #eee9dc; border-radius: 50%; display: block; position: absolute; } .content { max-height: 20px; padding: 10px 20px 0; border-color: transparent; border-width: 2px; border-style: solid; border-radius: 0.5em; position: relative; } .content:before, .content:after { content: ''; width: 0; height: 0; border: solid transparent; position: absolute; pointer-events: none; right: 100%; } .content:before { border-right-color: inherit; border-width: 20px; top: 50%; margin-top: -20px; } .content:after { border-right-color: #48b379; border-width: 17px; top: 50%; margin-top: -17px; } .content p { max-height: 0; color: transparent; text-align: center; word-break: break-word; hyphens: auto; overflow: hidden; } label { font-size: 1.3em; position: absolute; z-index: 100; cursor: pointer; top: 20px; transition: transform 0.2s linear; } .radio { display: none; } .radio + .relative label { cursor: auto; transform: translateX(42px); } .radio + .relative .circle { background: #f98262; } .radio ~ .content { max-height: inherit; border-color: #eee9dc; margin-right: 20px; transform: translateX(20px); transition: max-height 0.4s linear, border-color 0.5s linear, transform 0.2s linear; } .radio ~ .content p { max-height: 200px; color: #eee9dc; transition: color 0.3s linear 0.3s; } .radio ~ .content img { max-width: 100%; max-height: 150px; display: block; margin-left: auto; margin-right: auto; padding-bottom: 10px; color: #eee9dc; transition: color 0.3s linear 0.3s; } /* ------------------------------------- * mobile phones (vertical version only) * ------------------------------------- */ @media screen and (max-width: 767px) { #timeline { margin-left: 0; padding-left: 0; border-left: none; } #timeline li { margin: 50px 0; } label { width: 85%; font-size: 1.1em; white-space: nowrap; text-overflow: ellipsis; overflow: hidden; display: block; transform: translateX(18px); } .content { padding-top: 45px; border-color: #eee9dc; } .content:before, .content:after { border: solid transparent; bottom: 100%; } .content:before { border-bottom-color: inherit; border-width: 17px; top: -16px; left: 50px; margin-left: -17px; } .content:after { border-bottom-color: #48b379; border-width: 20px; top: -20px; left: 50px; margin-left: -20px; } .content p { font-size: 0.9em; line-height: 1.4; } .circle, .date { display: none; } }</style> </head> <body> <h1>Album de fotografias - Cronologia</h1> <ul id='timeline'>";
	
	print cabecalho > "index.html";
	end = "</ul></body></html>";
}

/<foto /	{	split($2, a, "\"");
				nomeFoto = a[2] }

/<onde/ 	{	ondeNormalizado = normalizarTexto($3); }

/<quando / 	{	split($2, dataFoto, "\"")
				quando = dataFoto[2] }

/<quem>/	 {	
				if (quando != null) {
					nomeNormalizado = normalizarTexto($3);

					if (ondeNormalizado != null) locais[ondeNormalizado] = ondeNormalizado;

					conteudoFoto = quando ";" nomeFoto ";" nomeNormalizado ";" ondeNormalizado

					if(datas[quando] != null) datas[quando] = datas[quando] "@" conteudoFoto;
					else datas[quando] = conteudoFoto;	
				}

				quando = null;			
}

END{
	asort(datas);

	for(data in datas) {

		split(datas[data], fotos, "@");

		for (i in fotos) {
			split(fotos[i], campos, ";");

			quando = campos[1];
			nomeFoto = campos[2];
			quem = campos[3];
			onde = campos[4];

			if (i == 1) printf(templateDataInicio, quando) > "index.html";

			printf(templateFotoF, quem, onde, path nomeFoto) > "index.html" 
		}

		print templateDataFim > "index.html";
	}

	print "Lista de locais fotografados:"
	for (local in locais) print "\t" local

	print end > "index.html";
}


function normalizarTexto(textoComEspacos) {
	tamanho = split(textoComEspacos, textoSemEspacos, " ");

    for (i = 1; i <= tamanho; i++) {
    	if (i == 1) result = textoSemEspacos[i];
    	else result = result " " textoSemEspacos[i];
    }
    
    return result
}