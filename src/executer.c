#include <stdio.h>
#include <glib.h>

#include "../include/date.h"
#include "../include/users.h"
#include "../include/flights.h"
#include "../include/reservations.h"
#include "../include/passengers.h"
#include "../include/parser.h"
#include "../include/users_catalog.h"
#include "../include/flights_catalog.h"
#include "../include/reservations_catalog.h"
#include "../include/passengers_catalog.h"
#include "../include/statistics.h"
#include "../include/queries.h"
#include "../include/executer.h"

char ** parse_input_line(char * line, int * complete_date_index1, int * complete_date_index2) {
    char ** tokens = malloc(sizeof(char *) * 5);
    int i, in_quote, length, found_first;
    i = in_quote = length = found_first = 0;
    char * token, * temp;
    token = temp = NULL;

    while ((token = strsep(&line, " "))) {
        length = strlen(token);
        if (token[0] == '"') {
            temp = strdup(token + 1);
            in_quote = 1;
        } else if (length > 0 && token[length - 1] == '"' && in_quote) {
            char * complete_date = malloc(strlen(temp) + 1 + strlen(token));
            token[length - 1] = '\0';
            strcpy(complete_date, temp);
            strcat(complete_date, " ");
            strcat(complete_date, token);
            if (found_first == 0) {
                (* complete_date_index1) = i;
                found_first = 1;
            } else {
                (* complete_date_index2) = i;
            }
            tokens[i++] = complete_date;
            free(temp);
            in_quote = 0;
        } else {
            tokens[i++] = token;
        }
    }
    tokens[i] = NULL;
    return tokens;
}

void execute(char * argv, Users_catalog * users_catalog, Flights_catalog * flights_catalog, Reservations_catalog * reservations_catalog, Passengers_catalog * passengers_catalog, CatalogoStats * stats) {
    FILE * input = fopen(argv, "r");
    if (!input) {
        perror("Erro ao abrir o ficheiro");
        return;
    }
    char * line = NULL;
    ssize_t read;
    size_t len;
    int ncomand = 1;
    while ((read = getline(&line, &len, input)) != -1) {
        int complete_date_index1 = -1, complete_date_index2 = -1;
        char * line_copy = strdup(line);
        char * formated_line = strsep(&line_copy, "\n");
        char ** tokens = parse_input_line(formated_line, &complete_date_index1, &complete_date_index2);        
        query(users_catalog, flights_catalog, passengers_catalog, reservations_catalog, stats, tokens, ncomand++);
        free(formated_line);
        if (complete_date_index1 >= 0) {
            free(tokens[complete_date_index1]);
        }
        if (complete_date_index2 >= 0) {
            free(tokens[complete_date_index2]);
        }
        free(tokens);
    }
    free(line);
    fclose(input);
}
