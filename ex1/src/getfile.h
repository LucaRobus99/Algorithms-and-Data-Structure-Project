#ifndef GETFILE_H
//Strutture dei records
typedef struct {
    int ID;
    char* field1;
    int field2;
    float field3;
} Record;
//Prende in input due punatorio:uno per il file di input e uno per il count dei record che viene utilizzato
// per sapere il numero delle righe del file.
//Sei il file viene aperto corettamente, restituisce i Record letti da file
//altrimenti restituisce NULL.
//I parametri di input non possono essere NULL.
Record* readRecords(FILE * file_name,size_t* record_count);


//Prende in input due punatorio ,uno per il file di output e uno per la lista dei records,e un size_t.
//Sei il file viene aperto corettamente, scrive su file la lista dei record.
//I parametri di input non possono essere NULL.
void write_record_to_file(FILE * file, const Record* records,size_t record_count);
#endif //GETFILE_H
