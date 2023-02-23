# RGPS - Trabalho 1 de Criptografia
## Feito por Gabriel Pontarolo e Rodrigo Soffner
 
### Compilação e execução:
 
**É necessária a instalação da biblioteca GMP (https://gmplib.org/)**
 
* Comando **make** faz a compilação dos fontes
* **./rgps [-k chave] [-d] [-c] [-v]**
 * **-k** indica a chave para criptografia. Consiste de uma palavra composta de letras/números/símbolos de no mínimo 3 caracteres. Caso não especificada, a chave padrão utilizada é *nerfthis*;
 * **-d** faz a descriptografia do texto cifrado;
 * **-c** faz a criptografia do texto claro;
 * **-v** utiliza o algoritmo de vigenere diferente;
 * A entrada do texto é feita pela entrada padrão **stdin** e a saída pela saída padrão **stdout**
 * O algoritmo trabalha apenas com os caracteres entre *32* e *126* da tabela *ASCII*. Outros caracteres serão substituídos por *'X'*;
 
## Sobre:
 
* Cifra de substituição composta por duas etapas executadas em sequência:
 * Criptografia feita a partir de uma iteração do SBCS314 seguida por 5 iterações do Vigenere
 * Decriptografia feita apatir de 5 iterações do Vigenre seguida por uma iteração do SBCS314
 
### SBCS314
 
* Separa o texto claro em blocos de até 128 bytes e executa 16 rodadas dividas em duas partes:
 * Cada caracter do texto é passado por uma caixa de substituição construída a partir da **chave** e um campo finito de tamanho 95 que representa os caracteres entre as posições 32 e 126 da tabela *ASCII*. A chave é posicionada antes do início da tabela, são retiradas as repetições e então cada símbolo é mapeado no seu inverso multiplicativo dentro do campo finito.
   * **Exemplo:**
       A primeira linha da tabela representa o caracter de entrada na tabela, a segunda o valor **w** atribuído ao caracter, a terceira o inverso multiplicativo **w'** dentro do GF(95), ou seja, **((w \* w') mod 96) == 1** (os valores que não possuem inverso dentro do campo foram mapeados para eles mesmos), e a quarta o caracter resultante.
 
       | n | e | r  | f  | t  | h | i  | s  |    | !  | "  | #  | $  | ... | {  | \| | }  | ~  |
       |---|---|----|----|----|---|----|----|----|----|----|----|----|-----|----|----|----|----|
       | 0 | 1 | 2  | 3  | 4  | 5 | 6  | 7  | 8  | 9  | 10 | 11 | 12 | ... | 91 | 92 | 93 | 94 |
       | 0 | 1 | 48 | 32 | 24 | 5 | 16 | 68 | 12 | 74 | 10 | 26 | 8  | ... | 71 | 63 | 47 | 94 |
       | n | e | H  | 8  | 0  | h | (  | \  | $  | b  | "  | 2  |    | ... | _  | W  | G  | ~  |
 * Após isso, a **chave** é convertida em um inteiro utilizando o valor do caracter: *nerfthis* -> *{110, 101, 114, 102, 116, 104, 105, 115}* -> *110101114102116104105115*, e os primeiros 7 dígitos são selecionados: 1101011. Com os dois primeiros dígitos (11), é feita uma exponenciação dos 400 primeiros dígitos de *pi*. Os 5 seguintes (01011) são multiplicados por 2 elevado ao número da rodada atual e utilizados como um deslocamento na posição dos primeiros dígitos da potência de *pi*. A partir disso, cada um dos dígitos é somado ao caracter correspondente do texto claro, fazendo uma "rotação" no alfabeto
   * **Exemplo:**
       Para a rodada 0 temos: *3141592653... ^ (11 \* 2^0) = 294204017974...* . É feito o deslocamento na posição dos dígitos obtendo-se *8515051051238...* . Finalmente, aplicando ao texto, temos:
       | L  | o   | r   | e   | m   |    | i   | p   | s   | u   | m   |    | d   | o   | l   | o   | r   |    | s   |
       |----|-----|-----|-----|-----|----|-----|-----|-----|-----|-----|----|-----|-----|-----|-----|-----|----|-----|
       | 76 | 111 | 114 | 101 | 109 | 32 | 105 | 112 | 115 | 117 | 109 | 32 | 100 | 111 | 108 | 111 | 114 | 32 | 115 |
       | 8  | 5   | 1   | 5   | 0   | 5  | 1   | 0   | 5   | 1   | 2   | 3  | 8   | 2   | 4   | 0   | 0   | 8  | 0   |
       | T  | t   | s   | k   | m   | %  | j   | p   | x   | v   | o   | #  |  l  | q   | p   | o   | r   | (  | s   |
 
       Onde a primeira linha da tabela consiste do texto claro, a segunda os valores na tabela *ASCII*, a terceira o dígito correspondente da potência de pi e a quarta o caráter resultante da soma.
 
* Essas duas etapas são executadas em sequência uma vez em cada uma das 16 rodadas.
* Para a descriptografia, basta executar as duas etapas na ordem inversa da rodada 15 até a 0. É possível utilizar a mesma caixa de substituição, visto que esta é sempre simétrica.
 
### Vigenere
 
* Cifra de Vigenere utilizando 95 diferentes caracteres.
 * Utiliza uma chave inicial, ou informada pelo usuário ou "nerfthis" como a default do algoritmo.
 * Gera a chave para o tamanho igual do texto, concatenando a chave com o texto a ser cifrado.
 
* Sem necessidade de criar uma matriz de 95x95, todas as substituições foram feitas matematicamente.
 * Primeiro feito o deslocamento da tabela ascii aceitável pelo algoritmo para 0 a 94.
 * Depois foi feita a substituição.
 * E finalmente deslocar a saída para a tabela ascii.

### Vigenere Diferente

* Cifra de Vigenere utilizando 28 diferentes caracteres. Transformando letras maiusculas para minusculas.
 * Utiliza a chave default "nerfthis".
 * Adiciona 8 caracteres ao texto.

* Cifra 3 vezes mudando a key em cada iteração.
* Possui uma key que realiza a decifra em uma iteração.
  * Impossivel reverter a cifra de forma normal sem as chaves intermediarias, apenas com a chave especifica que realiza em apenas uma iteração.