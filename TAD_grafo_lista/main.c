#include <stdlib.h>
#include <stdio.h>
#include "listaencad.h"
#include "grafo_lista.h"

int main(){

    int m, n, V1, V2;
    scanf("%d", &n); //numero de vertices
    scanf("%d", &m); //numero de arestas que serão inseridas
    GRAFO *A = criar_grafo(n);

    for (int i = 0; i < m; i++){
        scanf("%d %d", &V1, &V2);
        InsereAresta(A, V1, V2);
    }

    int q, opt;
    scanf("%d", &q); //numero de operações 

    for (int j = 0; j < q; j++){
        scanf("%d", &opt);

        if (opt == 1){
            scanf("%d %d", &V1, &V2);
            InsereAresta(A, V1, V2);
        }

        if (opt == 2){
            scanf("%d %d", &V1, &V2);
            RetiraAresta(A, V1, V2);
        }

        if (opt == 3){
            ImprimeGrafo(A);
        }

    }

    freeGrafo(A);
    return 0;
}

// teste grafos:

    /*GRAFO *A = criar_grafo(4);
    if (A == NULL) return 1;

    printf("\n");
    InsereAresta(A, 2 ,3);
    InsereAresta(A, 2 ,2);
    InsereAresta(A, 3 ,1);
    ImprimeGrafo(A);
    return 0;*/

 // teste lista encadeada:

    /*LISTA* l;
    l = lista_criar();
    lista_inserir_ordenado(l, 1);
    lista_inserir_fim(l, 2);
    lista_imprimir(l);
    lista_apagar(l);
    return 0;*/