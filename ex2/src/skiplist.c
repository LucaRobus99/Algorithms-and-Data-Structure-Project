#include <stdlib.h>
#include <stdio.h>
#include "skiplist.h"


void new_skiplist(struct SkipList **list, size_t max_height, int (*compare)(const void*, const void*))
{
    if(compare==NULL)
	return;
    *list = (struct SkipList*)malloc(sizeof(struct SkipList));
    if (*list == NULL) {
        // Gestione dell'errore di allocazione della struttura SkipList
        fprintf(stderr, "Errore di allocazione della struttura SkipList.\n");
        exit(EXIT_FAILURE);
    }

    (*list)->heads = (struct Node**)malloc(max_height * sizeof(struct Node*));
    if ((*list)->heads == NULL) {
        // Gestione dell'errore di allocazione dell'array di puntatori heads
        fprintf(stderr, "Errore di allocazione dell'array di puntatori heads.\n");
        exit(EXIT_FAILURE);
    }

    // Inizializzazione dei puntatori heads a NULL
    for (size_t i = 0; i < max_height; i++) {
        (*list)->heads[i] = NULL;
    }

    // Impostazione dell'altezza massima e della funzione di confronto
    (*list)->max_level = 0;
    (*list)->max_height = max_height;
    (*list)->compare = compare;
}


size_t random_level(size_t max_height) {
    size_t lvl = 1;

    double randomValue = (double)rand() / RAND_MAX;

    while (randomValue < 0.5 && lvl < max_height) {
        lvl++;
        randomValue = (double)rand() / RAND_MAX;
    }

    return lvl;
}

static struct Node* createNode(void *item, size_t size) {
    struct Node *nodo = malloc(sizeof(struct Node));
    if (nodo == NULL) {
        // Gestione dell'errore di allocazione del nodo
        fprintf(stderr, "Errore di allocazione del nodo.\n");
        exit(EXIT_FAILURE);
    }

    nodo->next = malloc(size * sizeof(struct Node*));
    if (nodo->next == NULL) {
        // Gestione dell'errore di allocazione dell'array next
        fprintf(stderr, "Errore di allocazione dell'array next del nodo.\n");
        exit(EXIT_FAILURE);
    }

    nodo->size = size;
    nodo->item = item;

    return nodo;
}


void insert_skiplist(struct SkipList *list, void *item) {
    if(list==NULL){
        return;
    }

    struct Node* new_node = createNode(item, random_level(list->max_height));
    if (new_node->size > list->max_level)
        list->max_level = new_node->size;

    struct Node** x = list->heads;
    for (int i =(int) list->max_level - 1; i >= 0; i--) {
        if (x[i] == NULL || list->compare(item, x[i]->item) < 0) {
            if (i < ((int) new_node->size)) {
                new_node->next[i] = x[i];
                x[i] = new_node;
            }
        } else {
            x = x[i]->next;
            i++;
        }
    }
}


const void* search_skiplist(struct SkipList *list, void *item) {
    if(list==NULL){
        return NULL;
    }
    if (list->heads[0] == NULL) {
        // La SkipList è vuota
        return NULL;
    }

    struct Node** x = list->heads;


    for (int i = (int)list->max_level - 1; i >= 0; i--) {
        while (x[i]->next[i] != NULL && list->compare(x[i]->next[i]->item, item) <= 0) {
            x = x[i]->next;
        }
    }


    if (list->compare(x[0]->item, item) == 0) {
        return x[0]->item;
    } else {
        return NULL;
    }
}


void clear_skiplist(struct SkipList **list) {
    if (*list == NULL) {
        // SkipList non è stata inizializzata
        return;
    }

    // Liberazione dei nodi della SkipList
    struct Node** x = (*list)->heads;
    while (x[0] != NULL) {
        struct Node* temp = x[0];
        x[0] = x[0]->next[0];
        free(temp->next);
        free(temp);
    }

    // Liberazione dell'array di puntatori heads
    free((*list)->heads);

    // Liberazione della struttura SkipList
    free(*list);

    // Impostazione del puntatore list a NULL
    *list = NULL;
}

