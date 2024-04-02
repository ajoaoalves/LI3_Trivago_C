#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <glib.h>

#include "../include/date.h"
#include "../include/users.h"
#include "../include/users_catalog.h"
#include "../include/flights.h"
#include "../include/flights_catalog.h"
#include "../include/passengers.h"

typedef struct passengers {
    int flight_id;
    char * user_id;
} Passenger; 

int get_passenger_flight_id (Passenger * passenger) {
    return (passenger -> flight_id);
}

char * get_passenger_user_id (Passenger * passenger) {
    return strdup(passenger -> user_id);
}

Passenger * create_passenger() { 
    return malloc(sizeof(Passenger));
}

int valida_tokens_passengers(char ** tokens, Users_catalog * users_catalog, Flights_catalog * flights_catalog) {
    Flight * voo = getFlight(flights_catalog, atoi(tokens[0]));
    if (strlen(tokens[0]) == 0 || atoi(tokens[0]) == 0 || voo == NULL) {
        free_flight(voo);
        return 1;
    }
    free_flight(voo);
    User * utilizador = getUser(users_catalog, tokens[1]);
    if (strlen(tokens[1]) == 0 || utilizador == NULL) {
        free_user(utilizador);
        return 1;
    }
    free_user(utilizador);
    return 0;
}

Passenger * completa_passenger(char ** tokens, void * structure1, void * structure2) {
    Users_catalog * users_catalog = (Users_catalog *) structure1;
    Flights_catalog * flights_catalog = (Flights_catalog *) structure2;
    if (valida_tokens_passengers(tokens, users_catalog, flights_catalog)) {
        FILE * file = fopen("Resultados/passengers_errors.csv", "a");
        int i = 0;
        if (file != NULL) {
            while(tokens[i + 1] != NULL) fprintf(file, "%s;", tokens[i++]);
            fprintf(file, "%s\n", tokens[i]);
            fclose(file);
            return NULL;
        }
    }
    Passenger * passageiro = create_passenger();
    if(!passageiro) return NULL;
    passageiro -> flight_id = atoi(tokens[0]);
    passageiro -> user_id = strdup(tokens[1]);
    return passageiro;
}

Passenger * clone_passenger(Passenger * passenger) {
    Passenger * passageiro = create_passenger();
    if (!passageiro) return NULL;
    passageiro->flight_id = get_passenger_flight_id(passenger);
    passageiro->user_id = get_passenger_user_id(passenger);
    return passageiro;
}

void free_passenger(Passenger * passenger) {
    if (passenger) {
        free(passenger -> user_id);
        free(passenger);
    }
}

void free_passenger_void(gpointer passenger) {
    free_passenger(passenger);
}
