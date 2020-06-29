#ifndef grafo_matriz_H
    #define grafo_matriz_H
    #include "listaencad.h"

    typedef struct grafo GRAFO;
    typedef struct voo VOO;

    struct voo{
        int tempo;
        int custo;
    };

    struct grafo {
        int numVertices;
        int numArestas;
        VOO **matriz;
    };

    GRAFO *criar_grafo(int numVertices);
    GRAFO *freeGrafo(GRAFO *A);
    int InsereAresta(GRAFO* A, int V1, int V2, int tempo, int custo);
    int RetiraAresta(GRAFO* A, int V1, int V2);
    int ExisteAresta(GRAFO *A, int V1, int V2);
    int ImprimeGrafo(GRAFO *A);
    LISTA * dijkstra(GRAFO * A, int origem, int destino);

#endif
