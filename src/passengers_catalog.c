#include <glib.h>
#include <stdio.h>

#include "../include/date.h"
#include "../include/passengers.h"
#include "../include/parser.h"
#include "../include/passengers_catalog.h"

typedef struct passengers_catalog {
    GPtrArray * passengers;
} Passengers_catalog;

Passenger * getPassenger(Passengers_catalog * catalogo, int index) {
    Passenger * passageiro = catalogo -> passengers -> pdata[index];
    return clone_passenger(passageiro);
}

int getPassengersLenght(Passengers_catalog * catalogo) {
    return catalogo -> passengers -> len;
}

void buildPassenger(char **tokens, Passengers_catalog *catalogo, void *structure1, void *structure2) {
    Passenger *passageiro = completa_passenger(tokens, structure1, structure2);
    if (!passageiro) return;
    g_ptr_array_add(catalogo -> passengers, passageiro);
}

void buildPassenger_wrapper(char **tokens, void *structure1, void *structure2, void *structure3) {
    return buildPassenger(tokens, (Passengers_catalog *)structure1, structure2, structure3);
}

Passengers_catalog * passengersToCatalog(char * path, void * structure1, void * structure2) {
    Passengers_catalog * catalogo = malloc(sizeof(Passengers_catalog));
    catalogo->passengers = g_ptr_array_new_with_free_func(free_passenger_void);
    parser(path, buildPassenger_wrapper, catalogo, structure1, structure2);
    return catalogo;
}

void free_passengers_catalog(Passengers_catalog * catalogo) {
    g_ptr_array_free(catalogo->passengers, TRUE);
    free(catalogo);
}
