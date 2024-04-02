#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parser.h"

char ** parseLine(char * line) {
    char ** tokens = malloc(sizeof(char *) * 16);
    int i = 0;
    char * token = NULL;
    while ((token = strsep(&line, ";"))) {
        tokens[i++] = token;
    }
    tokens[i] = NULL;
    return tokens;
}

void parser(char * path, void (* buildStruct)(char **, void *, void *, void *), void * structure1, void * structure2, void * structure3) {
    FILE * file = fopen(path, "r");
    if (!file) {
        perror("Erro ao abrir o ficheiro");
        return;
    }
    char * line = NULL;
    ssize_t read;
    size_t len;
    while ((read = getline(&line, &len, file)) != -1) {
        char * line_copy = strdup(line);
        char * formated_line = strsep(&line_copy, "\n");
        char ** tokens = parseLine(formated_line);
        buildStruct(tokens, structure1, structure2, structure3);
        free(formated_line);
        free(tokens);
    }
    free(line);
    fclose(file);
}
