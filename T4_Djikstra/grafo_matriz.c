#include <stdlib.h>
#include <stdio.h>
#include "grafo_matriz.h"

GRAFO *criar_grafo(int numVertices){
    GRAFO* A = (GRAFO*) malloc(sizeof(GRAFO*)); 
    if (A == NULL) return NULL;
    A->matriz = (VOO**)malloc(numVertices*sizeof(VOO*));

    if (A->matriz == NULL){
        free(A);
        return NULL;
    }

    for (int i = 0; i < numVertices; i++){
        A->matriz[i] = (VOO*) calloc(numVertices, sizeof(VOO));
        if (A->matriz[i] == NULL) { // não conseguiu alocar a linha i da matriz
            for (int k=0; k<i; k++) //libera todas a linhas alocadas
                free(A->matriz[k]); 
            free(A->matriz);
            free(A);
            return NULL;
        }
    }


    A->numVertices = numVertices;
    A->numArestas = 0;
    return A;
}

GRAFO *freeGrafo(GRAFO *A){
    if(A == NULL) return NULL;

    for (int i = 0; i < A->numVertices; i++)
        free(A->matriz[i]);

    free(A->matriz);
    free(A);
    A = NULL;
    return A;
}

int InsereAresta(GRAFO* A, int V1, int V2, int tempo, int custo){
    if (A == NULL) return -1;
    if (V1 < 0 || V1 > A->numVertices || V2 < 0 || V2 > A->numVertices) return -1;
    if (A->matriz[V1][V2].tempo != 0) return 0; //já existe aresta, pois não existe voo com tempo 0
    
    A->matriz[V1][V2].tempo = tempo;
    A->matriz[V1][V2].custo = custo;
    A->numArestas++;
    return 1;
}

int RetiraAresta(GRAFO* A, int V1, int V2){
    if (A == NULL) return -1;
    if (V1 < 0 || V1 > A->numVertices || V2 < 0 || V2 > A->numVertices) return -1;
    if (A->matriz[V1][V2].tempo == 0) return 0;
    A->matriz[V1][V2].tempo = 0;
    A->matriz[V1][V2].custo = 0;
    A->numArestas--;
    return 1;
}

int ExisteAresta(GRAFO *A, int V1, int V2){
    if (A == NULL) return -1;
    if (V1 < 0 || V1 > A->numVertices || V2 < 0 || V2 > A->numVertices) return -1;
    if (A->matriz[V1][V2].tempo == 0) return 0; //não existe aresta
    else return 1; //existe aresta
}

int ImprimeGrafo(GRAFO *A){
    if (A == NULL) 
        printf("\nO grafo não existe.");
    else{
        for (int i = 0; i < A->numVertices; i++){
            for (int j = 0; j < A->numVertices; j++){
                if (A->matriz[i][j].tempo != 0) printf("Voo de %d até %d: %d minutos, %d reais.\n", i, j, A->matriz[i][j].tempo, A->matriz[i][j].custo);
            }
            printf("\n");
        }
    }
    printf("\n");
}