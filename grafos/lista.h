#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include "grafo.h"

typedef struct lista {
    int id;
    int ligacao;
    struct lista *proximo;
} Lista;

Lista* inicializa_lista(void);
Lista* insere(Lista *l, int id, int ligacao);
Lista* componentes(Grafo *g, Grafo *orig, int n, Lista *li);
void libera_lista(Lista *l);
void imprime_lista(Lista *l);
int tamanho(Lista *l);
int busca_lista(Lista *l, int elemento1, int elemento2);

#endif // LISTA_H_INCLUDED
