#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "utils.h"


int main(int argc, char *argv[]) {
    if(argc<4){
        printf("inserire  percorso file input ,file di output e max_height");
        return 1;
    }

    FILE *dictionary;
    FILE *filetocorrect;
    dictionary= fopen(argv[1],"r");
    filetocorrect= fopen(argv[2],"r");
    size_t max_height = (size_t)strtoull(argv[3], NULL, 10);

    printf("Parole sbagliate all'interno del testo \n\n");
    clock_t start = clock();
    find_errors(dictionary,filetocorrect,max_height);
    clock_t end = clock();
    printf("\nTempo di esecuzione =  %f secondi \n", ((double)(end - start)) / CLOCKS_PER_SEC);

    return 0;
}



