
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libsort.h"
#include "getfile.h"
#include "utils.h"

// Resto del codice...


//Prende in input due puntaotri alla struttura record.
//Ritorna 1 se il campo Integer del primo reocord è più piccolo
//del campo Integer del secondo reocord(0 altrimenti)
static int compare_INT(const void* a, const void* b) {
    if(a==NULL){
        fprintf(stderr,"compare_INT il primo parametro è NULL");
        exit(EXIT_FAILURE);
    }
    if(b==NULL){
        fprintf(stderr,"compare_INT il secondo paremetro è NULL");
        exit(EXIT_FAILURE);
    }
    const Record *recordA = (const Record*)a;
    const Record *recordB = (const Record*)b;

    return recordA->field2 - recordB->field2;
}

//Prende in input due puntaotri alla struttura record.
//Ritorna 1 se il campo Float del primo reocord è più piccolo
//del campo Float del secondo reocord(0 altrimenti)
static int compare_FLOAT(const void* a, const void* b) {
    if(a==NULL){
        fprintf(stderr,"compare_FLOAT il primo parametro è NULL");
        exit(EXIT_FAILURE);
    }
    if(b==NULL){
        fprintf(stderr,"compare_FLOAT il secondo paremetro è NULL");
        exit(EXIT_FAILURE);
    }
    const Record *recordA = (const Record*)a;
    const Record *recordB = (const Record*)b;

    if (recordA->field3 < recordB->field3) return -1;
    if (recordA->field3 > recordB->field3) return 1;
    return 0;
}

//Prende in input due puntaotri alla struttura record.
//Ritorna 1 se il campo string del primo reocord è più corta
//del campo string del secondo reocord(0 altrimenti)
static int compare_STRING(const void* a, const void* b) {
    if(a==NULL){
        fprintf(stderr,"compare_STRING il primo parametro è NULL");
        exit(EXIT_FAILURE);
    }
    if(b==NULL){
        fprintf(stderr,"compare_STRING il secondo paremetro è NULL");
        exit(EXIT_FAILURE);
    }

    const Record *recordA = (const Record*)a;
    const Record *recordB = (const Record*)b;

    return strcmp(recordA->field1, recordB->field1);
}

void sort_records(FILE *infile, FILE  *outfile, size_t k, size_t field){

    size_t capacity;
    Record* r= readRecords(infile,&capacity);
    if (r == NULL) {
        printf("Errore nella lettura dei record.\n");
        return ;
    }

    if (field == 2) {
        merge_binary_insertion_sort(r, capacity, sizeof(Record), k, (libsort_comparator)compare_INT);
    } else if (field == 3) {
        merge_binary_insertion_sort(r, capacity, sizeof(Record), k, (libsort_comparator)compare_FLOAT);
    } else if (field == 1) {
        merge_binary_insertion_sort(r, capacity, sizeof(Record), k, (libsort_comparator)compare_STRING);
    } else {
        printf("Invalid field parameter.\n");
        free(r);
        return ;
    }

    write_record_to_file(outfile,r,capacity);

    for(size_t i=0;i<capacity;i++){
        free(r[i].field1);
    }
    free(r);

}