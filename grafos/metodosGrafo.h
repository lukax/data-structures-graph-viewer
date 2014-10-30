#ifndef METODOSGRAFO_H_INCLUDED
#define METODOSGRAFO_H_INCLUDED
#include "grafo.h"


TGrafo* inicializa(void) {
    return NULL;
}

TGrafo* busca(TGrafo* g, int elem) {
    TGrafo *p = g;

    while ((p) && (p-> id != elem)) {
        p = p->prox;
    }

    return p;
}

TGrafo* insere_no(TGrafo* g, int no) {
    if (busca(g,no)) {
        return g;
    }

    TGrafo *novo = (TGrafo*)malloc(sizeof(TGrafo));
    novo -> id = no;
    novo -> prim = NULL;
    novo -> prox = g;
    novo->visitado = 0;

    return novo;
}

void insere_aresta(TGrafo* g, int no1, int no2) {
    TGrafo *p = busca(g,no1);
    TGrafo *q = busca(g,no2);

    if ((!p)|| (!q)) {
        return;
    }

    TViz *novo = (TViz*)malloc(sizeof(TViz));
    novo -> id = no2;
    //novo -> custo = custo;
    novo -> prox_viz = p->prim;
    p -> prim = novo;

    novo = (TViz*)malloc(sizeof(TViz));
    novo -> id = no1;
    //novo -> custo = custo;
    novo -> prox_viz = q ->prim;
    q -> prim = novo;
}

TGrafo *retira_no(TGrafo *g , int elem) {
    TGrafo *p = g, *ant = NULL;

    while ((p) && (p -> id != elem)) {
        ant = p;
        p = p->prox;
    }

    if (!p) {
        return g;
    }

    TViz *q = p -> prim;

    while (q) {
        int id = q -> id;
        q = q -> prox_viz;
        retira_aresta(g,id,elem);
    }

    if (!ant) {
        g = g->prox;
    } else {
        ant->prox = p -> prox;
    }

    free(p);
    return g;
}

void retira_aresta(TGrafo*g, int id1, int id2) {
    TGrafo *p = busca(g,id1), *q = busca(g,id2);

    if ((!p) || (!q)) {
        return;
    }

    TViz *viz = p -> prim, *ant = NULL;

    while ((viz) && (viz -> id != id2)) {
        ant = viz;
        viz = viz ->prox_viz;

    }

    if (!viz) {
        return;
    }

    if (!ant) {
        p -> prim = p -> prim -> prox_viz;
    } else {
        ant -> prox_viz = viz -> prox_viz;
    }

    free(viz);

    viz = q -> prim;
    ant = NULL;

    while ((viz) && (viz -> id != id1)) {
        ant = viz;
        viz = viz -> prox_viz;
    }

    if (!viz) {
        return;
    }

    if (!ant) {
        q -> prim = q -> prim -> prox_viz;
    } else {
        ant -> prox_viz = viz -> prox_viz;
    }

    free(viz);
}

int qtd_nos(TGrafo*g){

    int cont=0;
    TGrafo* p = g;
    while(p){
        p = p->prox;
        cont++;
    }
    return cont;

}

 void gera_html(TGrafo*g){
    if(!g){
        printf("GRAFO VAZIO");
    } else{
        TGrafo * p = g;
        int qnos, i, j, lin, col;
        int**adj;
        qnos = qtd_nos(p);
        int nos[qnos];
        char info[50];
        FILE *html, *arqPart1, *arqPart2;
        arqPart1 = fopen("html/p1.txt","r");
        arqPart2 = fopen("html/p2.txt","r");
        html = fopen("grafo.html","w");

        //gravando primeira parte do arquivo HTML
        while( (fgets(info, sizeof(info), arqPart1))!=NULL )
            fprintf(html, "%s", info);

        //Percorre o grafo e salva cada ligação e nó
        while (p) {
            fprintf(html, "{source: \"%d\", target: \"%d\"},\n", p->id,p->id);
            TViz *q = p -> prim;
        while (q) {
            if (q -> prox_viz) {
                fprintf(html, "{source: \"%d\", target: \"%d\"},\n", p->id,q->id);
            } else {
               fprintf(html, "{source: \"%d\", target: \"%d\"},\n", p->id,q->id);
            }

            q = q -> prox_viz;

        }

        p = p -> prox;

    }

        //gravando segunda parte do arquivo HTML
        while( (fgets(info, sizeof(info), arqPart2))!=NULL )
			fprintf(html, "%s", info);

        fclose(arqPart1);
        fclose(arqPart2);
        fclose(html);
        system("grafo.html");
    }
 }

void libera(TGrafo *g) {
    TGrafo *p = g;

    while (p) {
        TViz *v = p -> prim;

        while (v) {
            TViz *q = v;
            v = v -> prox_viz;
            free(q);
        }

        TGrafo *r = p;
        p = p -> prox;
        free(r);
    }
}

void imprime(TGrafo *g){
    TGrafo *p = g;

    while (p) {
        printf("No: %d | Visitados: %d\n\n   Vizinhos: ", p->id, p->visitado);
        TViz *q = p -> prim;

        while (q) {
            if (q -> prox_viz) {
                printf("%d, ",q -> id);
            } else {
                printf("%d\n",q -> id);
            }

            q = q -> prox_viz;
        }

        p = p -> prox;
        printf("\n\n");
    }
}

void zera_visitados(TGrafo* g){

    TGrafo * p = g;
    while(p){
        p->visitado = 0;
        p = p->prox;
    }
}

TGrafo* copia(TGrafo*g){
    TGrafo * p = g;
    TGrafo * novo = inicializa();
    TGrafo * copia = inicializa();
    if(!p)return NULL;
    while (p) {
        int i = p->id;
        novo = insere_no(novo,i);
        TViz *q = p -> prim;
    while (q) {
            if (q -> prox_viz) {
               insere_aresta(novo,p->id,q->id);
            } else {
               insere_aresta(novo,p->id,q->id);
            }
            q = q -> prox_viz;
        }
        p = p -> prox;

    }

    //copiando de volta na ordem certa
       while (novo) {
        int i = novo->id;
        copia = insere_no(copia,i);
        TViz *q = novo -> prim;
    while (q) {
            if (q -> prox_viz) {
               insere_aresta(copia,novo->id,q->id);
            } else {
               insere_aresta(copia,novo->id,q->id);
            }
            q = q -> prox_viz;
        }
        novo = novo -> prox;
       }
       libera(novo);
    return copia;
}

void pontes(TGrafo*g) {
   TL* t = inicializa_lista();
   TGrafo *j = g;
   TGrafo * p = g;

   while (p) {
        TViz *q = p -> prim;

    while (q) {
        //Faz uma copia do grafo original, que será testado retirando a aresta em questão
         TGrafo * clone = copia(j);
         //Depois de retirar a aresta marca os visiados do clone
         retira_aresta(clone,p->id,q->id);
         conexidade(clone, clone);
         //Testa se o clone deixa de ser conexo e insere na lista a ligação
         if(testar_conexo(clone)==0) {
           //verifica se a ligação ja está na lista (Ex.: 10-8 = 8-10)
           if(busca_na_lista(t, p->id, q->id)==0)
           t = insere_na_lista(t, p->id,q->id);

         }
        libera(clone);
        q = q -> prox_viz;
        }
        p = p -> prox;
    }

    //Percorre a lista escrevendo as pontes no arquivo
   FILE *pontes;
   int tam = tam_lista(t);
   TL* l_aux = t;
    pontes = fopen("pontes.txt", "w");
    fprintf(pontes, "%d \n", tam);
    while(l_aux){
        fprintf(pontes, "%d %d \n", l_aux->id, l_aux->ligacao);
        l_aux = l_aux->prox;
    }


    fclose(pontes);
    libera_lista(t);
    system("pontes.txt");

}

void conexidade(TGrafo *g,TGrafo *g1){

    TGrafo *p = g;
    TViz * v;
    TGrafo *j;
    //Verifica se o grafo existe e se o nó já foi visitado
    if((p)&&(p->visitado==0)){
        p->visitado = 1;
        v = p->prim;
        //Enquanto o nó tiver vizinhos, ele testa se o vizinho não foi visitado e chama a recursão
        while(v){

            j = busca(g1,v->id);
            if((j)&&(j->visitado==0)){
                conexidade(j,g1);
            }
                v=v->prox_viz;
            }
    }
}

void salva_grafo(TGrafo*g, char* nome){
   TL* t = inicializa_lista();
   TL* l2 = inicializa_lista();
   TGrafo *j = g;
   TGrafo * p = g;

   while (p) {
        //salva na Lista os nós
        l2 = insere_na_lista(l2,p->id,0);
        TViz *q = p -> prim;
        while (q) {
            if (q -> prox_viz) {
                   if(busca_na_lista(t, p->id, q->id)==0)
                   t = insere_na_lista(t, p->id,q->id);
            } else {
                    if(busca_na_lista(t, p->id, q->id)==0)
                    t  = insere_na_lista(t, p->id,q->id);

            }
            q = q -> prox_viz;
        }
        p = p -> prox;

   }
    FILE * arq;
    arq = fopen(nome,"w");
    //primeira linha do arquivo: Quantidade de nós
    fprintf(arq, "%d\n", qtd_nos(j));

    TL* l = t;
    TL* l3 = l2;
    //salva no arquivo os nós
       while(l3){
        fprintf(arq, "%d \n", l3->id);
        l3 = l3->prox;
    }
    //salva no arquivo as ligaçoes;
    while(l){
        fprintf(arq, "%d %d \n", l->id, l->ligacao);
        l = l->prox;
    }

    fclose(arq);
    libera_lista(t);
    libera_lista(l2);
    system(nome);
}

int testar_conexo(TGrafo *g) {
    int controle = 0;
    TGrafo * auxiliar = g;
    while(auxiliar)
    {
        if(auxiliar->visitado == 1)
        {
            auxiliar = auxiliar->prox;
        }
        else
        {
            controle = 1;
            break;
        }

    }
    if(controle == 0)
    {
        zera_visitados(g);
        return 1;

    }
    else
    {
        zera_visitados(g);
        return 0;
    }

}

#endif // METODOSGRAFO_H_INCLUDED
