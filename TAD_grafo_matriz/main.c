#include <stdlib.h>
#include <stdio.h>
#include "grafo_matriz.h"

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
}