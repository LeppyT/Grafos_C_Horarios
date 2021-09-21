#include "grafo.h"
#include <stdlib.h>
#include <stdio.h>
#include "fila.h"


struct no
{
    int inicio, fim;
    struct no *prox;
};

Lista cria_lista()
{
    return NULL;
}

int lista_vazia(Lista lst)
{
    if (lst == NULL)
        return 1; // Lista vazia
    else
        return 0; // Lista NÃO vazia
}

int insere_elem (Lista *lst, int inicio, int fim)
{
    // Aloca um novo nó
    Lista N = (Lista) malloc(sizeof(struct no));
    if (N == NULL)
    {
        return 0;    // Falha: nó não alocado
    }
    N->inicio = inicio; // Insere o conteúdo (valor do inicio)
    N->fim = fim;
    if (lista_vazia(*lst) || inicio <= (*lst)->inicio)
    {
        N->prox = *lst; // Aponta para o 1onó atual da lista
        *lst = N; // Faz a lista apontar para o novo nó
        return 1;
    }
    Lista aux = *lst; // Faz aux apontar para 1onó
    while (aux->prox != NULL && (aux->prox->inicio < inicio || (aux->prox->inicio == inicio && aux->prox->fim < fim)))
        aux = aux->prox; // Avança
    if(aux->prox->inicio == inicio && aux->prox->fim == fim)//se o elemento já existe, não precisa inserir
    {
        limpa_lista(&N);
        return 2;
    }
    // Insere o novo elemento na lista
    N->prox = aux->prox;
    aux->prox = N;
    return 1;
}

int remove_elem (Lista *lst, int inicio, int fim)
{
    if (lista_vazia(*lst) == 1 || inicio < (*lst)->inicio)
        return 0; // Falha
    Lista aux = *lst; // Ponteiro auxiliar para o 1onó
    // Trata elemento = 1onó da lista
    if (inicio == (*lst)->inicio && fim == (*lst)->fim)
    {
        *lst = aux->prox; // Lista aponta para o 2onó
        free(aux); // Libera memória alocada
        return 1;
    }
    while (aux->prox != NULL && (aux->prox->inicio < inicio || (aux->prox->inicio == inicio && aux->prox->fim < fim)))
    {
        aux = aux->prox;
    }
    if (aux->prox == NULL || aux->prox->inicio > inicio || aux->prox->fim > fim)
        return 0; // Falha
    Lista aux2 = aux->prox; // Aponta nó a ser removido
    aux->prox = aux2->prox; // Retira nó da lista
    free(aux2); // Libera memória alocada
    return 1;
}



void limpa_lista(Lista *lst)
{
    if(*lst == NULL)
        return;
    Lista aux = *lst;
    while(aux != NULL)
    {
        aux = aux->prox;
        free(*lst);
        *lst = aux;
    }
    free(lst);
}


TipoGrafo* CriarGrafo(int NVertices)
{
    int i;
    TipoGrafo *Grafo;
    if ( NVertices <= 0) return NULL;
    Grafo = (TipoGrafo*) malloc(sizeof(TipoGrafo));
    if (Grafo == NULL) return NULL;

    Grafo->Mat = (Lista **) malloc(NVertices*sizeof(Lista*));
    if (Grafo->Mat == NULL)
    {
        free(Grafo);
        return NULL;
    }
    i=0;
    int j = 0;
    while(i<NVertices)
    {
        while(j<NVertices)
        {
            Grafo->Mat[i][j] = cria_lista();
            j++;
        }
        j = 0;
        i++;
    }
    Grafo->NumVertices = NVertices;
    Grafo->NumArestas = 0;
    return Grafo;
}

int inserirAresta(TipoGrafo *G, int v1, int v2, int inicio, int fim)
{
    int flag;
    if (G == NULL)
        return -1;
    if (v1<0 || v1>= G-> NumVertices || v2 < 0 || v2 >= G->NumVertices || fim-inicio<1)
        return -1; // nao eh possivel criar aresta: intervalo
    if(lista_vazia(G->Mat[v1][v2])==1)
        flag=1;
    int resultado = insere_elem(&(G->Mat[v1][v2]), inicio, fim);
    if(resultado>=1 && flag == 1)
        G->NumArestas++;
    return resultado;
}


int retirarAresta(TipoGrafo *G, int v1, int v2)
{
    if (G == NULL)
        return -1; // grafo nao existe
    if (v1<0 || v1>=G->NumVertices || v2<0 || v2>=G-> NumVertices)
        return -1; // nao eh possivel retirar aresta: intervalo
    if( lista_vazia(G->Mat[v1][v2]) == 1)
        return 0; // aresta nao existe
    limpa_lista(&G->Mat[v1][v2]); //remove aresta
    G->NumArestas--;
    return 1;
}

void exibirGrafo(TipoGrafo *G)
{
    int v, w;
    printf("\nGrafo - Resumo:\n");
    for (v = 0; v < G->NumVertices; ++v)
    {
        printf( "%d:", v);
        for (w = 0; w < G->NumVertices; ++w)
            if (lista_vazia(G->Mat[v][w])==0)
                imprime_lista(G->Mat[v][w]);
        printf( "\n");
    }
}

void exibirMatriz(TipoGrafo *G)
{
    int v, w;
    printf("\nGrafo - Matriz:\n");
    for (v = 0; v < G->NumVertices; ++v)
    {
        printf( "%d:", v);
        for (w = 0; w < G->NumVertices; ++w)
            imprime_lista(G->Mat[v][w]);
        printf( "\n");
    }
}

TipoGrafo* liberarGrafo(TipoGrafo* G)
{
    int i;
    if (G == NULL)
        return NULL;

    for(i=0; i< G->NumVertices; i++)
        free(G->Mat[i]);
    free(G->Mat);
    free(G);
    G = NULL;
    return G;
}

int FoiVisitado(int v, int visitados[], int tam)
{
    if(tam<v)
        return -1;
    else if(visitados[v]==1)
    {
        return 1;
    }
    return 0;
}
/*
int caminho_mais_curto(TipoGrafo G, int v, int destino)
{
    int *visitados;
    TipoFila *fila;
    int i=0, cont = 0, vt;

    int Dist[G.NumVertices], anterior[G.NumVertices];
    visitados = (int *) malloc (G.NumVertices * sizeof (int));
    //inicializa os vetores visitados, Dist, anterior.
    for (i=0; i<G.NumVertices; i++)
    {
        visitados[i] = 0;
        Dist[i] = 300000;
        anterior[i] = -1;
    }

    // anotar como visitado o vértice de origem (busca)
    visitados[cont]=v;

    //Iniciar a fila e inserir o vértice de origem
    fila = (TipoFila *) malloc (sizeof(TipoFila));
    IniciaFila(fila);
    Enfileira(v,fila);


    Dist[v]=0;

    while(Vazia(fila)!=1)
    {
        vt = Desenfileira(fila);
        for(i=0; i<G.NumVertices; i++)
        {
            if(G.Mat[vt][i]>0)
            {
                if(FoiVisitado(i,visitados,G.NumVertices)==0)
                {
                    Enfileira(i,fila);
                    visitados[i]=1;
                }
                if(Dist[i]>Dist[vt]+G.Mat[vt][i])
                {
                    Dist[i]=Dist[vt]+G.Mat[vt][i];
                    anterior[i] = vt;
                }
            }
        }
    }



    return Dist[destino];
}
*/
