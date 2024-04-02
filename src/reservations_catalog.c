#include <glib.h>
#include <stdio.h>

#include "../include/date.h"
#include "../include/reservations.h"
#include "../include/parser.h"
#include "../include/reservations_catalog.h"

typedef struct reservations_catalog {
    GPtrArray * reservations;
} Reservations_catalog;

Reservation * getReservation(Reservations_catalog * catalogo, int index) {
    Reservation * reserva = catalogo -> reservations -> pdata[index];
    return clone_reservation(reserva);
}

int getReservationsLenght(Reservations_catalog * catalogo) {
    return catalogo -> reservations -> len;
}

void buildReservation(char ** tokens, Reservations_catalog * catalogo, void * structure) {
    Reservation * reserva = completa_reservation(tokens, structure);
    if (!reserva) return;
    g_ptr_array_add(catalogo -> reservations, reserva);
}

void buildReservation_wrapper(char ** tokens, void * structure1, void * structure2, void * structure3) {
    return buildReservation(tokens, (Reservations_catalog *) structure1, structure2);
}

Reservations_catalog * reservationsToCatalog(char * path, void * structure) {
    Reservations_catalog * catalogo = malloc(sizeof(Reservations_catalog));
    catalogo -> reservations = g_ptr_array_new_with_free_func(free_reservation_void);
    parser(path, buildReservation_wrapper, catalogo, structure, NULL);
    return catalogo;
}

void free_reservations_catalog(Reservations_catalog * catalogo) {
    g_ptr_array_free(catalogo->reservations, TRUE);
    free(catalogo);
}