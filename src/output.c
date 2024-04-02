#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/output.h"

void defaultOutput(char * details, int ncommand) {
    char filename[100];
    snprintf(filename, sizeof(filename), "Resultados/command%d_output.txt", ncommand);

    FILE * file = fopen(filename, "a");
    if (!file) {
        printf("Erro ao abrir o arquivo %s.\n", filename);
        return;
    }

    if (details) {
        fprintf(file, "%s\n", details);
    }

    fclose(file);
}

void flagOutput(char * details, int ncommand, char ** qstruc, int i) {
    char filename[100];
    snprintf(filename, sizeof(filename), "Resultados/command%d_output.txt", ncommand);

    FILE *file = fopen(filename, "a");
    if (!file) {
        printf("Erro ao abrir o arquivo %s.\n", filename);
        return;
    }

    if (details) {
        fprintf(file, "--- %d ---\n", i);

        int count = 0;
        char * temp = strdup(details);
        char * temp_pointer = temp;
        char * token = strtok(temp, ";");

        while (token != NULL && qstruc[count] != NULL) {
            fprintf(file, "%s: %s\n", qstruc[count], token);
            token = strtok(NULL, ";");
            count++;
        }
    
        free(temp_pointer);
    }

    fclose(file);
}

