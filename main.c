#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expressao.h"

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main() {
    Expressao e;
    int opcao;
    
    do {
        printf("\n--- Avaliador de Expressoes ---\n");
        printf("1 - Converter Pos-Fixa para Infixa\n");
        printf("2 - Converter Infixa para Pos-Fixa\n");
        printf("3 - Avaliar Expressao Pos-Fixada\n");
        printf("4 - Avaliar Expressao Infixa\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        if (opcao == 0) {
            printf("Encerrando...\n");
            break;
        }

        printf("Digite a expressao: ");
        fgets(e.posFixa, sizeof(e.posFixa), stdin);
        e.posFixa[strcspn(e.posFixa, "\n")] = '\0';

        switch (opcao) {
            case 1: {
                char *infixa = getFormaInFixa(strdup(e.posFixa));
                printf("Forma Infixa: %s\n", infixa);
                free(infixa);
                break;
            }
            case 2: {
                char *posfixa = getFormaPosFixa(strdup(e.posFixa));
                printf("Forma Pos-Fixa: %s\n", posfixa);
                free(posfixa);
                break;
            }
            case 3: {
                e.Valor = getValorPosFixa(strdup(e.posFixa));
                printf("Valor: %.2f\n", e.Valor);
                break;
            }
            case 4: {
                e.Valor = getValorInFixa(strdup(e.posFixa));
                printf("Valor: %.2f\n", e.Valor);
                break;
            }
            default:
                printf("Opcao invalida.\n");
        }
    } while (1);

    return 0;
}