#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "lista.h"

int main (int argc, char *argv[]) {
    Grafo *teste = inicializa();
    Grafo *auxiliar;

    int tamanhoDoGrafo = 0;
    int no;
    int no1;
    int no2;
    char info[50];
    char saida[80];
    strcpy (saida, "novo_");
    strcat (saida, argv[1]);
    FILE *html, *arqPart1, *arqPart2;

    FILE *arq;
	arq = fopen(argv[1], "r");

	if (arq == NULL) {
	    printf("Erro, nao foi possivel abrir o arquivo\n");
	    exit(1);
    }

    // Lê a primeira linha do arquivo que é a quantidade de nós que o grafo tem.
    fscanf(arq, "%d", &tamanhoDoGrafo);

    // Lê todas as linhas que representam cada nó e os insere no grafo.
    int i;
    for (i = 0; i < tamanhoDoGrafo; i++) {
        fscanf(arq, "%d", &no);
        teste = insere_no(teste, no);
    }

    // Lê todas as linha do arquivo que representam as arestas e as insere no grafo.
    while (fscanf(arq, "%d %d", &no1, &no2) != EOF) {
        insere_aresta(teste, no1, no2);
    }

   //interação con usuario//
    int n,a1,a2,r,t1,t2;
    char usuario;
    char linha = '\0';
    printf("<GRAFOS - ED I (2014.1) - Romulo, Leonardo e Thiago> \n");
    printf("       PRESSIONE ENTER PARA INICIAR \n");

    do {
        scanf("%c", &linha);

        printf("-----------------MENU-------------\n");
        printf("Digite: \n \n \n 'i' para INSERIR um NO \n \n 'a' para INSERIR uma ARESTA \n \n 'r' para REMOVER um NO \n \n ");
        printf("'t' para REMOVER uma ARESTA \n \n 'c' para TESTAR CONEXIDADE  \n \n 'g' para SALVAR o GRAFO modificado no arquivo  \n \n 'p' para GERAR visualmente o GRAFO atual  \n \n");
        printf(" 's' para SAIR \n \n");
        printf("----------------------------------\n \n");
        printf("\n");
        printf("ENTRADA: ");
        scanf("%c", &usuario);
        if((usuario == 'i') || (usuario == 'a') || (usuario == 'r') || (usuario == 't') || (usuario == 'c') || (usuario == 's') || (usuario == 'p') || (usuario == 'g')) {
            switch(usuario){
                case 'i':
                    printf("No: ");
                    scanf("%d", &n);
                    printf("\n ");
                    teste = insere_no(teste, n);

                    break;
                case 'a':
                    printf("No A: ");
                    scanf("%d", &a1);
                    printf("No B: ");
                    scanf("%d", &a2);
                    insere_aresta(teste, a1, a2);

                    break;
                case 'r':
                    printf("No: ");
                    scanf("%d", &r);
                    teste = retira_no(teste, r);

                    break;
                case 'p':
                    gera_html(teste);

                    break;
                case 't':
                    printf("No A: ");
                    scanf("%d", &t1);
                    printf("No B: ");
                    scanf("%d", &t2);
                    retira_aresta(teste, t1, t2);

                    break;
                case 'g':
                    salva(teste, saida);

                    break;
                case 'c':
                    zera_visitados(teste);
                    conexidade(teste, teste);

                    if(conexo(teste) == 1) {
                        printf("Grafo conexo\n");
                        pontes(teste);
                    } else {
                        printf("Grafo nao conexo\n");
                        Lista *l = inicializa_lista();
                        l = componentes(teste, teste, 1, l);
                    }

                    break;
            }
       } else {
            printf("<<<ENTRADA INVALIDA>>>\n \n");
       }
    } while(usuario != 's');

    libera(teste);
    return 0;
}
