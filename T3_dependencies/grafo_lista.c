#include <stdlib.h>
#include <stdio.h>
#include "grafo_lista.h"
#include "listaencad.h"

#define COR int
#define BRANCO 0
#define CINZA 1
#define PRETO 2

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

void freeGrafo(GRAFO *A){
    if(A == NULL) return;

    for (int i = 0; i < A->numVertices; i++){
         freeLista(A->lista[i]);
         free(A->lista[i]);
    }     

    free(A->lista);
    free(A);
    A = NULL;
}

int InsereAresta(GRAFO* A, int V1, int V2){  
    if (A == NULL) return -1;
    if (V1 < 0 || V1 > A->numVertices || V2 < 0 || V2 > A->numVertices) return -1;
    if (lista_existe_no(A->lista[V1], V2) == 1) return -1;
    
    lista_inserir_fim(A->lista[V1], V2);
    //if (V1 != V2) lista_inserir_fim(A->lista[V2], V1);

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
    //lista_remover(A->lista[V2], V1);

    A->numArestas--;
    return 1;
}

// procura arestas de retorno utilizando a busca em profundidade
int GrafoPossuiCiclo(GRAFO *A, GRAFO *B){
    COR * cor = calloc(A->numVertices,sizeof(COR));
    int * antecessor = malloc(A->numVertices*sizeof(int));
    int V;

    for (V= 0; V < A->numVertices; V++) {
        cor[V]= BRANCO;
        antecessor[V]= -1;
    }

    for (V= 0; V< A->numVertices; V++){
        if (cor[V] == BRANCO)
            if (visita_dfs(A, V, cor, antecessor, B) == 1) {
                free(cor);
                free(antecessor);
                return 1;
            }
    }

    free(cor);
    free(antecessor);
    return 0;
}

// retorna 1 se V1 eh descendente de V2
int ehDescendente(GRAFO *A, int V1, int V2){

    if (lista_existe_no( A->lista[V1], V2)) {
        return 1;
    }

    else{
        for (int i = 0; i < A->lista[V1]->size; i ++){
            if (ehDescendente(A, getItem(A->lista[V1], i), V2) == 1) return 1;;
        }
    }
    
    return 0;
}

int visita_dfs(GRAFO *A, int V, COR *cor, int antecessor[], GRAFO *B){
    int FimListaAdj, erro;
    NO *Adj, *Aux;
    cor[V]= CINZA;

    if (!ListaAdjVazia(A, V, &erro)) {
        Aux = PrimeiroListaAdj(A, V, &erro);
        FimListaAdj= 0;
        while (!FimListaAdj) {
            ProxAdj(A, &Adj, &Aux, &FimListaAdj, &erro);
            if (cor[Adj->item] == BRANCO) {
                antecessor[Adj->item]= V;
                if (visita_dfs(A, Adj->item, cor, antecessor, B) == 1) {
                    return 1;
                }   
            }
            // caso o nó adj já tenha sido visitado e seja ascendente do nó atual
            // trata-se de uma aresta de retorno -> grafo possui ciclo!
            else if (cor[Adj->item] == CINZA && ehDescendente(B, V, Adj->item)) return 1;    
        }
    }

    cor[V] = PRETO;
    return 0; 
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

/*retorna o vértice adjacente Adj (apontado por Prox) da lista de adjacentes
de V, bem como o peso associado à aresta V-Adj, e posiciona Prox no próximo
vértice adjacente; FimListaAdj retorna 1 se o final da lista foi encontrado
esta é uma função interna ao TAD Grafo
*/
void ProxAdj(GRAFO *A, NO **Adj, NO **Prox, int *FimListaAdj, int *erro) {
     *erro=0;
     *Adj=*Prox;
     *Prox=(*Prox)->prox;
     if (*Prox==NULL)
        *FimListaAdj=1;
}

/* retorna o endereço do primeiro vértice na lista de adjacentes de V
   esta é uma função interna ao TAD Grafo
*/
NO* PrimeiroListaAdj(GRAFO *A, int V, int *erro) {
    if (V > A->numVertices) {
       *erro=1;
       return(NULL);
    }
    else {
        *erro=0;
        return ( NoInicial(A->lista[V]) );
    }
}

/*função que verifica se um vértice não tem vizinhos, assumindo a E.D. anterior
  essa função faz parte do TAD Grafo!!
*/
int ListaAdjVazia(GRAFO *A, int V, int *erro) {
    if (V > A->numVertices) {
       *erro=1;
       return(1);
    }
    else {
         *erro=0;
         if (NoInicial(A->lista[V]) == NULL) return(1);
         else return(0);
    }
}