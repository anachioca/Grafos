#include "listaencad.h"
#include "grafo_lista.h"
#include <stdlib.h>
#include <stdio.h>


LISTA *lista_criar(void){
    LISTA *lista = (LISTA*)malloc(sizeof(LISTA));
    if (lista != NULL){
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->size = 0;
    }
    return lista;
}

int lista_inserir_fim(LISTA *lista, int i){
    NO *p = (NO*)malloc(sizeof(NO));
    p->item = i;
    if (lista != NULL){
        if (lista->inicio == NULL){ //se for o primeiro elemento a ser inserido
            p->prox = NULL;
            lista->inicio = p;
        }
        else {
            lista->fim->prox = p;
            p->prox = NULL;
        }
        lista->fim = p;
        lista->size++;
        return 1;
    }
    return 0;
}

int lista_inserir_ordenado(LISTA *lista, int chave){
    NO *n = (NO*)malloc(sizeof(NO));
    n->item = chave;
    if (lista->inicio == NULL){ //se for o primeiro elemento a ser inserido
        lista->inicio = n;
        n->prox = NULL;
        lista->size++;
        return 0;
    }

    NO *p = lista->inicio;
    NO *q;

    if (p->item > chave) {
        lista->inicio = n;
        n->prox = p;
        lista->size++;
        return 0;
    }    
       
    else{
        for (p = lista->inicio; p != (lista->fim->prox); p = p->prox){
            if (p->item > chave){
                q->prox = n;
                n->prox = p;
                lista->size++;
                return 0;
            }
            q = p;
        }
    }

    if(lista->fim->item < chave){
        lista->fim->prox = n;
        lista->fim = n;
        n->prox = NULL;
        lista->size++;
        return 0;
    }

    return -1;
}

void lista_apagar(LISTA *l){
    NO* aux = l->inicio;
    while (aux != l->fim->prox){
        free(aux);
        aux = aux->prox;
    }
    free(l);
}

int lista_remover(LISTA *lista, int chave){
    NO *p = lista->inicio;
    NO *q;
    if (p->item == chave) {
        lista->inicio = p->prox;
        lista->size--;
        free(p);
        return 1;
    }    
       
    else{
        for (p = lista->inicio; p != (lista->fim->prox); p = p->prox){
            if (p->item == chave){
                if (p == lista->fim) lista->fim = q;
                else {
                    q->prox = p->prox;
                }
                lista->size--;
                free(p);
                return 1;
            }
            q = p;
        }
    }
    
    return 0;
}

int lista_existe_no(LISTA *l, int chave){
    NO* aux = l->inicio;
    int i = 0;
    while (i < l->size){
        if(aux->item == chave){
            return 1;
        }
        aux = aux->prox;
        i++;
    }
    return 0;
}

NO * NoInicial(LISTA *l){
    return l->inicio;
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

int getItem(LISTA *lista, int pos){
    NO* aux = lista->inicio;
    int i = 0;
    if (i > lista->size) return -1;
    while (i < pos){
        aux = aux->prox;
        i++;
    }
    return aux->item;
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

void lista_imprimir(LISTA *l){
    NO* aux = l->inicio;
    int i = 0;
    while (i < l->size){
        printf("%d ", aux->item);
        aux = aux->prox;
        i++;
    }
    printf("\n");
}