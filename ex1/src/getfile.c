#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getfile.h"



Record* readRecords(FILE* file, size_t* record_count) {

    if (file == NULL) {
        printf("Errore nell'apertura del file di input.\n");
        exit(EXIT_FAILURE);
    }

    Record* records = NULL;
    *record_count = 0;

    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char* token = strtok(buffer, ",");
        int id = atoi(token);

        token = strtok(NULL, ",");
        size_t field1_length = strlen(token);
        char* field1 = malloc(field1_length + 1);  // Alloca memoria per la stringa
        strcpy(field1, token);  // Copia la stringa

        token = strtok(NULL, ",");
        int field2 = atoi(token);

        token = strtok(NULL, ",");
        float field3= (float)atof(token);

        Record* new_record = malloc(sizeof(Record));
        if (new_record == NULL) {
            printf("Errore nell'allocazione di memoria.\n");
            fclose(file);
            free(records);
            exit(EXIT_FAILURE);
        }

        new_record->ID = id;
        new_record->field1 = field1;
        new_record->field2 = field2;
        new_record->field3 = field3;

        records = realloc(records, sizeof(Record) * (*record_count + 1));
        if (records == NULL) {
            printf("Errore nella riallocazione di memoria.\n");
            fclose(file);
            free(new_record->field1);  // Dealloca la memoria di field2
            free(records);
            exit(EXIT_FAILURE);
        }

        records[*record_count] = *new_record;
        (*record_count)++;

    }


    fclose(file);

    return records;
}




void write_record_to_file(FILE * file, const Record* records,size_t record_count) {

    if (file == NULL) {
        printf("Errore nell'apertura del file di output.\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < record_count; i++) {
        const Record* record = &records[i];
        fprintf(file, "%d,%s,%d,%.2f\n", record->ID, record->field1, record->field2, record->field3);
    }

    fclose(file);
}