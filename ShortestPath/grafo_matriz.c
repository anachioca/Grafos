#include <stdlib.h>
#include <stdio.h>
#include "grafo_matriz.h"
#include "listaencad.h"

#define infinito 99999

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

void freeGrafo(GRAFO **A){
    if(*A == NULL) return;
    GRAFO * B = *A;

    for (int i = 0; i < B->numVertices; i++)
        free(B->matriz[i]);

    free(B->matriz);
    free(*A);
    A = NULL;
    return;
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

LISTA * listaAdjacencias(GRAFO *A, int V1){
    LISTA * lista = lista_criar();

    for (int i = 0; i < A->numVertices; i++){
        if (A->matriz[V1][i].tempo != 0){
            lista_inserir_fim(lista, i);
        }
    }
    return lista;
}

// relaxa a aresta entre V1 e V2
void relax(GRAFO * A, int * d, int * antecessor, LISTA * filaPrioridade, int V1, int V2){
    if (d[V2] > d[V1] + A->matriz[V1][V2].tempo){
        d[V2] = d[V1] + A->matriz[V1][V2].tempo;
        antecessor[V2] = V1;
        ordenaLista(filaPrioridade, d);
    }
} 

LISTA * dijkstra(GRAFO * A, int origem, int destino){
    int * antecessor =  malloc(A -> numVertices * sizeof(int));
    int * d = malloc(A->numVertices * sizeof(int));
    LISTA * processados = lista_criar();
    LISTA * filaPrioridade = lista_criar();
    lista_inserir_inicio(filaPrioridade, origem);
    int u;

    for (int i = 0; i < A -> numVertices; i++){
        antecessor[i] = -1;
        d[i] = infinito;
        if (i != origem ) lista_inserir_fim(filaPrioridade, i);
    }

    d[origem] = 0;

    while(!listaVazia(filaPrioridade)){
        u = dequeue(filaPrioridade);
        lista_inserir_fim(processados, u);
        for (int v = 0; v < A->numVertices; v++){
            if (A->matriz[u][v].tempo != 0) relax(A, d, antecessor, filaPrioridade, u, v);
        } 
    }

    LISTA * caminho = lista_criar();
    int node = destino;
    int custo = 0;

    while (node != -1){
        lista_inserir_inicio(caminho, node);
        node = antecessor[node];
    }

    lista_imprimir(caminho);
    int size = caminho->size;
    int aux = dequeue(caminho);
    int aux2;

    for (int i = 0; i < size-1; i++){
        aux2 = dequeue(caminho);
        custo += A->matriz[aux][aux2].custo;
        aux = aux2;
    }

    
    printf("%d %d", d[destino], custo);

    free(antecessor);
    free(d);
    free(caminho);
    lista_apagar(&processados);
    free(filaPrioridade);
}