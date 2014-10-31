#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "lista.h"

Grafo* inicializa(void) {
    return NULL;
}

Grafo* busca(Grafo* g, int elemento) {
    Grafo *p = g;

    while ((p != NULL) && (p->id != elemento)) {
        p = p->proximo;
    }

    return p;
}

Grafo* insere_no(Grafo* g, int no) {
    if (busca(g, no)) {
        return g;
    }

    Grafo *novo = (Grafo*) malloc(sizeof(Grafo));

    novo->id = no;
    novo->primeiro = NULL;
    novo->proximo = g;
    novo->visitado = 0;

    return novo;
}

void insere_aresta(Grafo* g, int no1, int no2) {
    Grafo *p = busca(g, no1);
    Grafo *q = busca(g, no2);

    if ((p == NULL)|| (q == NULL)) {
        return;
    }

    Vizinho *novo = (Vizinho*) malloc(sizeof(Vizinho));

    novo->id = no2;
    novo->proximo_vizinho = p->primeiro;

    p->primeiro = novo;

    novo = (Vizinho*) malloc(sizeof(Vizinho));

    novo->id = no1;
    novo->proximo_vizinho = q->primeiro;

    q->primeiro = novo;
}

Grafo *retira_no(Grafo *g , int no) {
    Grafo *p = g, *ant = NULL;

    while ((p != NULL) && (p->id != no)) {
        ant = p;
        p = p->proximo;
    }

    if (p == NULL) {
        return g;
    }

    Vizinho *q = p->primeiro;

    while (q != NULL) {
        int id = q->id;
        q = q->proximo_vizinho;
        retira_aresta(g, id, no);
    }

    if (ant == NULL) {
        g = g->proximo;
    } else {
        ant->proximo = p->proximo;
    }

    free(p);
    return g;
}

void retira_aresta(Grafo *g, int id1, int id2) {
    Grafo *p = busca(g, id1), *q = busca(g, id2);

    if ((p == NULL) || (q == NULL)) {
        return;
    }

    Vizinho *viz = p->primeiro, *ant = NULL;

    while ((viz != NULL) && (viz->id != id2)) {
        ant = viz;
        viz = viz->proximo_vizinho;
    }

    if (viz == NULL) {
        return;
    }

    if (ant == NULL) {
        p->primeiro = p->primeiro->proximo_vizinho;
    } else {
        ant->proximo_vizinho = viz->proximo_vizinho;
    }

    free(viz);

    viz = q->primeiro;
    ant = NULL;

    while ((viz != NULL) && (viz->id != id1)) {
        ant = viz;
        viz = viz->proximo_vizinho;
    }

    if (viz == NULL) {
        return;
    }

    if (ant == NULL) {
        q->primeiro = q->primeiro->proximo_vizinho;
    } else {
        ant->proximo_vizinho = viz->proximo_vizinho;
    }

    free(viz);
}

int qtd_nos(Grafo *g) {
    int cont = 0;
    Grafo *p = g;

    while(p != NULL) {
        p = p->proximo;
        cont++;
    }

    return cont;
}

void gera_html(Grafo *g) {
    if(g == NULL) {
        printf("GRAFO VAZIO");
    } else {
        Grafo *p = g;
        int qnos, i, j, lin, col;
        qnos = qtd_nos(p);
        int nos[qnos];
        char info[50];
        FILE *html, *arqPart1, *arqPart2;
        arqPart1 = fopen("html/p1.txt","r");
        arqPart2 = fopen("html/p2.txt","r");
        html = fopen("grafo.html","w");

        //gravando primeira parte do arquivo HTML
        while((fgets(info, sizeof(info), arqPart1)) != NULL) {
            fprintf(html, "%s", info);
        }

        //Percorre o grafo e salva cada ligação e nó
        while (p != NULL) {
            fprintf(html, "{source: \"%d\", target: \"%d\"},\n", p->id,p->id);
            Vizinho *q = p->primeiro;

            while (q != NULL) {
                if (q->proximo_vizinho) {
                    fprintf(html, "{source: \"%d\", target: \"%d\"},\n", p->id,q->id);
                } else {
                   fprintf(html, "{source: \"%d\", target: \"%d\"},\n", p->id,q->id);
                }

                q = q->proximo_vizinho;
            }

            p = p->proximo;
    }

        //gravando segunda parte do arquivo HTML
        while((fgets(info, sizeof(info), arqPart2)) != NULL) {
			fprintf(html, "%s", info);
        }

        fclose(arqPart1);
        fclose(arqPart2);
        fclose(html);
        system("grafo.html");
    }
 }

void libera(Grafo *g) {
    Grafo *p = g;

    while (p != NULL) {
        Vizinho *v = p->primeiro;

        while (v != NULL) {
            Vizinho *q = v;
            v = v->proximo_vizinho;
            free(q);
        }

        Grafo *r = p;
        p = p->proximo;
        free(r);
    }
}

void imprime(Grafo *g) {
    Grafo *p = g;

    while (p != NULL) {
        printf("No: %d | Visitados: %d\n\n   Vizinhos: ", p->id, p->visitado);
        Vizinho *q = p->primeiro;

        while (q != NULL) {
            if (q->proximo_vizinho) {
                printf("%d, ",q -> id);
            } else {
                printf("%d\n",q -> id);
            }

            q = q->proximo_vizinho;
        }

        p = p->proximo;
        printf("\n\n");
    }
}

void zera_visitados(Grafo *g) {
    Grafo *p = g;

    while(p != NULL){
        p->visitado = 0;
        p = p->proximo;
    }
}

Grafo* copia(Grafo *g) {
    Grafo *p = g;
    Grafo *novo = inicializa();
    Grafo *copia = inicializa();

    if(p == NULL) return NULL;

    while (p != NULL) {
        int i = p->id;
        novo = insere_no(novo, i);
        Vizinho *q = p->primeiro;

        while (q != NULL) {
            if (q->proximo_vizinho != NULL) {
               insere_aresta(novo, p->id, q->id);
            } else {
               insere_aresta(novo, p->id, q->id);
            }

            q = q->proximo_vizinho;
        }

        p = p->proximo;
    }

    //copiando de volta na ordem certa
    while (novo != NULL) {
        int i = novo->id;
        copia = insere_no(copia, i);
        Vizinho *q = novo->primeiro;

        while (q != NULL) {
            if (q->proximo_vizinho != NULL) {
               insere_aresta(copia, novo->id, q->id);
            } else {
               insere_aresta(copia, novo->id, q->id);
            }

            q = q->proximo_vizinho;
        }

        novo = novo->proximo;
    }

    libera(novo);
    return copia;
}

void pontes(Grafo *g) {
    Lista *t = inicializa_lista();
    Grafo *j = g;
    Grafo *p = g;

    while (p != NULL) {
        Vizinho *q = p->primeiro;

        while (q != NULL) {
            //Faz uma copia do grafo original, que será testado retirando a aresta em questão
            Grafo *clone = copia(j);

            //Depois de retirar a aresta marca os visiados do clone
            retira_aresta(clone ,p->id, q->id);
            conexidade(clone, clone);

            //Testa se o clone deixa de ser conexo e insere na lista a ligação
            if(conexo(clone) == 0) {
                //verifica se a ligação ja está na lista (Ex.: 10-8 = 8-10)
                if(busca_lista(t, p->id, q->id) == 0) {
                    t = insere(t, p->id,q->id);
                }
            }

            libera(clone);
            q = q->proximo_vizinho;
        }

        p = p->proximo;
    }

    //Percorre a lista escrevendo as pontes no arquivo
    FILE *pontes;
    int tam = tamanho(t);
    Lista *l_aux = t;
    pontes = fopen("pontes.txt", "w");
    fprintf(pontes, "%d \n", tam);

    while(l_aux != NULL) {
        fprintf(pontes, "%d %d \n", l_aux->id, l_aux->ligacao);
        l_aux = l_aux->proximo;
    }

    fclose(pontes);
    libera_lista(t);
    system("pontes.txt");
}

void conexidade(Grafo *g, Grafo *g1) {
    Grafo *p = g;
    Vizinho *v;
    Grafo *j;

    //Verifica se o grafo existe e se o nó já foi visitado
    if((p != NULL) && (p->visitado == 0)) {
        p->visitado = 1;
        v = p->primeiro;

        //Enquanto o nó tiver vizinhos, ele testa se o vizinho não foi visitado e chama a recursão
        while(v != NULL) {
            j = busca(g1, v->id);

            if((j != NULL) && (j->visitado == 0)) {
                conexidade(j, g1);
            }

            v = v->proximo_vizinho;
        }
    }
}

void salva(Grafo *g, char *nome){
    Lista *t = inicializa_lista();
    Lista *l2 = inicializa_lista();
    Grafo *j = g;
    Grafo *p = g;

    while (p != NULL) {
        //salva na Lista os nós
        l2 = insere(l2, p->id, 0);
        Vizinho *q = p->primeiro;

        while (q != NULL) {
            if (q->proximo_vizinho != NULL) {
               if(busca_lista(t, p->id, q->id) == 0) {
                    t = insere(t, p->id,q->id);
               }
            } else {
                if(busca_lista(t, p->id, q->id) == 0) {
                    t  = insere(t, p->id,q->id);
                }
            }

            q = q->proximo_vizinho;
        }

        p = p->proximo;
    }

    FILE *arq;
    arq = fopen(nome, "w");
    //primeira linha do arquivo: Quantidade de nós
    fprintf(arq, "%d\n", qtd_nos(j));

    Lista *l = t;
    Lista *l3 = l2;

    //salva no arquivo os nós
    while(l3 != NULL){
        fprintf(arq, "%d \n", l3->id);
        l3 = l3->proximo;
    }

    //salva no arquivo as ligaçoes;
    while(l != NULL){
        fprintf(arq, "%d %d \n", l->id, l->ligacao);
        l = l->proximo;
    }

    fclose(arq);
    libera_lista(t);
    libera_lista(l2);
    system(nome);
}

int conexo(Grafo *g) {
    int controle = 0;
    Grafo *auxiliar = g;

    while(auxiliar != NULL) {
        if(auxiliar->visitado == 1) {
            auxiliar = auxiliar->proximo;
        } else {
            controle = 1;
            break;
        }
    }

    if(controle == 0) {
        zera_visitados(g);
        return 1;
    } else {
        zera_visitados(g);
        return 0;
    }
}
