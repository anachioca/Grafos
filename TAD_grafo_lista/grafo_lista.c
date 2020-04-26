#include <stdlib.h>
#include <stdio.h>
#include "grafo_lista.h"
#include "listaencad.h"


GRAFO *criar_grafo(int numVertices){
    GRAFO* A = (GRAFO*) malloc(sizeof(GRAFO)); 
    if (A == NULL) return NULL;
    A->lista = (LISTA**)malloc(numVertices*sizeof(LISTA*));

    if (A->lista == NULL){
        free(A);
        return NULL;
    }

    for (int i = 0; i < numVertices; i++){
        A->lista[i] = lista_criar();
    }

    A->numVertices = numVertices;
    A->numArestas = 0;
    return A;
}

GRAFO *freeGrafo(GRAFO *A){
    if(A == NULL) return NULL;

    for (int i = 0; i < A->numVertices; i++)
        free(A->lista[i]);

    free(A->lista);
    free(A);
    A = NULL;
    return A;
}

int InsereAresta(GRAFO* A, int V1, int V2){  
    if (A == NULL) return -1;
    if (V1 < 0 || V1 > A->numVertices || V2 < 0 || V2 > A->numVertices) return -1;
    if (lista_existe_no(A->lista[V1], V2) == 1) return -1;
    
    lista_inserir_fim(A->lista[V1], V2);
    if (V1 != V2) lista_inserir_fim(A->lista[V2], V1);

    // Caso queira inserir os vértices de maneira ordenada:
    // Lembrar do problema (não inserir desse modo se for o primeiro a ser inserido)
    
    //lista_inserir_ordenado(A->lista[V1], V2);
    //if (V1 != V2) lista_inserir_ordenado(A->lista[V2], V1);
    

    A->numArestas++;
    return 1;
}

int RetiraAresta(GRAFO* A, int V1, int V2){
    if (A == NULL) return -1;
    if (V1 < 0 || V1 > A->numVertices || V2 < 0 || V2 > A->numVertices) return -1;
    
    lista_remover(A->lista[V1], V2);
    lista_remover(A->lista[V2], V1);

    A->numArestas--;
    return 1;
}

int ImprimeGrafo(GRAFO *A){
    if (A == NULL) 
        printf("\nO grafo não existe.");
    else{
        for (int i = 0; i < A->numVertices; i++){
            printf("%d: ", i);
            lista_imprimir(A->lista[i]);
        }
    }
    printf("\n");
}