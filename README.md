
# Trabalho LFA - Parser Descendente Recursivo 2019/1 

**Autor:**  
>Marcos Antonio Carneiro de Paula

**Linguagem:** 
>- C

**Ambiente de programação:** 
>- VS Code 
>- GCC 8.3.0
>- Manjaro Linux 18.0.4 *Illyria*

**Descrição geral dos arquivos aqui contidos**

*source/mel_parser.c*
>Código fonte da implementação do *Parser Descendente Recursivo*

*source/mel_parser.h*
>Header com as declarações das funções presentes em *source/mel_parser.c*, definição de constantes e da *struct* utilizada.

*source/main.c*
>Arquivo contendo o código principal de execução do programa.

*source/trab1.sh*
>Shell script que pode ser usado para copilar o código fonte e executar o binário gerado 

**Executando** 

Para executar o programa existe duas formas:
- **Excutar o *source/trab1.sh*:** 
    - O script cria uma pasta chamada *binario*, copila o código fonte dentro da pasta criada e executa o binário;
- **Copilar e executar manualmente**
    - Em ambiente Linux execute os seguintes comandos
    ```bash
    $ gcc -Wall -pedantic ./mel_parser.c ./main.c -o ./main.bin -lm
    $ ./main.bin
    ```
    **PS1:** O script *source/trab1.sh* deve estar com as devidas permissões para ser executado.

    **PS2:** Considera-se que se execute o script e os comandos dentro do diretório *./source*.