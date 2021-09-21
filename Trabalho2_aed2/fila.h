#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED
#include "no.h"

typedef struct Fila
{
    TipoNo *inicio, *fim;
    int tamanho;
} TipoFila;


void IniciaFila(TipoFila *fila);
int Vazia(TipoFila *fila);
void Enfileira(int x, TipoFila *fila);
int Desenfileira(TipoFila *fila);



#endif // FILA_H_INCLUDED
