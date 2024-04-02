#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>

#include "../include/date.h"
#include "../include/users.h"
#include "../include/users_catalog.h"
#include "../include/reservations.h"

typedef struct reservations {
    char * id;
    char * user_id;
    char * hotel_id;
    char * hotel_name;
    int hotel_stars;
    int city_tax; 
    Date * begin_date;
    Date * end_date;
    int price_per_night;
    int includes_breakfast; 
    int rating;
} Reservation;

char * get_reservation_id(Reservation * reservation) {
    return strdup(reservation -> id);
}

char * get_reservation_user_id(Reservation * reservation) {
    return strdup(reservation -> user_id);
}

char * get_reservation_hotel_id(Reservation * reservation) {
    return strdup(reservation -> hotel_id);
}

char * get_reservation_hotel_name(Reservation * reservation) {
    return strdup(reservation -> hotel_name);
}

int get_reservation_hotel_stars(Reservation * reservation) {
    return (reservation -> hotel_stars);
}

int get_reservation_city_tax(Reservation * reservation) {
    return (reservation -> city_tax);
}

Date * get_reservation_begin_date(Reservation * reservation) {
    return clone_date(reservation -> begin_date);
}

Date * get_reservation_end_date(Reservation * reservation) {
    return clone_date(reservation -> end_date);
}

int get_reservation_price_per_night(Reservation * reservation) {
    return (reservation -> price_per_night);
}

int get_reservation_includes_breakfast(Reservation * reservation) {
    return (reservation -> includes_breakfast);
}

int get_reservation_rating(Reservation * reservation) {
    return (reservation -> rating);
}

Reservation * create_reservation() {
    return malloc(sizeof(Reservation));
}

int valida_includes_breakfast(char * str) {
    if (strcmp(str, "t") == 0 || strcmp(str, "T") == 0 || strcmp(str, "true") == 0 || strcmp(str, "TRUE") == 0 || strcmp(str, "1") == 0) return 1;
    if (strcmp(str, "f") == 0 || strcmp(str, "F") == 0 || strcmp(str, "false") == 0 || strcmp(str, "FALSE") == 0 || strcmp(str, "0") == 0 || strcmp(str, "") == 0) return 0;
    return 2;
}

int isInteger(const char * str) {
    char * endptr;
    strtol(str, &endptr, 10);
    if (* endptr != '\0' && *endptr != '\n') return 1;
    return 0; 
}

int valida_tokens_reservations(char ** tokens, Users_catalog * users_catalog) {
    if (strlen(tokens[0]) == 0) return 1;
    User * utilizador = getUser(users_catalog, tokens[1]);
    if (strlen(tokens[1]) == 0 || utilizador == NULL) {
        free_user(utilizador);
        return 1;
    }
    free_user(utilizador);
    if (strlen(tokens[2]) == 0) return 1;
    if (strlen(tokens[3]) == 0) return 1;
    if (atoi(tokens[4]) < 1 || atoi(tokens[4]) > 5 || isInteger(tokens[4])) return 1;
    if (atoi(tokens[5]) <= 0 || isInteger(tokens[5])) return 1;
    if (strlen(tokens[6]) == 0) return 1;
    if (validate_date(tokens[7])) return 1;
    if (validate_date(tokens[8])) return 1;
    if (atoi(tokens[9]) <= 0 || isInteger(tokens[9])) return 1;
    if (valida_includes_breakfast(tokens[10]) == 2) return 1;
    if (strlen(tokens[12]) != 0 && (atoi(tokens[12]) < 1 || atoi(tokens[12]) > 5 || isInteger(tokens[12]))) return 1;
    Date * data_1 = string_to_date(tokens[7]);
    Date * data_2 = string_to_date(tokens[8]);
    if (compare_date(data_1, data_2) == -1) {
        free_date(data_1);
        free_date(data_2);
        return 1;
    }
    free_date(data_1);
    free_date(data_2);
    return 0;
}

Reservation * completa_reservation(char ** tokens, void * structure) {
    Users_catalog * users_catalog = (Users_catalog *) structure;
    if (valida_tokens_reservations(tokens, users_catalog)) {
        FILE * file = fopen("Resultados/reservations_errors.csv", "a");
        int i = 0;
        if (file != NULL) {
            while(tokens[i + 1] != NULL) fprintf(file, "%s;", tokens[i++]);
            fprintf(file, "%s\n", tokens[i]);
            fclose(file);
            return NULL;
        }
    }
    Reservation * reserva = create_reservation();
    if(!reserva) return NULL;
    reserva -> id = strdup(tokens[0]);
    reserva -> user_id = strdup(tokens[1]);
    reserva -> hotel_id = strdup(tokens[2]);
    reserva -> hotel_name = strdup(tokens[3]);
    reserva -> hotel_stars = atoi(tokens[4]);
    reserva -> city_tax = atoi(tokens[5]);
    reserva -> begin_date =  string_to_date(tokens[7]); 
    reserva -> end_date  = string_to_date(tokens[8]);
    reserva -> price_per_night = atoi(tokens[9]);
    reserva -> includes_breakfast = valida_includes_breakfast(tokens[10]);
    reserva -> rating = atoi(tokens[12]);
    return reserva;
}

Reservation * clone_reservation(Reservation * reservation) {
    Reservation * reserva = create_reservation();
    reserva -> id = get_reservation_id(reservation);
    reserva -> user_id = get_reservation_user_id(reservation);
    reserva -> hotel_id = get_reservation_hotel_id(reservation);
    reserva -> hotel_name = get_reservation_hotel_name(reservation);
    reserva -> hotel_stars = get_reservation_hotel_stars(reservation);
    reserva -> city_tax = get_reservation_city_tax(reservation);
    reserva -> begin_date = get_reservation_begin_date(reservation);
    reserva -> end_date = get_reservation_end_date(reservation);
    reserva -> price_per_night = get_reservation_price_per_night(reservation);
    reserva -> includes_breakfast = get_reservation_includes_breakfast(reservation);
    reserva -> rating = get_reservation_rating(reservation);
    return reserva;
}

double precoReserva(Reservation * reserva) {
    double res = 0;
    Date * end_date = get_reservation_end_date(reserva);
    Date * begin_date = get_reservation_begin_date(reserva);
    double preco = get_reservation_price_per_night(reserva);
    double imposto = get_reservation_city_tax(reserva);
    double end_res = get_day(end_date);
    double begin_res = get_day(begin_date);
    double noites = end_res - begin_res;
    res = preco * noites + (preco * noites/ 100) * imposto;
    free_date(end_date);
    free_date(begin_date);
    return res;
}

void free_reservation(Reservation * reservation) {
    if (reservation) {
        free(reservation -> id);
        free(reservation -> user_id);
        free(reservation -> hotel_id);
        free(reservation -> hotel_name);
        free_date(reservation -> begin_date);
        free_date(reservation -> end_date);
        free(reservation);
    }
}

void free_reservation_void(gpointer reservation) {
    free_reservation(reservation);
}
