#include "libsort.h"

#include <stdlib.h>
#include <string.h>

//metodo che esegue il binary_insertion_sort
static void binary_insertion_sort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *))
{

    char *base_ptr = (char *)base;

    for (size_t i = 1; i < nitems; i++)
    {
        size_t left = 0;
        size_t right = i;
        char *current = base_ptr + i * size;
        char temp[size];
        memcpy(temp, current, size);

        while (left < right)
        {
            size_t mid = left + (right - left) / 2;
            char *mid_ptr = base_ptr + mid * size;

            if (compar(mid_ptr, current) > 0)
                right = mid;
            else
                left = mid + 1;
        }

        memmove(base_ptr + (left + 1) * size, base_ptr + left * size, (i - left) * size);
        memcpy(base_ptr + left * size, temp, size);
    }
}
//metodo che esegue il merge
static void merge(void *base, size_t left, size_t mid, size_t right, size_t size, libsort_comparator compar) {
    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;

    
 
    char* L = malloc(n1 * size);
    char* R = malloc(n2 * size);

    memcpy(L, (char*)base + left * size, n1 * size);
    memcpy(R, (char*)base + (mid + 1) * size, n2 * size);

    size_t i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (compar(L + i * size, R + j * size) <= 0) {
            memcpy((char*)base + k * size, L + i * size, size);
            i++;
        } else {
            memcpy((char*)base + k * size, R + j * size, size);
            j++;
        }
        k++;
    }

    while (i < n1) {
        memcpy((char*)base + k * size, L + i * size, size);
        i++;
        k++;
    }

    while (j < n2) {
        memcpy((char*)base + k * size, R + j * size, size);
        j++;
        k++;
    }

    free(L);
    free(R);
     
}





//metodo che esegue il merge_binary_insertion_sort
 void merge_binary_insertion_sort(void *base, size_t nitems, size_t size, size_t k, libsort_comparator compar) {

    if(base==NULL||compar==NULL )return;

    if (nitems ==1) {
        return;
    } else if (nitems <= k) {
        binary_insertion_sort(base, nitems, size, compar);
              return;
    } 
        size_t mid = nitems / 2;

        merge_binary_insertion_sort(base, mid, size, k, compar);
        merge_binary_insertion_sort((char*)base + mid * size, nitems - mid, size, k, compar);

        merge(base, 0, mid - 1, nitems - 1, size, compar);
    


}




