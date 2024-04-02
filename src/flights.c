#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <glib.h>

#include "../include/date.h"
#include "../include/flights.h"

typedef struct flights {
    int id;
    char * airline;
    char * plane_model;
    int total_seats;
    char * origin;
    char * destination;
    Date * schedule_departure_date; 
    Date * schedule_arrival_date;
    Date * real_departure_date; 
    Date * real_arrival_date;
} Flight;

int get_flight_id(Flight *flight) {
    return (flight->id);
}

char * get_flight_airline(Flight* flight) {
    return strdup(flight -> airline);
}

char * get_flight_plane_model(Flight* flight) {
    return strdup(flight -> plane_model);
}

int get_flight_total_seats(Flight* flight) {
    return (flight -> total_seats);
}

char * get_flight_origin(Flight* flight) {
    return strdup(flight -> origin);
}

char * get_flight_destination(Flight* flight) {
    return strdup(flight -> destination);
}

Date * get_flight_schedule_departure_date(Flight * flight) {
    return clone_date(flight -> schedule_departure_date);
}

Date * get_flight_schedule_arrival_date(Flight* flight) {
    return clone_date(flight -> schedule_arrival_date);
}

Date * get_flight_real_departure_date(Flight* flight) {
    return clone_date(flight -> real_departure_date);
}

Date * get_flight_real_arrival_date(Flight* flight) {
    return clone_date(flight -> real_arrival_date);
}

Flight * create_flight() { 
    return malloc(sizeof(Flight));
}

void string_to_upper(char * str) {
    while (* str) {
        * str = toupper(* str);
        str++;
    }
}

int valida_tokens_flights(char ** tokens){
    if(strlen(tokens[0]) == 0) return 1;
    if(strlen(tokens[1]) == 0) return 1;
    if(strlen(tokens[2]) == 0) return 1;
    if(atoi(tokens[3]) <= 0) return 1;
    if(strlen(tokens[4]) != 3) return 1;
    if(strlen(tokens[5]) != 3) return 1;
    if(validate_date(tokens[6])) return 1;
    if(validate_date(tokens[7])) return 1;
    if(validate_date(tokens[8])) return 1;
    if(validate_date(tokens[9])) return 1;
    if(strlen(tokens[10]) == 0) return 1;
    if(strlen(tokens[11]) == 0) return 1;
    Date * data_1 = string_to_date(tokens[6]);
    Date * data_2 = string_to_date(tokens[7]);
    if (compare_date(data_1, data_2) == -1) {
        free_date(data_1);
        free_date(data_2);
        return 1;
    }
    free_date(data_1);
    free_date(data_2);
    Date * data_3 = string_to_date(tokens[8]);
    Date * data_4 = string_to_date(tokens[9]);
    if (compare_date(data_3, data_4) == -1) {
        free_date(data_3);
        free_date(data_4);
        return 1;
    }
    free_date(data_3);
    free_date(data_4);
    return 0;
}

Flight * completa_flight(char ** tokens) {
    if (valida_tokens_flights(tokens)) {
        FILE * file = fopen("Resultados/flights_errors.csv", "a");
        int i = 0;
        if (file != NULL) {
            while(tokens[i + 1] != NULL) fprintf(file, "%s;", tokens[i++]);
            fprintf(file, "%s\n", tokens[i]);
            fclose(file);
            return NULL;
        }
    }
    Flight * voo = create_flight();
    if(!voo) return NULL;
    voo -> id = atoi(tokens[0]);
    voo -> airline = strdup(tokens[1]);
    voo -> plane_model = strdup(tokens[2]);
    voo -> total_seats = atoi(tokens[3]);
    string_to_upper(tokens[4]);
    voo -> origin = strdup(tokens[4]);
    string_to_upper(tokens[5]);
    voo -> destination = strdup(tokens[5]);
    voo -> schedule_departure_date = string_to_date(tokens[6]);
    voo -> schedule_arrival_date = string_to_date(tokens[7]);
    voo -> real_departure_date = string_to_date(tokens[8]);
    voo -> real_arrival_date = string_to_date(tokens[9]);
    return voo;
}

Flight * clone_flight(Flight * flight) {
    Flight * voo = create_flight();
    voo -> id = get_flight_id(flight);
    voo -> airline = get_flight_airline(flight);
    voo -> plane_model = get_flight_plane_model(flight);
    voo -> total_seats = get_flight_total_seats(flight);
    voo -> origin = get_flight_origin(flight);
    voo -> destination = get_flight_destination(flight);
    voo -> schedule_departure_date = get_flight_schedule_departure_date(flight);
    voo -> schedule_arrival_date = get_flight_schedule_arrival_date(flight);
    voo -> real_departure_date = get_flight_real_departure_date(flight);
    voo -> real_arrival_date = get_flight_real_arrival_date(flight);
    return voo;
}

void free_flight(Flight * flight) {
    if (flight) { 
        free(flight -> airline);
        free(flight -> plane_model);
        free(flight -> origin);
        free(flight -> destination);
        free_date(flight -> schedule_departure_date);
        free_date(flight -> schedule_arrival_date);
        free_date(flight -> real_departure_date);
        free_date(flight -> real_arrival_date);
        free(flight);
    }
}

void free_flight_void(gpointer flight) {
    free_flight(flight);
}
