#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "expressao.h"

#define MAX 100
#define PI 3.14159265358979323846

// Estruturas de pilhas

typedef struct {
    float itens[MAX];
    int topo;
} PilhaFloat;

typedef struct {
    char *itens[MAX];
    int topo;
} PilhaString;

typedef struct {
    char itens[MAX][32];
    int topo;
} PilhaToken;

// Inicialização de pilhas
void inicializarPilhaFloat(PilhaFloat *p) { p->topo = -1; }
int pilhaFloatVazia(PilhaFloat *p) { return p->topo == -1; }
void empilharFloat(PilhaFloat *p, float val) { p->itens[++p->topo] = val; }
float desempilharFloat(PilhaFloat *p) { return p->itens[p->topo--]; }

void inicializarPilhaString(PilhaString *p) { p->topo = -1; }
void empilharString(PilhaString *p, char *val) { p->itens[++p->topo] = val; }
char* desempilharString(PilhaString *p) { return p->itens[p->topo--]; }

void inicializarPilhaToken(PilhaToken *p) { p->topo = -1; }
void empilharToken(PilhaToken *p, const char *val) { strcpy(p->itens[++p->topo], val); }
char* desempilharToken(PilhaToken *p) { return p->itens[p->topo--]; }
char* topoToken(PilhaToken *p) { return p->itens[p->topo]; }
int pilhaTokenVazia(PilhaToken *p) { return p->topo == -1; }

// Funções matemáticas auxiliares
float raizQuadrada(float x) {
    if (x <= 0) return 0;
    float estimativa = x / 2.0f;
    for (int i = 0; i < 20; i++) {
        estimativa = 0.5f * (estimativa + x / estimativa);
    }
    return estimativa;
}

float potencia(float base, float exp) {
    if (exp == 0) return 1;
    if (exp < 0) return 1.0f / potencia(base, -exp);

    float resultado = 1.0f;
    for (int i = 0; i < (int)exp; i++) {
        resultado *= base;
    }

    float fracao = exp - (int)exp;
    if (fracao > 0.00001f) {
        resultado *= raizQuadrada(base); // Correção: agora raizQuadrada foi definida antes
    }
    return resultado;
}

float grausParaRadianos(float graus) {
    return graus * PI / 180.0f;
}

float seno(float x) {
    float x2 = x * x;
    float x3 = x2 * x;
    float x5 = x3 * x2;
    float x7 = x5 * x2;
    float x9 = x7 * x2;
    return x - x3/6.0f + x5/120.0f - x7/5040.0f + x9/362880.0f;
}

float cosseno(float x) {
    float x2 = x * x;
    float x4 = x2 * x2;
    float x6 = x4 * x2;
    float x8 = x6 * x2;
    return 1 - x2/2.0f + x4/24.0f - x6/720.0f + x8/40320.0f;
}

float tangente(float x) {
    float c = cosseno(x);
    if (c == 0) return 0;
    return seno(x) / c;
}

float logaritmo10(float x) {
    if (x <= 0) return 0;

    // Melhoria: log(x) = ln(x) / ln(10), usando série de Taylor para ln(x)
    // ln(x) = 2 * [ (x-1)/(x+1) + 1/3 * ((x-1)/(x+1))^3 + 1/5 * ((x-1)/(x+1))^5 + ... ]

    float y = (x - 1) / (x + 1);
    float y2 = y * y;
    float termo = y;
    float soma = 0;
    int i;

    for (i = 1; i <= 19; i += 2) {
        soma += termo / i;
        termo *= y2;
    }

    float ln = 2 * soma;
    return ln / 2.302585093f;  // ln(10)
}


// Avaliação de expressão pós-fixada
float getValorPosFixa(char *StrPosFixa) {
    PilhaFloat pilha;
    inicializarPilhaFloat(&pilha);
    char *token = strtok(StrPosFixa, " ");

    while (token != NULL) {
        if (strcmp(token, "+") == 0) {
            float b = desempilharFloat(&pilha), a = desempilharFloat(&pilha);
            empilharFloat(&pilha, a + b);
        } else if (strcmp(token, "-") == 0) {
            float b = desempilharFloat(&pilha), a = desempilharFloat(&pilha);
            empilharFloat(&pilha, a - b);
        } else if (strcmp(token, "*") == 0) {
            float b = desempilharFloat(&pilha), a = desempilharFloat(&pilha);
            empilharFloat(&pilha, a * b);
        } else if (strcmp(token, "/") == 0) {
            float b = desempilharFloat(&pilha), a = desempilharFloat(&pilha);
            if (b == 0) {
                printf("Erro: Divisao por zero!\n");
                return 0;
            }
            empilharFloat(&pilha, a / b);
        } else if (strcmp(token, "^") == 0) {
            float b = desempilharFloat(&pilha), a = desempilharFloat(&pilha);
            empilharFloat(&pilha, potencia(a, b));
        } else if (strcmp(token, "%") == 0) {
            int b = (int)desempilharFloat(&pilha), a = (int)desempilharFloat(&pilha);
            if (b == 0) {
                printf("Erro: Modulo por zero!\n");
                return 0;
            }
            empilharFloat(&pilha, a % b);
        } else if (strcmp(token, "log") == 0) {
            float a = desempilharFloat(&pilha);
            empilharFloat(&pilha, logaritmo10(a));
        } else if (strcmp(token, "sen") == 0) {
            float a = desempilharFloat(&pilha);
            empilharFloat(&pilha, seno(grausParaRadianos(a)));
        } else if (strcmp(token, "cos") == 0) {
            float a = desempilharFloat(&pilha);
            empilharFloat(&pilha, cosseno(grausParaRadianos(a)));
        } else if (strcmp(token, "tg") == 0) {
            float a = desempilharFloat(&pilha);
            empilharFloat(&pilha, tangente(grausParaRadianos(a)));
        } else if (strcmp(token, "raiz") == 0) {
            float a = desempilharFloat(&pilha);
            empilharFloat(&pilha, raizQuadrada(a));
        } else {
            empilharFloat(&pilha, atof(token));
        }
        token = strtok(NULL, " ");
    }
    return desempilharFloat(&pilha);
}

// Conversão de pos-fixa para infixa
char *getFormaInFixa(char *Str) {
    PilhaString pilha;
    inicializarPilhaString(&pilha);
    char *token = strtok(Str, " ");

    while (token != NULL) {
        if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || 
            strcmp(token, "*") == 0 || strcmp(token, "/") == 0 || 
            strcmp(token, "^") == 0 || strcmp(token, "%") == 0) {
            char *b = desempilharString(&pilha);
            char *a = desempilharString(&pilha);
            char *res = malloc(strlen(a) + strlen(b) + strlen(token) + 4);
            sprintf(res, "(%s %s %s)", a, token, b);
            free(a); free(b);
            empilharString(&pilha, res);
        } else if (strcmp(token, "log") == 0 || strcmp(token, "sen") == 0 ||
                   strcmp(token, "cos") == 0 || strcmp(token, "tg") == 0 || 
                   strcmp(token, "raiz") == 0) {
            char *a = desempilharString(&pilha);
            char *res = malloc(strlen(a) + strlen(token) + 3);
            sprintf(res, "%s(%s)", token, a);
            free(a);
            empilharString(&pilha, res);
        } else {
            char *val = malloc(strlen(token) + 1);
            strcpy(val, token);
            empilharString(&pilha, val);
        }
        token = strtok(NULL, " ");
    }
    return desempilharString(&pilha);
}

// Precedência de operadores
int precedencia(char *op) {
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0) return 1;
    if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0 || strcmp(op, "%") == 0) return 2;
    if (strcmp(op, "^") == 0) return 3;
    if (strcmp(op, "log") == 0 || strcmp(op, "sen") == 0 || 
        strcmp(op, "cos") == 0 || strcmp(op, "tg") == 0 || 
        strcmp(op, "raiz") == 0) return 4;
    return 0;
}

// Conversão de infixa para pos-fixa
char *getFormaPosFixa(char *Str) {
    PilhaToken operadores;
    inicializarPilhaToken(&operadores);
    char *saida = malloc(512);
    saida[0] = '\0';
    char token[32];
    char *p = Str;

    while (*p) {
        if (isspace(*p)) {
            p++;
            continue;
        }
        if (isdigit(*p) || *p == '.') {
            int len = 0;
            while (isdigit(p[len]) || p[len] == '.') {
                token[len] = p[len];
                len++;
            }
            token[len] = '\0';
            strcat(saida, token);
            strcat(saida, " ");
            p += len;
        } else if (isalpha(*p)) {
            int len = 0;
            while (isalpha(p[len])) {
                token[len] = p[len];
                len++;
            }
            token[len] = '\0';
            empilharToken(&operadores, token);
            p += len;
        } else if (*p == '(') {
            token[0] = '(';
            token[1] = '\0';
            empilharToken(&operadores, token);
            p++;
        } else if (*p == ')') {
            while (!pilhaTokenVazia(&operadores) && strcmp(topoToken(&operadores), "(") != 0) {
                strcat(saida, desempilharToken(&operadores));
                strcat(saida, " ");
            }
            if (!pilhaTokenVazia(&operadores) && strcmp(topoToken(&operadores), "(") == 0)
                desempilharToken(&operadores);
            if (!pilhaTokenVazia(&operadores)) {
                char *topo = topoToken(&operadores);
                if (strcmp(topo, "sen") == 0 || strcmp(topo, "cos") == 0 ||
                    strcmp(topo, "tg") == 0 || strcmp(topo, "log") == 0 || strcmp(topo, "raiz") == 0) {
                    strcat(saida, desempilharToken(&operadores));
                    strcat(saida, " ");
                }
            }
            p++;
        } else {
            token[0] = *p;
            token[1] = '\0';
            while (!pilhaTokenVazia(&operadores) &&
                   strcmp(topoToken(&operadores), "(") != 0 &&
                   precedencia(topoToken(&operadores)) >= precedencia(token)) {
                strcat(saida, desempilharToken(&operadores));
                strcat(saida, " ");
            }
            empilharToken(&operadores, token);
            p++;
        }
    }

    while (!pilhaTokenVazia(&operadores)) {
        strcat(saida, desempilharToken(&operadores));
        strcat(saida, " ");
    }

    return saida;
}

// Avalia expressão infixada diretamente
float getValorInFixa(char *StrInFixa) {
    char *expressao = strdup(StrInFixa);
    for (char *p = expressao; *p; p++) {
        if (*p == ',') *p = '.';
    }
    char *posfixa = getFormaPosFixa(expressao);
    float resultado = getValorPosFixa(posfixa);
    free(expressao);
    free(posfixa);
    return resultado;
}
