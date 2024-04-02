#include <stdio.h>
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
#include "../include/executer.h"
#include "../include/menus.h"

char * users_path(char * argv) {
    char * path = malloc(strlen(argv) + strlen("/users.csv") + 1);
    strcpy(path, argv);
    strcat(path, "/users.csv");
    return path;
}

char * flights_path(char * argv) {
    char * path = malloc(strlen(argv) + strlen("/flights.csv") + 1);
    strcpy(path, argv);
    strcat(path, "/flights.csv");
    return path;
}

char * reservations_path(char * argv) {
    char * path = malloc(strlen(argv) + strlen("/reservations.csv") + 1);
    strcpy(path, argv);
    strcat(path, "/reservations.csv");
    return path;
}

char * passengers_path(char * argv) {
    char * path = malloc(strlen(argv) + strlen("/passengers.csv") + 1);
    strcpy(path, argv);
    strcat(path, "/passengers.csv");
    return path;
}

int main(int argc, char ** argv) {    
    if (argc >= 2) {
        char * users_csv = users_path(argv[1]);
        char * flights_csv = flights_path(argv[1]);
        char * reservations_csv = reservations_path(argv[1]);
        char * passengers_csv = passengers_path(argv[1]);

        Users_catalog * users_catalog = usersToCatalog(users_csv);
        Flights_catalog * flights_catalog = flightsToCatalog(flights_csv);
        Reservations_catalog * reservations_catalog = reservationsToCatalog(reservations_csv, users_catalog);
        Passengers_catalog * passengers_catalog = passengersToCatalog(passengers_csv, users_catalog, flights_catalog);

        CatalogoStats * stats = loadstats(users_catalog, flights_catalog, passengers_catalog, reservations_catalog);

        if (argc == 3) {
            execute(argv[2], users_catalog, flights_catalog, reservations_catalog, passengers_catalog, stats);
        } else {
            system("clear");
            menuUI();
            start_menu(users_catalog, flights_catalog, reservations_catalog, passengers_catalog, stats);
        }

        free(users_csv);
        free(flights_csv);
        free(reservations_csv);
        free(passengers_csv);

        free_users_catalog(users_catalog);
        free_flights_catalog(flights_catalog);
        free_reservations_catalog(reservations_catalog);
        free_passengers_catalog(passengers_catalog);

        free_catalogo_stats(stats);

        return 0;
    } else {
        printf("Error, invalid number or arguments.\n");
        return 1;
    }
}
