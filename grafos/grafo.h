#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

typedef struct vizinho {
    int id;
    struct vizinho *proximo_vizinho;
} Vizinho;

typedef struct grafo {
    int visitado;
    int id;
    Vizinho *primeiro;
    struct grafo *proximo;
} Grafo;

Grafo* inicializa(void);
Grafo* busca(Grafo* g, int elemento);
Grafo* insere_no(Grafo *g, int no);
Grafo* retira_no(Grafo *g, int no);
Grafo* copia(Grafo *g);
void insere_aresta(Grafo *g, int no1, int no2);
void retira_aresta(Grafo *g, int no1, int no2);
void gera_html(Grafo*g);
void libera(Grafo *g);
void imprime(Grafo *g);
void zera_visitados(Grafo *g);
void pontes(Grafo *g);
void conexidade(Grafo *g, Grafo *g1);
void salva(Grafo *g, char* nome);
int qtd_nos(Grafo *g);
int conexo(Grafo *g);

#endif // GRAFO_H_INCLUDED
