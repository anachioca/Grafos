#include "listaencad.h"
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

int lista_inserir_inicio(LISTA *lista, int i){
    NO *p = (NO*)malloc(sizeof(NO));
    p->item = i;
    if (lista != NULL){
        if (lista->inicio == NULL){ //se for o primeiro elemento a ser inserido
            p->prox = NULL;
            lista->fim = p;
        }
        else {
            p->prox = lista->inicio;
        }
        lista->inicio= p;
        lista->size++;
        return 1;
    }
    return 0;
}

int lista_inserir_ordenado(LISTA *lista, int chave, int *d){
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

    if (d[p->item] > d[chave]) {
        lista->inicio = n;
        n->prox = p;
        lista->size++;
        return 0;
    }    
       
    else{
        for (p = lista->inicio; p != (lista->fim->prox); p = p->prox){
            if (d[p->item] > d[chave]){
                q->prox = n;
                n->prox = p;
                lista->size++;
                return 0;
            }
            q = p;
        }
    }

    if(d[lista->fim->item] < d[chave]){
        lista->fim->prox = n;
        lista->fim = n;
        n->prox = NULL;
        lista->size++;
        return 0;
    }

    return -1;
}

void lista_apagar(LISTA ** l){
    if (*l == NULL) return;
    LISTA * lista = *l;
    NO* aux = lista->inicio;
    while (aux != lista->fim->prox){
        free(aux);
        aux = aux->prox;
    }
    free(lista);
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

void swap(int *xp, int *yp) { 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

void bubbleSort(int arr[], int n, int *d) { 
   int i, j; 
   for (i = 0; i < n-1; i++)       
     
       for (j = 0; j < n-i-1; j++)  
           if (d[arr[j]] > d[arr[j+1]]) 
              swap(&arr[j], &arr[j+1]); 
} 

// ordena a lista de acordo com o vetor d[]
void ordenaLista(LISTA *l, int *d){
    int * lista = malloc(l->size * sizeof(int));
    int size = l->size;
    for (int i = 0; i < size; i++){
        lista[i] = dequeue(l);
    }
    bubbleSort(lista, size, d);
    for (int i = 0; i < size; i++){
        lista_inserir_fim(l, lista[i]);
    }
    free(lista);
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

int listaVazia(LISTA *l){
    if (l->size == 0) return 1;
    else return 0;
}

// remove o primeiro elemento da lista (como uma fila)
int dequeue(LISTA *l){
    int aux = l->inicio->item;
    lista_remover(l, aux);
    return aux;
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