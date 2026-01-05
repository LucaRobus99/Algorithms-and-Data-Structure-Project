
#include <stdlib.h>

#include <string.h>
#include <time.h>
#include <ctype.h>
#include "utils.h"
#include "skiplist.h"

//Questa funzione è utilizzata come funzione di confronto per gli elementi nella SkipList
static int compare_function(const void *a, const void *b) {
    const char *str_a = *(const char **)a;
    const char *str_b = *(const char **)b;

    return strcmp(str_a, str_b);
}



/*
 * Questa funzione legge gli elementi da un file specificato e li memorizza in un array di stringhe.
 * Conta anche il numero di righe nel file per determinare la dimensione dell'array.
 * Restituisce l'array degli elementi letti o NULL in caso di errore.
 * */
static  char** read_items_from_file(FILE * file, int* num_items) {

    if (file == NULL) {
        fprintf(stderr, "Impossibile aprire il file");
        return NULL;
    }

    // Conta il numero di righe nel file
    int lines = 0;
    int ch; // Modifica il tipo di dati da char a int
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }
    fseek(file, 0, SEEK_SET);

    // Alloca l'array per gli elementi
    char** items = malloc((size_t)lines * sizeof(char*));
    if (items == NULL) {
        fprintf(stderr, "Errore di allocazione per l'array degli elementi.\n");
        fclose(file);
        return NULL;
    }

    // Leggi gli elementi dal file riga per riga
    char buffer[256];
    int i = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Rimuovi il carattere newline finale
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        // Alloca la memoria per l'elemento e copialo nell'array
        items[i] = strdup(buffer);
        if (items[i] == NULL) {
            fprintf(stderr, "Errore di allocazione per l'elemento %d.\n", i);
            fclose(file);
            for (int j = 0; j < i; j++) {
                free(items[j]);
            }
            free(items);
            return NULL;
        }

        i++;
    }
    fclose(file);
    *num_items = i;
    return items;
}




/*
 *Questa funzione rimuove i caratteri speciali da una parola specificata.
 * Crea una nuova stringa pulita senza caratteri speciali e la restituisce.
 * La funzione alloca memoria per la nuova stringa pulita.
 *
 * */

static char* remove_special_chars(const char* word) {
    size_t max_length = 256;
    char* clean_word = malloc(max_length * sizeof(char));

    if (clean_word == NULL) {
        fprintf(stderr, "Errore di allocazione per la parola senza caratteri speciali.\n");
        return NULL;
    }

    size_t clean_index = 0;
    int skip = 0;

    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] == '\'') {
            skip = 1;
            continue;
        }

        if (skip) {
            skip = 0;
            clean_index = 0; // Resettiamo l'indice per la nuova parola
        }

        if (!ispunct(word[i])) {
            clean_word[clean_index] = word[i];
            clean_index++;

            if (clean_index >= max_length - 1) {
                break;
            }
        }
    }

    clean_word[clean_index] = '\0';

    return clean_word;
}

/*
 *  Questa funzione legge le parole da un file di testo specificato e le memorizza in un array di stringhe.
 *  Conta anche il numero di parole nel testo per determinare la dimensione dell'array.
 *  La funzione rimuove i caratteri speciali da ogni parola utilizzando la funzione remove_special_chars.
 *  Restituisce l'array delle parole lette o NULL in caso di errore.
 * */
static char** load_word_list(FILE* file, size_t* num_words) {

    if (file == NULL) {
        fprintf(stderr, "Impossibile aprire il file ");
        return NULL;
    }

    // Conta il numero di parole nel testo
    size_t words = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch)) {
            words++;
        }
    }
    fseek(file, 0, SEEK_SET);

    // Alloca l'array per le parole
    char** word_list = malloc((size_t)words * sizeof(char*));
    if (word_list == NULL) {
        fprintf(stderr, "Errore di allocazione per l'array delle parole.\n");
        fclose(file);
        return NULL;
    }

    // Leggi le parole dal testo
    char buffer[256];
    int i = 0;
    while (fscanf(file, "%255s", buffer) == 1) {
        // Rimuovi i caratteri speciali dalla parola
        char* clean_word = remove_special_chars(buffer);
        if (clean_word == NULL) {
            fprintf(stderr, "Errore di rimozione caratteri speciali per la parola %d.\n", i);
            fclose(file);
            for (int j = 0; j < i; j++) {
                free(word_list[j]);
            }
            free(word_list);
            return NULL;
        }

        // Alloca la memoria per la parola pulita e copiala nell'array
        word_list[i] = clean_word;

        i++;
    }

    fclose(file);

    *num_words = words;
    return word_list;
}
/*
 * Questa funzione verifica se le parole nell'array word_list (cioè nel testo) non sono presenti nel dizionario o
 * se una loro variante con la prima lettera maiuscola o minuscola non è presente nella SkipList.
 * Stampa le parole che non sono presenti nella SkipList.
 * */

static void print_incorrect_words(struct SkipList* dictionary, char** word_list, size_t word_list_length){

    unsigned int i;

    for ( i = 0 ; i < word_list_length ; i++ ){
        char* new_word = strdup(word_list[i]);


        if (isupper(word_list[i][0])) {
            new_word[0] =(char ) tolower(new_word[0]);

        } else {
            new_word[0] = (char)toupper(new_word[0]);

        }
        const void *result_1 = search_skiplist(dictionary, &word_list[i]);
        const void *result_2 = search_skiplist(dictionary, &new_word);
        if(result_1==NULL && result_2==NULL){
            printf("%s\n",word_list[i]);
        }
        free(new_word);
    }
}
/*
 * Questa funzione che sarà presentata allo sviluppatore  per la correzione degli errori nel testo.
 * Crea una nuova SkipList, legge gli elementi dal file di dizionario e li inserisce nella SkipList.
 * Successivamente, carica le parole dal file di testo,
 * cerca le parole errate nella SkipList utilizzando print_incorrect_words e infine pulisce la SkipList.
 * */
void find_errors(FILE *dictfile, FILE *textfile, size_t max_height){
    srand((unsigned int)time(NULL));
    struct SkipList* list;
    if(max_height<=0){// non puo' essere minore o uguale di 0 in quanto una skiplist non puo' avere 0 livelli
        printf("Max height non puo' essere minore o uguale di 0 ");
        return;
    }
    new_skiplist(&list, max_height, compare_function);


    int num_items;
    char** items = read_items_from_file(dictfile, &num_items);
    if (items == NULL) {
        printf("Errore durante la lettura degli elementi dal file.\n");
        return;
    }

    for (int i = 0; i < num_items; i++) {
        insert_skiplist(list, &items[i]);
    }

    
    size_t num_items_o;
    char** items_o = load_word_list(textfile, &num_items_o);
    if (items_o == NULL) {
        printf("Errore durante la lettura degli elementi dal file.\n");
        return;
    }



    print_incorrect_words(list,items_o,num_items_o);

    clear_skiplist(&list);

}