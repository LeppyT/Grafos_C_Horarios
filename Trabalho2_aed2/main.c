#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"

int main()
{
    TipoGrafo *g = NULL;
    int first, sec;
    int test;
    int option = 0;
    int inicio,fim;
    while(option != 6) {
        printf(" ---------------MENU--------------- \n");
        printf("|                                  |\n");
        printf("| [1]Inserir número de cidades     |\n");
        printf("| [2]Inserir arestas               |\n");
        printf("| [3]Exibir matriz                 |\n");
        printf("| [4]Verificar caminho             |\n");
        printf("| [5]Retirar horario               |\n");
        printf("| [6]Sair                          |\n");
        printf(" ---------------------------------- \n");

        printf("\nDigite a opção desejada: ");
        scanf("%d", &option);

        switch(option) {
            case 1:
                scanf("%d", &first);
                if(first<1)
                {
                    printf("Numero invalido, por favor tente novamente!\n");
                    break;
                }
                g = CriarGrafo(first);
                break;

            case 2:
                printf("Digite o número da primeiro vertice: ");
                scanf("%d", &first);

                printf("Digite o número da segundo vertice: ");
                scanf("%d", &sec);
                while(1)
                {
                    printf("Digite a chegada, ou menor que 0 para sair: ");
                    scanf("%d", &inicio);

                    printf("Digite a saida, ou menor que 0 para sair: ");
                    scanf("%d", &fim);
                    if(inicio<0||fim<0)
                        break;
                    test = inserirAresta(g, first, sec, inicio, fim);
                    if(test == -1)
                        printf("Erro no grafo ou vértices.\n");
                    else if(test == 0)
                        printf("Falha ao inserir horario.\n");
                    else if(test == 1)
                        printf("Horario removido.\n");
                }

                break;

            case 3:
                exibirGrafo(g);
                exibirMatriz(g);
                break;

            case 4:
                printf("Digite o número da primeiro vertice: ");
                scanf("%d", &first);

                printf("Digite o número da segundo vertice: ");
                scanf("%d", &sec);
                test = caminho_valido(g, first, sec);
                if(test == -1)
                    printf("Algo errado.");
                else if(test == 0)
                    printf("Caminho nao encontrado.\n");
                else if(test == 1)
                    printf("Caminho encontrado.\n");
                else
                    printf("Algo muito errado.\n");

                break;
            case 5:
                printf("Digite o número da primeiro vertice: ");
                scanf("%d", &first);

                printf("Digite o número da segundo vertice: ");
                scanf("%d", &sec);
                while(1)
                {
                    printf("Digite a chegada, ou menor que 0 para sair: ");
                    scanf("%d", &inicio);

                    printf("Digite a saida, ou menor que 0 para sair: ");
                    scanf("%d", &fim);
                    test = retirar_horario(g, first, sec, inicio, fim);
                    if(test == -1)
                        printf("Erro no grafo ou vértices.\n");
                    else if(test == 0)
                        printf("Falha ao remover horario.\n");
                    else if(test == 1)
                        printf("Horario removido.\n");
                }
            case 6:

                break;

            default:
                printf("Opção inválida, por favor tente novamente!\n");
                break;
        }

        printf("=======================================\n\n");
    }

    return 0;
}
