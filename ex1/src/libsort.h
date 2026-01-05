#ifndef LIBSORT_H
#define LIBSORT_H

#include <stddef.h>
#include <stdio.h>
//alias del comparatore
typedef int (*libsort_comparator)(const void*, const void*);

//metodo per l'ordinamento dei reocords (nel infile) in base al campo e al k
//prende in input:due puntatori a file(input e output)e due size_t(k e field)
// restiusice un file(outfile)con all'interno tutti i record(del infile) ordinati in base al campo dato in input

void merge_binary_insertion_sort(void *base, size_t nitems, size_t size, size_t k, libsort_comparator compar);

#endif /* LIBSORT_H */
