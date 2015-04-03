# AssemblerM
Um montador para o Assembly M.

##O que ele faz?
Realiza a montagem, a partir de um arquivo de texto de entrada, de um arquivo binário que
estará no formato compatível do processador conceitual CPUM.

##Procedimento de compilação do AssemblerM
Estando-se na pasta pai do projeto ("/AssemblerM"), realize o comando abaixo:

	$ make

##Procedimentos de utilização via Terminal
Através de um terminal de comando do Linux, observa-se o formato de entrada abaixo:

	$ ./bin/AssemblerM <NOME_DO_ARQUIVO>
	
	ENTRADA: 
		<NOME_DO_ARQUIVO> : é um arquivo de texto codificado no padrão ANSI ASCII.
	
Se a execução for bem-sucedida, então será gerado o arquivo binário para a CPUM.
