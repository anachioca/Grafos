#ifndef grafo_matriz_H
    #define grafo_matriz_H

    typedef struct grafo GRAFO;

    struct grafo {
        int numVertices;
        int numArestas;
        int **matriz;
    };

    GRAFO *criar_grafo(int numVertices);
    GRAFO *freeGrafo(GRAFO *A);
    int InsereAresta(GRAFO* A, int V1, int V2);
    int RetiraAresta(GRAFO* A, int V1, int V2);
    int ExisteAresta(GRAFO *A, int V1, int V2);
    int ImprimeGrafo(GRAFO *A);

#endif
