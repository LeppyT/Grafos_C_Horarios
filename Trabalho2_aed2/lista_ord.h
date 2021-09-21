#ifndef LISTA_ORD_H_INCLUDED
#define LISTA_ORD_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
typedef struct no * Lista;
Lista cria_lista();
int lista_vazia(Lista lst);
int insere_elem (Lista *lst, int inicio, int fim);
int remove_elem (Lista *lst, int inicio, int fim);
void limpa_lista(Lista *lst);

#endif // LISTA_ORD_H_INCLUDED
