#include <glib.h>

#include "../include/date.h"
#include "../include/flights.h"
#include "../include/parser.h"
#include "../include/flights_catalog.h"

typedef struct flights_catalog {
    GHashTable * flights;
} Flights_catalog;

Flight * getFlight(Flights_catalog * catalogo, int id) {
    Flight * voo = g_hash_table_lookup(catalogo -> flights, GINT_TO_POINTER (id));
    if(!voo) return NULL;
    return clone_flight(voo);
}

void buildFlight(char ** tokens, Flights_catalog * catalogo) {
    Flight * voo = completa_flight(tokens);
    if (!voo) return;
    int flight_id = get_flight_id(voo);
    g_hash_table_insert(catalogo -> flights, GINT_TO_POINTER (flight_id), voo);
}

void buildFlight_wrapper(char ** tokens, void * structure1, void * structure2, void * structure3) {
    return buildFlight(tokens, (Flights_catalog *) structure1);
}

Flights_catalog * flightsToCatalog(char * path) {
    Flights_catalog * catalogo = malloc(sizeof(Flights_catalog));
    catalogo -> flights = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, free_flight_void);
    parser(path, buildFlight_wrapper, catalogo, NULL, NULL);
    return catalogo;
}

void free_flights_catalog(Flights_catalog * catalogo) {
    g_hash_table_destroy(catalogo -> flights);
    free(catalogo);
}
