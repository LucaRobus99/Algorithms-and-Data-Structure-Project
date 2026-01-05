#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "time.h"
int main(int argc, char* argv[]) {
    if (argc < 5) {
        printf("Inserire tutti i campi: %s <input_file> <output_file> <k> <field>\n", argv[0]);
        return 1;
    }
   
    char* input_file = argv[1];
    char* output_file = argv[2];
    size_t k =(size_t) atoi(argv[3]);
    size_t field =(size_t) atoi(argv[4]);
    FILE* file1= fopen(input_file, "r");
    FILE* file2= fopen(output_file, "w");
   
    clock_t start = clock();
      sort_records(file1, file2, k, field);
     clock_t end = clock();
    printf("\nTempo di esecuzione =  %f secondi \n", ((double)(end - start)) / CLOCKS_PER_SEC);

    return 0;
}
