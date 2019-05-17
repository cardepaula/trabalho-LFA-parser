#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mel_parser.h"

#define STRING_EXIT "exit"

int main(){
    Expressao *ex = criaExpressao();

    printf("Digite a expressao (ou exit para sair):\n");
    scanf("%[^\n]", ex->str);

    while (strcmp(ex->str, STRING_EXIT) != 0){
        getchar();
        ex->resultado = expr(ex);
        printf("Resultado: %f\n", ex->resultado);
        printf("Digite a expressao (ou exit para sair):\n");
        scanf("%[^\n]", ex->str);
    }

    apagarExpressao(ex);
    return 0;
}
