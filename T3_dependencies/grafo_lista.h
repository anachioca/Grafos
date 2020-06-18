#ifndef grafo_matriz_H
    #define grafo_matriz_H
    #include "listaencad.h"

    typedef struct grafo GRAFO;
    typedef struct no_ NO;
    typedef struct lista_ LISTA;

    #define COR int
    #define BRANCO 0
    #define CINZA 1
    #define PRETO 2

    struct grafo {
        int numVertices;
        int numArestas;
        LISTA **lista; 
    };

    GRAFO *criar_grafo(int numVertices);
    void freeGrafo(GRAFO *A);
    int InsereAresta(GRAFO* A, int V1, int V2);
    int RetiraAresta(GRAFO* A, int V1, int V2);
    int GrafoPossuiCiclo(GRAFO *A, GRAFO *B);
    int ExisteAresta(GRAFO *A, int V1, int V2);
    int ehDescendente(GRAFO *A, int V1, int V2);
    int visita_dfs(GRAFO *A, int V, COR *cor, int antecessor[], GRAFO *B);
    int ImprimeGrafo(GRAFO *A);
    void ProxAdj(GRAFO *A, NO **Adj, NO **Prox, int *FimListaAdj, int *erro) ;
    NO* PrimeiroListaAdj(GRAFO *A, int V, int *erro) ;
    int ListaAdjVazia(GRAFO *A, int V, int *erro);

#endif