#include "ord.h"
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

int insere_elem (Lista *lst, int inicio, int fim) {
    // Aloca um novo nó
    Lista N = (Lista) malloc(sizeof(struct no));
    if (N == NULL) { return 0; } // Falha: nó não alocado
    N->inicio = inicio; // Insere o conteúdo (valor do inicio)
    N->fim = fim;
    if (lista_vazia(*lst) || inicio <= (*lst)->inicio)
        {N->prox = *lst; // Aponta para o 1onó atual da lista
    *lst = N; // Faz a lista apontar para o novo nó
    return 1;  }
    Lista aux = *lst; // Faz aux apontar para 1onó
    while (aux->prox != NULL && (aux->prox->inicio < inicio || aux->prox->inicio == inicio && aux->prox->fim < fim))
        aux = aux->prox; // Avança
    if(aux->prox->inicio == inicio && aux->prox->fim == fim)//se o elemento já existe, não precisa inserir
    {
        limpa_lista(&N);
        return 2;
    }
    // Insere o novo elemento na lista
    N->prox = aux->prox;
    aux->prox = N;
    return 1;}

int remove_elem (Lista *lst, int inicio, int fim) {
    if (lista_vazia(*lst) == 1 || inicio < (*lst)->inicio)
        return 0; // Falha
    Lista aux = *lst; // Ponteiro auxiliar para o 1onó
    // Trata elemento = 1onó da lista
    if (inicio == (*lst)->inicio && fim == (*lst)->fim)
        {*lst = aux->prox; // Lista aponta para o 2onó
    free(aux); // Libera memória alocada
    return 1; }
    while (aux->prox != NULL (aux->prox->inicio < inicio || aux->prox->inicio == inicio && aux->prox->fim < fim))
        aux = aux->prox;
    if (aux->prox == NULL || aux->prox->inicio > inicio || aux->prox->fim > fim)
        return 0; // Falha
    Lista aux2 = aux->prox; // Aponta nó a ser removido
    aux->prox = aux2->prox; // Retira nó da lista
    free(aux2); // Libera memória alocada
    return 1;}



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
