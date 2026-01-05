//
// Created by Luca on 14/06/2023.
//

#ifndef SKIPLISTEXERCISE_SKIPLIST_H
#define SKIPLISTEXERCISE_SKIPLIST_H
#include <stddef.h>


struct SkipList {
    struct Node **heads;
    size_t max_level;
    size_t max_height;
    int (*compare)(const void*, const void*);
};

struct Node {
    struct Node **next;
    size_t size;
    void *item;
};


// Funzione che crea una nuova struttura SkipList vuota con altezza massima e funzione di confronto specificati.
void new_skiplist(struct SkipList **list, size_t max_height,     int (*compare)(const void*, const void*));
// Funzione che svuota la SkipList, liberando la memoria occupata dai nodi.
void clear_skiplist(struct SkipList **list);
// Funzione che inserisce un nuovo elemento nella SkipList.
void insert_skiplist(struct SkipList *list, void *item);
// Funzione che cerca un elemento nella SkipList e restituisce il puntatore all'elemento trovato o NULL se non presente.
const void* search_skiplist(struct SkipList *list, void *item);

#endif //SKIPLISTEXERCISE_SKIPLIST_H
