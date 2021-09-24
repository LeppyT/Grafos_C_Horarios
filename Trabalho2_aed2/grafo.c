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
    while (aux->prox != NULL &&
            (aux->prox->inicio < inicio || (aux->prox->inicio == inicio && aux->prox->fim < fim)))
        //duas chaves de ordenacao: primeiro ordenado por inicio, depois por fim
        aux = aux->prox; // Avança
    if(aux->prox!=NULL)
    {
        if(aux->prox->inicio == inicio && aux->prox->fim == fim)//se o elemento já existe, não precisa inserir
        {
            limpa_lista(&N);
            return 2;
        }
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
        //segue ordenaçao por inicio, depois pelo fim
        aux = aux->prox;
    }
    if (aux->prox == NULL || aux->prox->inicio > inicio || aux->prox->fim > fim)
        return 0; // Falha
    Lista aux2 = aux->prox; // Aponta nó a ser removido
    aux->prox = aux2->prox; // Retira nó da lista
    free(aux2); // Libera memória alocada
    return 1;
}

int menor_chegada(TipoGrafo *G, int v1, int v2)
{
    if(G == NULL)
        return -1;

    if (v1 < 0 || v1 >= G->NumVertices || v2 < 0 || v2 >= G->NumVertices)
        return -1; // nao e possivel encontrar aresta: intervalo

    if(lista_vazia(G->Mat[v1][v2])==1)
        return -1;

    int menor = G->Mat[v1][v2]->fim;
    Lista aux = G->Mat[v1][v2];

    while(aux != NULL)
    {

        if(aux->inicio>menor)//Se o horário de inicio e maior que o menor fim, nao e necessario continuar percorrendo a lista.
            break;
        if(aux->fim < menor)
            menor = aux->fim;
        aux = aux->prox;
    }
    return menor;
}

int ultima_saida(TipoGrafo *G, int v1, int v2)
{
    if(G==NULL)
        return -1;
    if (v1<0 || v1>= G-> NumVertices || v2 < 0 || v2 >= G->NumVertices)
        return -1; // nao e possivel encontrar aresta: intervalo
    if(lista_vazia(G->Mat[v1][v2])==1)
        return -1;
    int saida = G->Mat[v1][v2]->inicio;
    Lista aux = G->Mat[v1][v2];
    while(aux!=NULL)/*e necessario percorrer ate o final para encontrar o elemento desejado, pois o maior pode estar no ultimo no.
        Possivel otimizacao: implementar uma lista circular e/ou adicionar cabeçalho para armazenar o maior e menor inicio e fim*/
    {
        if(aux->inicio>saida)
            saida = aux->inicio;
        aux = aux->prox;
    }
    return saida;
}

int menor_tempo(TipoGrafo *G, int v1, int v2, int * ini, int * fim)
{
    if(G==NULL)
        return -1;
    if (v1<0 || v1>= G-> NumVertices || v2 < 0 || v2 >= G->NumVertices)
        return -1; // nao e possivel criar aresta: intervalo
    if(lista_vazia(G->Mat[v1][v2])==1)
        return -1;
    Lista aux = G->Mat[v1][v2];
    int menor = G->Mat[v1][v2]->fim - G->Mat[v1][v2]->inicio;

    int stor_ini, stor_fim;
    while(aux!=NULL)
    {
        /*da forma que foi criada a estrutura, o menor tempo possivel e um.
        Para uma implementacao mais representativa de tempo, uma estrutura:
            struct data
            {
                int horas;
                int minutos;
            } seria mais precisa.*/
        if(menor == 1)
        {
            break;
        }
        if(aux->fim - aux->inicio < menor)
        {
            stor_fim = aux->fim;
            stor_ini = aux->inicio;
            menor = stor_fim - stor_ini;
        }
        aux = aux->prox;
    }
    *ini = stor_ini;
    *fim = stor_fim;
    return menor;
}

int menor_chegada_temporal(TipoGrafo *G, int v1, int v2, int tempoatual)
{
    if(G == NULL)
        return -1;

    if (v1 < 0 || v1 >= G->NumVertices || v2 < 0 || v2 >= G->NumVertices)
        return -1;

    if(lista_vazia(G->Mat[v1][v2])==1)
        return -1;

    Lista aux = G->Mat[v1][v2];

    int menor = 300000;
    while(aux != NULL)
    {
        if(aux->inicio<tempoatual)//Uma aresta que inicia antes do tempo atual não deve ser considerada
        {
            aux = aux->prox;
            continue;
        }
        if(aux->inicio>menor)//Se o horário de inicio e maior que o menor fim, nao e necessario continuar percorrendo a lista.
            break;
        if(aux->fim < menor)
            menor = aux->fim;
        aux = aux->prox;
    }
    if(menor == 300000)//nenhum horario valido encontrado
    {
        return -1;
    }
    return menor;
}

int caminho_valido_aux(TipoGrafo *G, int v1, int v2, int * ant, int tempoatual)
{
    int v, flag, primeira_chegada;

    if(lista_vazia(G->Mat[v1][v2]) == 0)//Existe aresta direta no destino
    {
        primeira_chegada = menor_chegada_temporal(G,v1,v2,tempoatual);
        if(primeira_chegada != -1)//valor -1 -> nao existe horario valido
            return 1; // Caminho encontrado;
    }
    for(v = 0; v < G->NumVertices; v++)
    {
        if(lista_vazia(G->Mat[v1][v]) == 0)  //Existe aresta entre vizinho v
        {
            primeira_chegada = menor_chegada_temporal(G,v1,v,tempoatual);
            if(primeira_chegada == -1)//valor -1 -> nao existe horario valido
                continue;
            if(primeira_chegada >= ant[v])/*Se ant[v] for menor ou igual que a chegada descoberta,
                esse vértice já foi visitado, e não se encontrou um caminho, pois a função teria retornado.
                Isso significa que não existe um caminho em tempos iguais ou maiores.*/
                continue;
            ant[v] = primeira_chegada;//Marca que o vértice foi visitado, e o horário.
            flag = caminho_valido_aux(G, v, v2, ant, primeira_chegada);
        }
        if(flag == 1)
        {
            return 1;  // Caminho encontrado;
        }
    }
    return 0;
}

int caminho_valido(TipoGrafo *G, int v1, int v2)
{
    if(G == NULL)
        return -1;

    if (v1 < 0 ||  v1 >= G->NumVertices || v2 < 0 || v2 >= G->NumVertices)
        return -1;//vertices nao existem
    int ant[G->NumVertices];
    for(int i = 0; i<G->NumVertices; i++)
    {
        ant[i] = 300000;/*vetor vai armazenar o tempo mais cedo que
        ja se chegou no vertice i , inicializado com valor extremamente alto*/
    }
    int tempoatual = 0;
    int i = caminho_valido_aux(G, v1, v2, ant, tempoatual);
    return i;
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
    int k;
    while(i<NVertices)
    {
        Grafo->Mat[i] = (Lista*) calloc (NVertices,sizeof(Lista));
        if (Grafo->Mat[i] == NULL)
        {
            for (k=0; k<i; k++)
                free(Grafo->Mat[k]);
            free(Grafo) ;
            return NULL;
        }
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
        return -1; // nao e possivel criar aresta: intervalo
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
    if(lista_vazia(G->Mat[v1][v2]) == 1)
        return 0; // aresta nao existe
    limpa_lista(&G->Mat[v1][v2]); //remove aresta
    G->NumArestas--;
    return 1;
}

int retirar_horario(TipoGrafo *G, int v1, int v2, int inicio, int fim)
{
    if (G == NULL)
        return -1; // grafo nao existe
    if (v1<0 || v1>=G->NumVertices || v2<0 || v2>=G-> NumVertices)
        return -1; // nao eh possivel retirar aresta: intervalo
    if(lista_vazia(G->Mat[v1][v2]) == 1)
        return 0; // aresta nao existe
    int flag = remove_elem(&G->Mat[v1][v2], inicio, fim);
    return flag;
}

void exibirGrafo(TipoGrafo *G)
{
    int v, w;
    printf("\nGrafo - Resumo:\n");
    for (v = 0; v < G->NumVertices; ++v)
    {
        printf( "%d:", v);
        for (w = 0; w < G->NumVertices; ++w)
            if (lista_vazia(G->Mat[v][w]) == 0)
                printf( " %d",w );
        printf( "\n");
    }
}

void exibirMatriz(TipoGrafo *G)
{
    int v, w;
    Lista aux;
    printf("\nGrafo - Matriz:\n");
    for (v = 0; v < G->NumVertices; ++v)
    {
        printf( "%d:", v);
        for (w = 0; w < G->NumVertices; ++w)
        {
            if (lista_vazia(G->Mat[v][w]) == 0)
            {
                aux = G->Mat[v][w];
                printf( " %d[",w );
                while(aux != NULL)
                {
                    printf( "[%d,%d]",aux->inicio, aux->fim);
                    aux = aux->prox;
                }
                printf("]");
            }
        }
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

