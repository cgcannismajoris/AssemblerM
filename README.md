# AssemblerM
Um montador para o Assembly M.

##O que ele faz?
Realiza a montagem, a partir de um arquivo de texto de entrada, de um arquivo binário que
estará no formato compatível do processador conceitual CPUM.

##Requisitos recomendados
* Sistema Operacional Unix-like ou GNU/Linux mais recente;
* GCC 4.9.1 ou superior;
* GNU Make 4.0 ou superior.

**Requisito opcional**
* Qt Creator 5.3.0 ou superior.

##Estrutura do projeto

A seguir, está disposto a organização básica do projeto AssemblerM.

	/AssemblerM				: pasta-pai do projeto	
		/data				: arquivos de entrada/saída e relativos ao projeto
		/src				: pasta de códigos-fonte
		/tools				: pasta de ferramentas
		.gitignore			: arquivo gitignore
		AssemblerM.pro 	    : árvore do projeto (Qt Creator)
		AssemblerM.pro.user : estruturação do projeto (Qt Creator)
		Makefile			: arquivo Makefile
		README.md			: arquivo LEIA-ME

> Obs.: como cortesia da casa, é oferecido um layout simples do projeto para o Qt Creator.

##Procedimento de compilação do AssemblerM
Estando-se na pasta pai do projeto ("/AssemblerM"), realize o comando abaixo:

	$ make

##Procedimentos de utilização via Terminal
Através de um terminal de comando do Linux, observa-se o formato de entrada abaixo:

	$ ./bin/AssemblerM <ARQUIVO_ENTRADA> <arg1> <arg2> ... <argn>
	
Entrada: 

	<ARQUIVO_ENTRADA>        : é um arquivo de texto codificado no padrão ANSI ASCII contendo o código a 
		                       ser montado.
	<arg1> <arg2> ... <argn> : os valores numéricos inteiros para configurar os valores iniciais
                               dos registradores de entrada declarados no cabeçalho do arquivo de texto
                               de entrada.
                               
Se a execução for bem-sucedida, então será gerado o arquivo binário para a CPUM.

##Sintaxe da linguagem M
A sintaxe da linguagem é semelhante às linguagens conceituais monolíticas.

###Sintaxe do Cabeçalho
Todo código-fonte deve ter, em seu cabeçalho (primeira linha), a declaração da máquina a ser utilizada.
	
	<NOME_DA_MÁQUINA>:<OUTREG_1>,<OUTREG_2>,...,<OUTREG_N><-<INREG_1>,<INREG_2>,...,<INREG_N>
	
Significado:
		
		<NOME_DA_MÁQUINA>                    : é o nome da máquina;
		<OUTREG_1>,<OUTREG_2>,...,<OUTREG_N> : é a declaração dos registradores de saída;
		<-                                   : seta que determina o significado dos registradores 
											   (será tratada a seguir);
		<INREG_1>,<INREG_2>,...,<INREG_N>    : é a declaração dos registradores de entrada. É esta lista de
										       registradores que receberá os valores numéricos inteiros de 
										       entrada descritos anteriormente;
		
A seta descrita acima (<-), pode ser invertida, ou seja, escrita como "->". Todavia, a ordem dos registradores 
também deverá ser alterada, isto é:
		
	<NOME_DA_MÁQUINA>:<INREG_1>,<INREG_2>,...,<INREG_N>-><OUTREG_1>,<OUTREG_2>,...,<OUTREG_N>
		
Em resumo, a seta indica o sentido do fluxo do processamento descrito nas linhas subsequentes.
Tal fluxo pode ser dar como:
			
	1. Os registradores de entrada recebem os dados de entrada;
	2. Os dados armazenados são processados seguindo a lógica descrita nas linhas subsequentes 
	   ao cabeçalho;
	3. Os registradores de saída armazenam os resultados do processamento.

É importante ressaltar que o resultado do processamento só será armazenado nos registradores de saída, caso a lógica
descrita no código viabilize este transporte.
A utilização de todos os registradores declarados fica a cargo do usuário, mas a tentativa de uso de registradores não 
declarados gera erro de montagem do programa.

###Sintaxe das Instruções
Toda instrução deve possuir um rótulo, um identificador de operação/teste, um registrador a ser utilizado e o(s)
endereço(s) da próxima instrução.
	
Existem duas operações e um teste. São eles:

* **INC**	: incrementa um determinado registrador em uma unidade;
* **DEC**	: decrementa um determinado registrador em uma unidade;
* **ZERO**	: testa se um registrador é igual a 0.

As instruções de operação seguem as seguintes sintaxes:
	
	1. <RÓTULO>: faca <OPERACAO> <REGISTRADOR> va_para <RÓTULO_DESTINO>
	2. <RÓTULO>: <OPERACAO> <REGISTRADOR> <RÓTULO_DESTINO>
	
Para ambos os casos, seguem os seguintes significados:
	
	<RÓTULO>         : Rótulo da instrução;
	<OPERACAO>       : Operação a ser realizada (INC ou DEC);
	<REGISTRADOR>    : Registrador a ser utilizado na operação;
	<RÓTULO_DESTINO> : Rótulo da próxima instrução.
		
A instrução de teste pode seguir uma das possibilidades:

	1. <RÓTULO>: se zero <REGISTRADOR> entao <RÓTULO_DESTINO_VERDADE> senao  <RÓTULO_DESTINO_FALSO>
	2. <RÓTULO>: faca zero <REGISTRADOR> va_para <RÓTULO_DESTINO_VERDADE> <RÓTULO_DESTINO_FALSO>
	3. <RÓTULO>: zero <REGISTRADOR> <RÓTULO_DESTINO_VERDADE> <RÓTULO_DESTINO_FALSO>
	
Para todos os casos, há os seguintes significados:

	<RÓTULO>                 : Rótulo da instrução;
	<REGISTRADOR>            : Registrador a ter seu valor verificado;
	<RÓTULO_DESTINO_VERDADE> : Rótulo da próxima instrução caso o teste retornar verdade.
	<RÓTULO_DESTINO_FALSO>   : Rótulo da próxima instrução caso o teste retornar falso.

Com exceção dos rótulos e nomes atribuídos aos registradores, a linguagem não é case sensitive ("sensível ao caso").

####Determinando o fim do programa
O fim do programa pode ser determinado referenciando um rótulo inexistente no rótulo de destino da instrução.

###Exemplo de Código

O código a seguir transfere o valor contido no registrador b para o registrador a, para valores maiores do que 0.
```
M:a<-b
r1: faca inc a va_para r2
r2: faca dec b va_para r3
r3: se zero b entao r5 senao r1
```
Atenta-se ao fato de que existe mais de uma possibilidade de escrita das instruções. O código a seguir é 
equivalente ao anterior:
```
M:a<-b
r1: inc a r2
r2: dec b r3
r3: zero b r5 r1
```
Outra escrita equivalente é:
```
M:a<-b
r1: INC a va_PARA r2
r2: Faca DEC b VA_para r3
r3: se ZERO b Va_PaRa r5 r1
```
Uma observação importante, é que o rótulo "r5", referenciado na instrução rotulada "r3", não existe. Logo, 
se o teste "zero b" resultar em verdade, o programa será finalizado.
Como boa prática de programação, recomenda-se seguir um único padrão de escrita, visando uma maior facilidade de 
entendimento humano do código.



