#ifndef listaencad_H
    #define listaencad_H
 
    typedef struct no_ NO;
    typedef struct lista_ LISTA;

    struct no_{
        int item;
        NO* prox;
    };

    struct lista_{
        NO* inicio;
        NO* fim;
        int size;
    };

    LISTA *lista_criar(void);
    int lista_inserir_fim(LISTA *lista, int i);
    int lista_inserir_ordenado(LISTA *lista, int i);
    void lista_apagar(LISTA *lista);
    int lista_remover(LISTA *lista, int chave);
    int lista_existe_no(LISTA *l, int chave);
    void lista_imprimir(LISTA *l);


#endif