#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "hash_c_ver.h"

//I make no claims about this code being memory safe and frankly I am too afraid to ask

#define MAX_LINE_LENGTH 1000

void build_codex(uint64_t *codex, char **string_conts, char *name, int *num_strings) {
    //open file from input name
    FILE *script = fopen(name, "r");
    if (script == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    //collect all lines from file and place in vector codex
    char temp_line[MAX_LINE_LENGTH];
    uint64_t temp_hash;
    unsigned int i = 0;
    while (fgets(temp_line, MAX_LINE_LENGTH, script) != NULL) {
        temp_line[strlen(temp_line)-1] = '\0';
        temp_hash = GENHASH(temp_line); 
        if (temp_hash==SETHASH("print")) {//print condition
                codex[i] = temp_hash;//pass print converted to int into hash
                i++;
                fgets(temp_line, MAX_LINE_LENGTH, script);//read next line
                string_conts[*num_strings] = strdup(temp_line);//store string in separate vector
                codex[i] = *num_strings;//pass string's location into codex
                *num_strings++;
        } else {
                codex[i] = temp_hash;
        }
    }
    fclose(script);
}

void read_codex(uint64_t *codex, char **string_conts, int num_strings) {
    //read instructions inside codex and interpret results
    for (unsigned int i = 0; i < 2; i++) {
        if (codex[i]==SETHASH("print")) {
            //if print found increment line by one and print next line
            i++;
            printf("%s\n", string_conts[codex[i]]);
        } else {
            printf("Syntax Error on line: %ld:%ld:%d\n", SETHASH("print"),codex[i],i+1);
        }
    }
}

int main(int argc, char **argv) {
    //vectors to hold instruction
    uint64_t *codex = (uint64_t*) malloc(MAX_LINE_LENGTH * sizeof(uint64_t));
    char **string_conts = (char **) malloc(MAX_LINE_LENGTH * sizeof(char *));
    int num_strings = 0;

    //make sure there is a script listed in the command line argument
    if (argc > 1) {
        //import script
        build_codex(codex, string_conts, argv[1], &num_strings);
        //interpret instructions
        read_codex(codex, string_conts, num_strings);
    }
    free(codex);
    for (int i = 0; i < num_strings; i++) {
        free(string_conts[i]);
    }
    free(string_conts);
    return 0;
}