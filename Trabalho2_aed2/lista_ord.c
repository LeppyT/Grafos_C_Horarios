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
        return 0; // Lista N�O vazia
}

int insere_elem (Lista *lst, int inicio, int fim) {
    // Aloca um novo n�
    Lista N = (Lista) malloc(sizeof(struct no));
    if (N == NULL) { return 0; } // Falha: n� n�o alocado
    N->inicio = inicio; // Insere o conte�do (valor do inicio)
    N->fim = fim;
    if (lista_vazia(*lst) || inicio <= (*lst)->inicio)
        {N->prox = *lst; // Aponta para o 1on� atual da lista
    *lst = N; // Faz a lista apontar para o novo n�
    return 1;  }
    Lista aux = *lst; // Faz aux apontar para 1on�
    while (aux->prox != NULL && (aux->prox->inicio < inicio || aux->prox->inicio == inicio && aux->prox->fim < fim))
        aux = aux->prox; // Avan�a
    if(aux->prox->inicio == inicio && aux->prox->fim == fim)//se o elemento j� existe, n�o precisa inserir
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
    Lista aux = *lst; // Ponteiro auxiliar para o 1on�
    // Trata elemento = 1on� da lista
    if (inicio == (*lst)->inicio && fim == (*lst)->fim)
        {*lst = aux->prox; // Lista aponta para o 2on�
    free(aux); // Libera mem�ria alocada
    return 1; }
    while (aux->prox != NULL (aux->prox->inicio < inicio || aux->prox->inicio == inicio && aux->prox->fim < fim))
        aux = aux->prox;
    if (aux->prox == NULL || aux->prox->inicio > inicio || aux->prox->fim > fim)
        return 0; // Falha
    Lista aux2 = aux->prox; // Aponta n� a ser removido
    aux->prox = aux2->prox; // Retira n� da lista
    free(aux2); // Libera mem�ria alocada
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
