#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

Lista* inicializa_lista(void) {
    return NULL;
}

Lista* insere(Lista *l, int id, int ligacao) {
    Lista* novo = (Lista*) malloc(sizeof(Lista));

    novo->id = id;
    novo->ligacao = ligacao;
    novo->proximo = l;

    return novo;
}

Lista* componentes(Grafo *g, Grafo *orig, int n, Lista *li) {
    Lista* clista = li;

    if (g != NULL) {
        int pos = n;
        Grafo *p = g;
        Grafo *j = copia(g);

        //Marca os n�s que est�o conectados entre si
        conexidade(g,g);

        Lista *visit = inicializa_lista();

        //Salva na clista os n�s marcados com 1
        while (p != NULL) {
            if (p->visitado == 1) {
                clista = insere(clista, p->id, pos);
                visit = insere(visit, p->id, 0);
            }

            p = p->proximo;
        }

        pos++;

        //Percorre aux e retira do grafo copiado j, os n�s j� visitados
        Lista *aux = visit;

        while (aux != NULL) {
            j = retira_no(j, aux->id);
            aux = aux->proximo;
        }

        //Chama a fun��o novamente passando o grafo sem os n�s j� visitados
        return componentes(j, orig, pos, clista);
        libera_lista(visit);
    }

    Lista *aux = clista;
    FILE *arq;

    arq = fopen("componentes.txt", "w");

    //primeira linha do arquivo: Quantidade de n�s
    int c = aux->ligacao;
    fprintf(arq, "%d\n", c);

    //Salva no arquivo as componentes conexas
    while (aux != NULL) {
        if (aux->ligacao == c) {
            fprintf(arq, "%d ", aux->id);
            aux = aux->proximo;
        } else {
            c--;
            fprintf(arq, "\n");
        }
    }

    fclose(arq);
    libera_lista(clista);

    system("componentes.txt");
}

void libera_lista(Lista *l) {
    if (l != NULL) {
        libera_lista(l->proximo);
        free(l);
    }
}

void imprime_lista(Lista *l) {
    Lista *li = l;

    while (li != NULL) {
        printf("%d - %d\n", li->id, li->ligacao);
        li = li->proximo;
    }
}

int tamanho(Lista *l) {
    Lista *li = l;
    int cont = 0;

    while (li != NULL) {
        cont++;
        li = li->proximo;
    }

    return cont;
}

int busca_lista(Lista *l, int elemento1, int elemento2) {
    Lista *li = l;

    while (li != NULL) {
        if ((li->id == elemento2) && (li->ligacao == elemento1) ){
            return 1;
        }

        li = li->proximo;
    }

    return 0;
}
