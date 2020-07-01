#include <stdlib.h>
#include <stdio.h>
#include "grafo_matriz.h"
#include "listaencad.h"

int main(){
    int nCidades, nVoos, V1, V2, tempo, custo, origem, destino;
    scanf("%d", &nCidades); //numero de vertices
    scanf("%d", &nVoos); //numero de arestas que serão inseridas
    GRAFO *A = criar_grafo(nCidades);

    // preenchendo o grafo
    for (int i = 0; i < nVoos; i++){
        scanf("%d %d %d %d", &V1, &V2, &tempo, &custo);
        InsereAresta(A, V1, V2, tempo, custo);
    }

    scanf("%d %d", &origem, &destino);
    dijkstra(A, origem, destino); // calculando o menor caminho

    freeGrafo(&A);
    return 0;
}