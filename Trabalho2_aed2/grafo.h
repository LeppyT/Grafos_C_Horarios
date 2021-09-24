#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "lista_ord.h"


struct grafo
{
    int NumVertices;
    int NumArestas;
    Lista **Mat;
};


typedef struct grafo TipoGrafo;

TipoGrafo* CriarGrafo(int NVertices);
int inserirAresta(TipoGrafo *G, int v1, int v2, int inicio, int fim);
int retirarAresta(TipoGrafo *Grafo, int v1, int v2);
void exibirGrafo(TipoGrafo *G);
void exibirMatriz(TipoGrafo *G);
TipoGrafo* liberarGrafo(TipoGrafo* G);
int caminho_valido(TipoGrafo *G, int v1, int v2);
int retirar_horario(TipoGrafo *G, int v1, int v2, int inicio, int fim);

#endif // GRAFO_H_INCLUDED
