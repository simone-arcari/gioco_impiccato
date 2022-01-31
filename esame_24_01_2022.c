/*
===============================================================================
 Name        : esame_24_01_2022.c
 Author      : Simone Arcari
 Version     : 1.0
 Copyright   : none
 Description : main definition
===============================================================================
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define RESET   "\033[0m"
#define MAGENTA "\033[35m"              /* Magenta */
#define CYAN    "\033[36m"              /* Cyan */
#define BOLDRED "\033[1m\033[31m"       /* Bold Red */

#define BUF_LEN 1024

#define ERR_ARG "[ERROR] wrong number of arguments\n"
#define ERR_FOPEN "[ERROR] unable to open the file\n"
#define ERR_MALLOC "[ERROR] unable to allocate other memory\n"

typedef struct match {
        struct match *next;
        char *word;
        char *unknown_letters;
        unsigned int life_points;
} match_t;

enum err_type {
        err_fopen,
        err_malloc
};

unsigned int life_points;

bool check_ptr(void *ptr, enum err_type err_case) {

        if(ptr == NULL) {
                switch (err_case) {

                        case err_fopen:
                                fprintf(stderr, ERR_FOPEN);
                        break;

                        case err_malloc:
                                fprintf(stderr, ERR_MALLOC);
                        break;
                
                        default:
                                fprintf(stderr, "some error\n");
                        break;
                }

                return false;
        }
        return true;
}

char *take_word(char *buffer) {

        char *word;
        char *token = strtok(buffer, ";");
        size_t len = strlen(token);

        word = malloc( sizeof(char)*(len+1) );
        if(check_ptr(word, err_malloc) == false) {
                exit(EXIT_FAILURE);
        }

        memmove(word, token, len+1);
        word[len] = '\0';

        return word;
}

char *take_lowercase(char *str) {

        size_t len = strlen(str);
        char buffer[len];
        char *lower_letters;
        size_t i=0;
        size_t j=0;

        for(; i<len; i++) {
                if(islower(str[i])) {
                        buffer[j] = str[i];
                        j++;
                }    
        }
        
        lower_letters = malloc( sizeof(char)*(j+1) );
        if(check_ptr(lower_letters, err_malloc) == false) {
                exit(EXIT_FAILURE);
        }

        memmove(lower_letters, buffer, j);
        lower_letters[j] = '\0';

        return lower_letters;
}

void print_list(match_t **head) {

        int i = 1;        
        while(*head != NULL) {
                printf("TURNO %d:\n", i);
                printf("\tnext: %p\n", (*head)->next);
                printf("\tword: %s\n", (*head)->word);
                printf("\tunknown_letters: %s\n", (*head)->unknown_letters);
                printf("\tlife_points: %d\n", (*head)->life_points);

                head = &(*head)->next;
                i++;
        }
}

void match_load(FILE *file, match_t **head) {

        char buffer[1024];
        match_t *new_turn;

        while( fgets(buffer, BUF_LEN, file) != NULL ) {

                new_turn = malloc(sizeof(match_t));
                if(check_ptr(new_turn, err_malloc) == false) {
                        exit(EXIT_FAILURE);
                }

                new_turn->next = NULL;
                new_turn->word = take_word(buffer);
                new_turn->unknown_letters = take_lowercase(new_turn->word);
                new_turn->life_points = atoi( strtok(NULL, ";") );

                /* inserisco sempre in coda */
                *head = new_turn;
                head = &(*head)->next;
        }
}

void show_word(char *str) {

        printf("\nparola da indovinare: %s", MAGENTA);

        while(*str) {
                if(isupper(*str)) {
                        printf("%c", *str);
                } else {
                        printf("_");
                }
                str++;
        }
        printf("%s\n", RESET);
}

char insert_letter(char *msg) {

        char buffer[1024];

        printf("%s", msg);
        if(fgets(buffer, 1024, stdin)) {
                buffer[strcspn(buffer,"\n")] = '\0';
        }
        return buffer[0];
}

bool is_unknown_letters(match_t *cur, char letter) {

        letter = tolower(letter);
        char *ptr = cur->unknown_letters;        
        
        while(*ptr) {
                if(*ptr == letter) {
                     *ptr = toupper(*ptr);
                     return true;   
                }
                ptr++;
        }
        
        return false;
}

bool word_find(char *word) {
/* la la parola è tutta magliuscola allora è trovata */
        while(*word) {
                if(islower(*word))
                        return false;
                word++;
        }
        return true;
}

void start_game(match_t **head) {

        bool game_end = false;
        char letter;
        char msg[30];
        unsigned int base_HP;    // sono gli health point base di ogni turno
        unsigned int healt_points;
        
        base_HP = healt_points = (*head)->life_points;

        do {
                show_word( (*head)->word );
                printf("punti vita rimanenti: %s%d%s\n",CYAN, healt_points, RESET);
                
                snprintf(msg, 30, "inserci una lettera: %s", CYAN);
                letter = insert_letter(msg);
                printf("%s", RESET);
                
                if(is_unknown_letters(*head, letter) == false) {
                        /* la letera non è stata indovinata */
                        healt_points--;

                } else {
                        /* la lettera è stata indovinata */
                        char *ptr = (*head)->word;
                        while(*ptr != tolower(letter)) {
                                ptr++;                      
                        }
                        *ptr = toupper(letter);   // la lettera trovata diventa maiuscola
                }

                if( healt_points == 0) {
                        game_end = true;
                        printf("\n\n\n\t%sHAI PERSO!!!%s\n", BOLDRED, RESET); 
                }

                if( word_find((*head)->word) ) {
                        printf("\n\t---> parola trovata: %s%s%s\n", BOLDRED, (*head)->word, RESET);
                        
                        head = &(*head)->next;
                        
                        if(*head != NULL) {
                                healt_points = (*head)->life_points + healt_points + base_HP;
                                base_HP = (*head)->life_points;
                        } else {
                                game_end = true;        // la lista dei turni è finita
                                printf("\n\n\n\t%sHAI VINTO!!!%s\n", BOLDRED, RESET); 
                        }
                }

        } while(game_end == false);
}

int main(int argc, char **argv) {

        bool debug = false;

        if(argc != 2) {                         // solo due parametri!
                fprintf(stderr, ERR_ARG);
                exit(EXIT_FAILURE);
        }

        const char *filename = argv[1];         // datapath del file passato come parametro

        FILE *fp = fopen(filename, "r");        // apro il file con i parametri dei turni
        if(check_ptr(fp, err_fopen) == false) {
                exit(EXIT_FAILURE);
        }

        printf("\n\n\n\t%sGIOCO DELL'IMPICCATO%s\n", BOLDRED, RESET);   // titolo

        match_t *cur_match = NULL;              // puntatore sentinella della lista dei turni
        
        match_load(fp, &cur_match);             // carica la lista dei turni
        
        if(debug) {
                print_list(&cur_match);         // stampa la lista dei turni a scopo di debug
        }
   
        start_game(&cur_match);                 // è un loop che finisce se il giocatore perde o se finiscono tutti i turni


        fclose(fp);
 
        return EXIT_SUCCESS;
}
