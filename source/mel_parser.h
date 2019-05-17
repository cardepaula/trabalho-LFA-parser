#ifndef __PARSER_H__
#define __PARSER_H__

#define __TRUE 1
#define __FALSE 0

typedef struct expressao{
    char * str;
    double resultado;
} Expressao;

typedef struct digito{
    int digito;
    int syntaxErr;
} Digito;

Expressao * criaExpressao();

void apagarExpressao(Expressao * e);

void addCasaInteiro (int * numero, int digito);

void error(const char mensagem[]);

void retiraEspaco(Expressao * e);

double expr(Expressao * e);

double term(Expressao * e);

double factor(Expressao * e);

double base(Expressao * e);

double number(Expressao * e);

Digito * digit(Expressao * e);

#endif