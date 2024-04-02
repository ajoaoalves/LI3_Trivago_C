#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
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
#include "../include/menus.h"

void menuUI() {
    printf("                                 ._______________________.                                   \n");
    printf("                                 |.---------------------.|                                   \n");
    printf("                                 ||  Sistema de gestão  ||                                   \n");
    printf("                                 ||e consulta de viagens||                                   \n");
    printf("                                 ||                     ||                                   \n");
    printf("                                 ||      Grupo 34:      ||                                   \n");
    printf("                                 ||  - Ana João Alves   ||                                   \n");
    printf("                                 ||  - Gonçalo Brandão  ||                                   \n");
    printf("                                 ||  - Simão Antunes    ||                                   \n");
    printf("                                 ||_____________________||                                   \n");
    printf("                                 /.-.-.-.-.-.-.-.-.-.-.-.\\                                  \n");
    printf("                                /.-.-.-.-.-.-.-.-.-.-.-.-.\\                                 \n");
    printf("                               /.-.-.-.-.-.-.-.-.-.-.-.-.-.\\                                \n");
    printf("                              /______/__________\\__________\\                               \n");
    printf("                              \\_____________________________/                               \n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("                                          Welcome!                                           \n");
    printf("                               What queries do you want to run?                              \n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("1. Display User, Flight or Reservation Summary (1 <ID>)\n");
    printf("2. List User Flights, Reservations or Both (2 <ID> [flights|reservations])\n");
    printf("3. Display Average Hotel Rating (3 <ID>)\n");
    printf("4. List Reservations by Hotel (4 <ID>)\n");
    printf("5. List Flights by Origin Airport (5 <Name> <Begin_date> <End_date>)\n");
    printf("6. List Top Airports for a Year (6 <Year> <N>)\n");
    printf("7. List Top Airports by Median Delay (7 <N>)\n");
    printf("8. Display Total Revenue by Hotel (8 <Id> <Begin_date> <End_date>)\n");
    printf("9. List Users by Name Prefix (9 <Prefix>)\n");
    printf("10. Display General Metrics (10 [year [month]])\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("                                   Press E key to to exit!                                   \n");
    printf("---------------------------------------------------------------------------------------------\n");
}

void start_menu(Users_catalog * users_catalog, Flights_catalog * flights_catalog, Reservations_catalog * reservations_catalog, Passengers_catalog * passengers_catalog, CatalogoStats * stats) {
    bool exit_requested = false;

    while (!exit_requested) {
        char userInput[100];
        int complete_date_index1 = -1, complete_date_index2 = -1;

        printf("Enter your option: ");

        fgets(userInput, sizeof(userInput), stdin);

        size_t len = strlen(userInput);
        if (len > 0 && userInput[len - 1] == '\n') {
            userInput[len - 1] = '\0';
        }

        if (userInput[0] == 'E' || userInput[0] == 'e') {
            system("clear");
            exit_requested = true;
        } else {
            system("clear");
            menuUI();

            char **tokens = parse_input_line(userInput, &complete_date_index1, &complete_date_index2);
            query(users_catalog, flights_catalog, passengers_catalog, reservations_catalog, stats, tokens, 0);

            printf("---------------------------------------------------------------------------------------------\n");

            if (complete_date_index1 >= 0) {
                free(tokens[complete_date_index1]);
            }
            if (complete_date_index2 >= 0) {
                free(tokens[complete_date_index2]);
            }

            free(tokens);
        }
    }
}

