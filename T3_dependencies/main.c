#include <stdlib.h>
#include <stdio.h>
#include "listaencad.h"
#include "grafo_lista.h"

// verifica se todas as tarefas já foram executadas
int finalizado(int *lista, int size){
    for (int i = 0; i < size; i++){
        if (lista[i] == 0) return 0;
    }
    return 1;
}

// deleta as arestas que representam dependências com vértices que já foram processados
void atualizaGrafo(GRAFO *A, int *lista){
    for (int i = 0; i < A->numVertices; i++){
        if (lista[i] == 1){
            for (int j = 0; j < A->numVertices; j++){
                if (lista_existe_no(A->lista[j], i)) lista_remover(A->lista[j], i);
            }
        }
    }
}

int main(){

    int m, n, V1, V2, count = 0;
    scanf("%d", &n); //numero de vertices
    scanf("%d", &m); //numero de arestas que serão inseridas
    GRAFO *A = criar_grafo(n); // grafo invertido
    GRAFO *B = criar_grafo(n); // grafo normal
    int * executado = (int*) calloc(n, sizeof(int));

    for (int i = 0; i < m; i++){
        scanf("%d %d", &V1, &V2);
        InsereAresta(A, V2, V1); // preenche o grafo ao contrário!
        InsereAresta(B, V1, V2); // preenche o grafo normal
    }

    if (GrafoPossuiCiclo(B, A)){
        printf("%d", -1);
        free(executado);
        freeGrafo(A);
        freeGrafo(B);
        return 0;     
    }

    while (!finalizado(executado, n)){

        // para cada atividade, caso sua lista de dependências esteja vazia, executá-la
        for (int i = 0; i < n; i++){
            
            if (A->lista[i]->size == 0){
                executado[i] = 1;
            }
        }
        
        atualizaGrafo(A, executado);
        count++;
    }

    printf("%d", count);

    free(executado);
    freeGrafo(B);
    freeGrafo(A);
    return 0;    
}