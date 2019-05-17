#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mel_parser.h"

#define DEZ 10
#define ZERO 0
#define TAM_EXPRESSAO 500
#define CHAR_ZERO '0'
#define CHAR_NOVE '9'
#define CHAR_PONTO '.'
#define CHAR_E 'E'
#define CHAR_e 'e'
#define CHAR_MAIS '+'
#define CHAR_MENOS '-'
#define CHAR_ABRE_PARENTESES '('
#define CHAR_FECHA_PARENTESES ')'
#define CHAR_ELEVADO '^'
#define CHAR_ESPACO ' '
#define CHAR_MULT '*'
#define CHAR_DIV '/'
#define CHAR_RESTO '%'

// PARSER DESCENDENTE RECURSIVO
double expr(Expressao * e){
    double termo1 = term(e);
    double termo2 = 0.0;
    retiraEspaco(e);

    while (*e->str == CHAR_MAIS || *e->str == CHAR_MENOS || *e->str == CHAR_ESPACO){
        
        if (*e->str == CHAR_ESPACO) {
            retiraEspaco(e);
        }

        if (*e->str == CHAR_MAIS) {
            e->str++;
            termo2 = term(e);
            termo1 += termo2;
        } else if (*e->str == CHAR_MENOS) {
            e->str++;
            termo2 = term(e);
            termo1 -= termo2;
        } else error("Syntax error.");
    } 

    return termo1;
}

double term(Expressao * e) {

    double fator1 = factor(e);
    double fator2 = 0.0;
    retiraEspaco(e);

    while ( *e->str == CHAR_MULT || *e->str == CHAR_DIV || *e->str == CHAR_RESTO ){
        
        if ( *e->str == CHAR_MULT ) {
            e->str++;
            fator2 = factor(e);
            fator1 = fator1 * fator2; 
        } else if ( *e->str == CHAR_DIV ) {
            e->str++;
            if ( *e->str == CHAR_DIV ){
                e->str++;
                fator2 = factor(e);
                fator1 = (int) (fator1 / fator2);
            } else {
                fator2 = factor(e);
                fator1 = fator1 / fator2;
            }
        } else {
            e->str++;
            fator2 = factor(e);
            fator1 = (long int) fator1 %  (long int) fator2;
        }
    }
    
    return fator1;
}

double factor(Expressao * e) {

    double b = base(e);
    double fator = 0.0;
    retiraEspaco(e);

    if (*e->str == CHAR_ELEVADO) {
        e->str++;
        fator = factor(e);
        b = pow(b, fator);
    }

    return b;
}

double base(Expressao * e){

    double b = 0.0;
    int nega = __FALSE;
    retiraEspaco(e);

    if (*e->str == CHAR_MAIS || *e->str == CHAR_MENOS) {
        if (*e->str == CHAR_MENOS) 
            nega = __TRUE;

        
        e->str++;
        b = base(e);
        
        if (nega == __TRUE) 
            b = b * -1;
        return b;
    } else if (*e->str == CHAR_ABRE_PARENTESES){
        
        e->str++;
        b = expr(e);
        if (*e->str == CHAR_FECHA_PARENTESES){
            
            e->str++;
        }
    }  else {
        b = number(e);
    }
    return b;
}

double number(Expressao * e){

    int numeroInteiro = 0;
    int casasDecimais= 1;
    int decimalFlag =  __FALSE;
    int eFlag = __FALSE;
    int eFlagNeg = __FALSE;
    int notacaoE = 0;
    double numeroRetorno;
    Digito * digi = digit(e);

    while (digi->syntaxErr == __FALSE){

        if (eFlag == __FALSE){
            addCasaInteiro(&numeroInteiro, digi->digito);
            if (decimalFlag == __TRUE ){
                casasDecimais *= DEZ;
            }

            if (*e->str == CHAR_PONTO){
                decimalFlag = __TRUE;
                e->str++;
            }
            if (*e->str == CHAR_E || *e->str == CHAR_e){
                eFlag = __TRUE;
                e->str++;
                if (*e->str == CHAR_MENOS){
                    eFlagNeg = __TRUE;
                    e->str++;
                }else if (*e->str == CHAR_MAIS){
                    e->str++;
                }
            }
        } else if (eFlag == __TRUE) {
            addCasaInteiro(&notacaoE, digi->digito);
        }
        free(digi);
        digi = digit(e);
    }
    free(digi);
    
    numeroRetorno = (double) numeroInteiro / casasDecimais;
    
    if (notacaoE != ZERO){
        for (int i = 0; i < notacaoE; i++){
            if (eFlagNeg == __TRUE)
                numeroRetorno /= DEZ;
            else
                numeroRetorno *= DEZ;
        }
    }
    return numeroRetorno;
}

Digito * digit(Expressao * e){
    Digito * d = malloc(sizeof(Digito));

    if (*e->str >= CHAR_ZERO && *e->str <= CHAR_NOVE){
        d->digito = (int) *e->str - CHAR_ZERO;
        d->syntaxErr = __FALSE;
        e->str++;
        return d;
    }else{
        d->syntaxErr = __TRUE;
        return d;       
    }
}


// FUNCOES AUXILIARES
void addCasaInteiro (int * numero, int digito){
    *numero *= DEZ;
    *numero += digito;
}

void retiraEspaco(Expressao * e){
    while(*e->str == CHAR_ESPACO){
        e->str++;
    }
}

void error(const char mensagem[]){
    printf("%s\n", mensagem);
    exit(0);
}

Expressao * criaExpressao(){
    Expressao * e = malloc(sizeof(Expressao));
    e->str = malloc(TAM_EXPRESSAO * sizeof(char));
    e->resultado = 0;
    return e;
}

void apagarExpressao(Expressao * e){
    free(e);
}