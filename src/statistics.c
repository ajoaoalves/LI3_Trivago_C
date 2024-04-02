#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <glib.h>

#include "../include/date.h"
#include "../include/users.h"
#include "../include/flights.h"
#include "../include/reservations.h"
#include "../include/passengers.h"
#include "../include/users_catalog.h"
#include "../include/flights_catalog.h"
#include "../include/reservations_catalog.h"
#include "../include/passengers_catalog.h"
#include "../include/statistics.h"

// * Estruturas para o catálogo de estatísticas
typedef struct cs{
    GHashTable * users;
    GHashTable * flights;
    GHashTable * reservations;
    GHashTable * hotels;
    GPtrArray * hreservations;
} CatalogoStats;

typedef struct us{
    int n_flights;
    int n_reservations;
    double total_spend;
} UserStats;

typedef struct hs{
    int soma_classificacoes;
    int total_reservas;
    double classificacao;
} HotelStats;

typedef struct hr{
    char * hotel_id;
    char * reservation_id;
    Date * begin_date;
    Date * end_date;
    char * user_id;
    int rating;
    double total_price;
} HotelReservation;



// ? Estruturas para responder à QUERY 1
typedef struct q1u{
    char * name;
    char sex;
    int age;
    char * country_code;
    char * passport;
    int n_flights;
    int n_reservations;
    double total_spend;
} Q1User;

typedef struct q1f{
    char * airline;
    char * plane_model;
    char * origin;
    char * destination;
    Date * schedule_departure_date; 
    Date * schedule_arrival_date;
    int n_passengers;
    int delay;
} Q1Flight;

typedef struct q1r{
    char * hotel_id;
    char * hotel_name;
    int hotel_stars;
    Date * begin_date;
    Date * end_date;
    int includes_breakfast; 
    int n_nights;
    double total_price;
} Q1Reservation;



// ? Estruturas para responder à QUERY 2
typedef struct q2d{
    GList * user_history;
} Q2Details;

typedef struct q2f{
    int id;
    Date * date;
} Q2Flight;

typedef struct q2r{
    char * id;
    Date * date;
} Q2Reservation;

typedef struct q2ud{
    char * id;
    Date * date;
    char * type;
} Q2UserDetails;



// ? Estruturas para responder à QUERY 4
typedef struct q4d{
    GList * reservations;
} Q4Details;

typedef struct q4r{
    char * reservation_id;
    Date * begin_date;
    Date * end_date;
    char * user_id;
    int rating;
    double total_price;
} Q4Reservation;



// ? Estruturas para responder à QUERY 5
typedef struct q5d{
    GList * flights;
} Q5Details;

typedef struct q5f{
    int id;
    Date * schedule_departure_date;
    char * destination;
    char * airline;
    char * plane_model;
} Q5Flight;



// * Getters
GList * get_q2Details_list(Q2Details * detalhes) {
    if (detalhes) {
        return g_list_copy(detalhes->user_history);
    } else {
        return NULL;
    }
}

GList * get_q4Details_list(Q4Details * detalhes) {
    if (detalhes) {
        return g_list_copy(detalhes->reservations);
    } else {
        return NULL;
    }
}

GList * get_q5Details_list(Q5Details * detalhes) {
    if (detalhes) {
        return g_list_copy(detalhes->flights);
    } else {
        return NULL;
    }
}



// * Funções para converter as estruturas acima em strings
char * userDetailsToString(Q1User * detalhes) {
    char *result = NULL;
    if (detalhes) {
        asprintf(&result, "%s;%c;%d;%s;%s;%d;%d;%.3f", detalhes->name, detalhes->sex, detalhes->age, detalhes->country_code, detalhes->passport, detalhes->n_flights, detalhes->n_reservations, detalhes->total_spend);
    }
    return result;
}

char * flightDetailsToString(Q1Flight *detalhes) {
    char *result = NULL;
    if (detalhes) {
        char * schedule_departure_date = date_to_string(detalhes->schedule_departure_date);
        char * schedule_arrival_date = date_to_string(detalhes->schedule_arrival_date);
        asprintf(&result, "%s;%s;%s;%s;%s;%s;%d;%d", detalhes->airline, detalhes->plane_model, detalhes->origin, detalhes->destination, schedule_departure_date, schedule_arrival_date, detalhes->n_passengers, detalhes->delay);
        free(schedule_departure_date);
        free(schedule_arrival_date);
    }
    return result;
}

char * reservationDetailsToString(Q1Reservation *detalhes) {
    char *result = NULL;
    if (detalhes) {
        char * begin_date = date_to_string(detalhes->begin_date);
        char * end_date = date_to_string(detalhes->end_date);
        if (detalhes->includes_breakfast == 1) {
            asprintf(&result, "%s;%s;%d;%s;%s;%s;%d;%.3f", detalhes->hotel_id, detalhes->hotel_name, detalhes->hotel_stars, begin_date, end_date, "True", detalhes->n_nights, detalhes->total_price);
        } else {
            asprintf(&result, "%s;%s;%d;%s;%s;%s;%d;%.3f", detalhes->hotel_id, detalhes->hotel_name, detalhes->hotel_stars, begin_date, end_date, "False", detalhes->n_nights, detalhes->total_price);
        }
        free(begin_date);
        free(end_date);
    }
    return result;
}

char * q2FlightToString(Q2Flight *detalhesvoo) {
    char *result = NULL;
    if (detalhesvoo) {
        char * date = small_date_to_string(detalhesvoo->date);
        asprintf(&result, "%010d;%s", detalhesvoo->id, date);
        free(date);
    }
    return result;
}

char * q2FlightToStringWrapper(gpointer detalhesvoo) {
    return(q2FlightToString(detalhesvoo));
}

char * q2ReservationToString(Q2Reservation *detalhesreserva) {
    char *result = NULL;
    if (detalhesreserva) {
        char * date = date_to_string(detalhesreserva->date);
        asprintf(&result, "%s;%s", detalhesreserva->id, date);
        free(date);
    }
    return result;
}

char * q2ReservationToStringWrapper(gpointer detalhesreserva) {
    return q2ReservationToString(detalhesreserva);
}

char * q2UserDetailsToString(Q2UserDetails *detalhesutilizador) {
    char *result = NULL;
    if (detalhesutilizador) {
        char * date = small_date_to_string(detalhesutilizador->date);
        asprintf(&result, "%s;%s;%s", detalhesutilizador->id, date, detalhesutilizador->type);
        free(date);
    }
    return result;
}

char * q2UserDetailsToStringWrapper(gpointer detalhesutilizador) {
    return q2UserDetailsToString(detalhesutilizador);
}

char * q4ReservationToString(Q4Reservation *detalhesreserva) {
    char *result = NULL;
    if (detalhesreserva) {
        char * begin_date = date_to_string(detalhesreserva->begin_date);
        char * end_date = date_to_string(detalhesreserva->end_date);
        asprintf(&result, "%s;%s;%s;%s;%d;%.3f", detalhesreserva->reservation_id, begin_date, end_date, detalhesreserva->user_id, detalhesreserva->rating, detalhesreserva->total_price);
        free(begin_date);
        free(end_date);
    }
    return result;
}

char * q4ReservationToStringWrapper(gpointer detalhesreserva) {
    return q4ReservationToString(detalhesreserva);
}

char * q5FlightToString(Q5Flight *detalhesvoo) {
    char *result = NULL;
    if (detalhesvoo) {
        char * schedule_departure_date = date_to_string(detalhesvoo->schedule_departure_date);
        asprintf(&result, "%010d;%s;%s;%s;%s", detalhesvoo->id, schedule_departure_date, detalhesvoo->destination, detalhesvoo->airline, detalhesvoo->plane_model);
        free(schedule_departure_date);
    }
    return result;
}

char * q5FlightToStringWrapper(gpointer detalhesvoo) {
    return q5FlightToString(detalhesvoo);
}



// * Funções para dar free às estruturas acima
void free_catalogo_stats(CatalogoStats * stats) {
    g_hash_table_destroy(stats->users);
    g_hash_table_destroy(stats->flights);
    g_hash_table_destroy(stats->reservations);
    g_hash_table_destroy(stats->hotels);
    g_ptr_array_free(stats->hreservations, TRUE);
    free(stats);
}

void free_user_stats(UserStats * userstats) {
    if (userstats) {
        free(userstats);
    }
}

void free_user_stats_wrapper(gpointer userstats) {
    free_user_stats(userstats);
}

void free_hotel_stats(HotelStats * hotelstats) {
    if (hotelstats) {
        free(hotelstats);
    }
}

void free_hotel_stats_wrapper(gpointer hotelstats) {
    free_hotel_stats(hotelstats);
}

void free_hotel_reservation(HotelReservation * hotelreservation) {
    if (hotelreservation) {
        free(hotelreservation -> hotel_id);
        free(hotelreservation->reservation_id);
        free_date(hotelreservation->begin_date);
        free_date(hotelreservation->end_date);
        free(hotelreservation->user_id);
        free(hotelreservation);
    }
}

void free_hotel_reservation_wrapper(gpointer hotelreservation) {
    free_hotel_reservation(hotelreservation);
}

void free_userDetails(Q1User * detalhes) {
    if (detalhes) {
        free(detalhes->name);
        free(detalhes->country_code);
        free(detalhes->passport);
        free(detalhes);
    }
}

void free_flightDetails(Q1Flight * detalhes) {
    if (detalhes) {
        free(detalhes->airline);
        free(detalhes->plane_model);
        free(detalhes->origin);
        free(detalhes->destination);
        free_date(detalhes->schedule_departure_date);
        free_date(detalhes->schedule_arrival_date);
        free(detalhes);
    }
}

void free_reservationDetails(Q1Reservation * detalhes) {
    if (detalhes) {
        free(detalhes->hotel_id);
        free(detalhes->hotel_name);
        free_date(detalhes->begin_date);
        free_date(detalhes->end_date);
        free(detalhes);
    }
}

void free_reservationDetails_void(gpointer detalhes) {
    free_reservationDetails(detalhes);
}

void free_q2Flight(Q2Flight * detalhesvoo) {
    if (detalhesvoo) {
        free_date(detalhesvoo->date);
        free(detalhesvoo);
    }
}

void free_q2Flight_void(gpointer detalhesvoo) {
    free_q2Flight(detalhesvoo);
}

void free_q2Reservation(Q2Reservation * detalhesreserva) {
    if (detalhesreserva) {
        free(detalhesreserva -> id);
        free_date(detalhesreserva -> date);
        free(detalhesreserva);
    }
}

void free_q2Reservation_void(gpointer detalhesreserva) {
    free_q2Reservation(detalhesreserva);
}

void free_q2UserDetails(Q2UserDetails * detalhesutilizador) {
    if (detalhesutilizador) {
        free(detalhesutilizador->id);
        free_date(detalhesutilizador->date);
        free(detalhesutilizador->type);
        free(detalhesutilizador);
    }
}

void free_q2UserDetails_void(gpointer detalhesutilizador) {
    free_q2UserDetails(detalhesutilizador);
}

void free_userFlights(Q2Details * detalhes) {
    if (detalhes) {
        g_list_free_full(detalhes->user_history,free_q2Flight_void);
        free(detalhes);
    }
}

void free_userReservations(Q2Details * detalhes) {
    if (detalhes) {
        g_list_free_full(detalhes->user_history,free_q2Reservation_void);
        free(detalhes);
    }
}

void free_q2Details(Q2Details * detalhes) {
    if (detalhes) {
        g_list_free_full(detalhes->user_history, free_q2UserDetails_void);
        free(detalhes);
    }
}

void free_q4Reservation(Q4Reservation * detalhesreserva) {
    if (detalhesreserva) {
        free(detalhesreserva->reservation_id);
        free_date(detalhesreserva->begin_date);
        free_date(detalhesreserva->end_date);
        free(detalhesreserva->user_id);
        free(detalhesreserva);
    }
}

void free_q4Reservation_void(gpointer detalhesreserva) {
    free_q4Reservation(detalhesreserva);
}

void free_q4Details(Q4Details * detalhes) {
    if (detalhes) {
        g_list_free_full(detalhes->reservations, free_q4Reservation_void);
        free(detalhes);
    }
}

void free_q5FLight(Q5Flight * detalhesvoo) {
    if (detalhesvoo) {
        free_date(detalhesvoo->schedule_departure_date);
        free(detalhesvoo->destination);
        free(detalhesvoo->airline);
        free(detalhesvoo->plane_model);
        free(detalhesvoo);
    }
}

void free_q5FLight_void(gpointer detalhesvoo) {
    free_q5FLight(detalhesvoo);
}

void free_q5Details(Q5Details * detalhes) {
    if (detalhes) {
        g_list_free_full(detalhes->flights, free_q5FLight_void);
        free(detalhes);
    }
}



// * Funções auxiliares
UserStats * preenche_user_stats(User * user) {
    UserStats * new = malloc(sizeof(UserStats));
    new -> n_flights = 0;
    new -> n_reservations = 0;
    new -> total_spend = 0;
    return new;
}

HotelReservation * preenche_hotel_reservation(Reservation * reservation) {
    HotelReservation * new = malloc(sizeof(HotelReservation));
    new -> hotel_id = get_reservation_hotel_id(reservation);
    new -> reservation_id = get_reservation_id(reservation);
    new -> begin_date = get_reservation_begin_date(reservation);
    new -> end_date = get_reservation_end_date(reservation);
    new -> user_id = get_reservation_user_id(reservation);
    new -> rating = get_reservation_rating(reservation);
    Date * begin_date = get_reservation_begin_date(reservation);
    Date * end_date = get_reservation_end_date(reservation);
    int begin_day = get_day(begin_date);
    int end_day = get_day(end_date);
    int n_nights = end_day - begin_day;
    int price_per_night = get_reservation_price_per_night(reservation);
    int city_tax = get_reservation_city_tax(reservation);
    double t_price = price_per_night * n_nights; 
    double tt_price = (t_price/100) * city_tax;
    double total_price =  t_price + tt_price;
    new -> total_price = total_price;
    free_date(begin_date);
    free_date(end_date);
    return new;
}

Q1User * preencheUserDetails(User * user, UserStats * userstats) {
    Q1User * utilizador = malloc(sizeof(Q1User));
    utilizador -> name = get_user_name(user);
    utilizador -> sex = get_user_sex(user);
    Date * birth_date = get_user_birth_date(user);
    utilizador -> age = idade(birth_date);
    free_date(birth_date);
    utilizador -> country_code = get_user_country_code(user);
    utilizador -> passport = get_user_passport(user);
    utilizador -> n_flights = userstats -> n_flights;
    utilizador -> n_reservations = userstats -> n_reservations;
    utilizador -> total_spend = userstats -> total_spend;
    return utilizador;
}

Q1Flight * preencheFlightDetails(Flight * flight, int n_passengers) {
    Q1Flight * voo = malloc(sizeof(Q1Flight));
    voo -> airline = get_flight_airline(flight);
    voo -> plane_model = get_flight_plane_model(flight);
    voo -> origin = get_flight_origin(flight);
    voo -> destination = get_flight_destination(flight);
    voo -> schedule_departure_date = get_flight_schedule_departure_date(flight);
    voo -> schedule_arrival_date = get_flight_schedule_arrival_date(flight);
    Date * schedule_departure_date = get_flight_schedule_departure_date(flight);
    Date * real_departure_date = get_flight_real_departure_date(flight);
    voo -> delay = differenceInSeconds(schedule_departure_date, real_departure_date);
    free_date(schedule_departure_date);
    free_date(real_departure_date);
    voo -> n_passengers = n_passengers;
    return voo;
}

Q1Reservation * preencheReservationDetails(Reservation * reservation) {
    Q1Reservation * reserva = malloc(sizeof(Q1Reservation));
    reserva -> hotel_id = get_reservation_hotel_id(reservation);
    reserva -> hotel_name = get_reservation_hotel_name(reservation);
    reserva -> hotel_stars = get_reservation_hotel_stars(reservation);
    reserva -> begin_date = get_reservation_begin_date(reservation);
    reserva -> end_date = get_reservation_end_date(reservation);
    reserva -> includes_breakfast = get_reservation_includes_breakfast(reservation);
    Date * begin_date = get_reservation_begin_date(reservation);
    Date * end_date = get_reservation_end_date(reservation);
    int begin_day = get_day(begin_date);
    int end_day = get_day(end_date);
    int n_nights = end_day - begin_day;
    reserva -> n_nights = n_nights;
    int price_per_night = get_reservation_price_per_night(reservation);
    int city_tax = get_reservation_city_tax(reservation);
    double t_price = price_per_night * n_nights; 
    double tt_price = (t_price/100) * city_tax;
    double total_price =  t_price + tt_price;
    reserva -> total_price = total_price;
    free_date(begin_date);
    free_date(end_date);
    return reserva;
}

UserStats * clone_user_stats(UserStats * old){
    UserStats * new = malloc(sizeof(UserStats));
    new -> n_flights = old -> n_flights;
    new -> n_reservations = old -> n_reservations;
    new -> total_spend = old -> total_spend;
    return new;
}

Q1Reservation * clone_reservation_details(Q1Reservation * old) {
    Q1Reservation * new = malloc(sizeof(Q1Reservation));
    new -> hotel_id = strdup(old -> hotel_id);
    new -> hotel_name = strdup(old -> hotel_name);
    new -> hotel_stars = old -> hotel_stars;
    new -> begin_date = clone_date(old -> begin_date);
    new -> end_date = clone_date(old -> end_date);
    new -> includes_breakfast = old -> includes_breakfast;
    new -> n_nights = old -> n_nights;
    new -> total_price = old -> total_price;
    return new;
}

HotelStats * clone_hotel_stats(HotelStats * old) {
    HotelStats * new = malloc(sizeof(HotelStats));
    new -> soma_classificacoes = old -> soma_classificacoes;
    new -> total_reservas = old -> total_reservas;
    new -> classificacao = old -> classificacao;
    return new;
}

int q2CompareFlights(Q2Flight * a, Q2Flight * b) {
    int comparison = compare_date(a -> date, b -> date);
    if (!comparison) {
        return a -> id - b -> id;
    }
    return comparison;
}

int q2CompareReservations(Q2Reservation * a, Q2Reservation * b) {
    int comparison = compare_date(a -> date, b -> date);
    if (!comparison) {
        return strcmp(a -> id, b -> id);
    }
    return comparison;
}

int q2CompareUserDetails(Q2UserDetails * a, Q2UserDetails * b) {
    int comparison = compare_date(a -> date, b -> date);
    if (!comparison) {
        return strcmp(a -> id, b -> id);
    }
    return comparison;
}

Q4Reservation * preencheQ4Reservation(HotelReservation * hotelreservation) {
    Q4Reservation * reserva = malloc(sizeof(Q4Reservation));
    reserva -> reservation_id = strdup(hotelreservation -> reservation_id);  
    reserva -> begin_date = clone_date(hotelreservation -> begin_date);
    reserva -> end_date = clone_date(hotelreservation -> end_date);
    reserva -> user_id = strdup(hotelreservation -> user_id);
    reserva -> rating = hotelreservation -> rating;
    reserva -> total_price = hotelreservation -> total_price;
    return reserva;
}

int q4CompareReservations(Q4Reservation * a, Q4Reservation * b) {
    int comparison = compare_date(a -> begin_date, b -> begin_date);
    if (!comparison) {
        return strcmp(a -> reservation_id, b -> reservation_id);
    }
    return comparison;
}

int compare_hotel_reservations(const HotelReservation * const * a, const HotelReservation * const * b) {
    int comparison = strcmp((*a)->hotel_id, (*b)->hotel_id);
    if (!comparison) {
        comparison = compare_date((*a)->begin_date, (*b)->begin_date);
        if (!comparison) {
            return strcmp((*a)->reservation_id, (*b)->reservation_id);
        }
        return comparison;
    }
    return comparison;
}

gint compare_hotel_reservations_wrapper(gconstpointer a, gconstpointer b) {
    return (gint) compare_hotel_reservations((const HotelReservation * const *)a, (const HotelReservation * const *)b);
}

Q5Flight * preencheQ5Flight(Flight * flight) {
    Q5Flight * voo = malloc(sizeof(Q5Flight));
    voo -> id = get_flight_id(flight);
    voo -> schedule_departure_date = get_flight_schedule_departure_date(flight);
    voo -> destination = get_flight_destination(flight);
    voo -> airline = get_flight_airline(flight);
    voo -> plane_model = get_flight_plane_model(flight);
    return voo;
}

int q5CompareFlights(Q5Flight * a, Q5Flight * b) {
    int comparison = compare_date(a -> schedule_departure_date, b -> schedule_departure_date);
    if (!comparison) {
        return a -> id - b -> id;
    }
    return comparison;
}

CatalogoStats * loadstats(Users_catalog * users_catalog, Flights_catalog * flights_catalog, Passengers_catalog * passengers_catalog, Reservations_catalog * reservations_catalog) {
    CatalogoStats * stats = malloc(sizeof(CatalogoStats));
    stats->users = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free_user_stats_wrapper);
    stats->flights = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, NULL);
    stats->reservations = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free_reservationDetails_void);
    stats->hotels = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free_hotel_stats_wrapper);
    stats->hreservations = g_ptr_array_new_with_free_func(free_hotel_reservation_wrapper);

    int passengerslenght = getPassengersLenght(passengers_catalog), reservationslenght = getReservationsLenght(reservations_catalog), i = 0;
    while (i < passengerslenght || i < reservationslenght) {
        if (i < passengerslenght) {
            Passenger * passenger = getPassenger(passengers_catalog, i);

            char * passenger_user_id = get_passenger_user_id(passenger);
            int passenger_flight_id = get_passenger_flight_id(passenger);
            User * user = getUser(users_catalog, passenger_user_id);
            Flight * flight = getFlight(flights_catalog, passenger_flight_id);
            int status = get_user_account_status(user);

            // ? QUERY 1
            if (status) {
                if (!g_hash_table_contains(stats->users, passenger_user_id)) {
                    UserStats * userstats = preenche_user_stats(user);
                    (userstats -> n_flights)++;
                    g_hash_table_insert(stats->users, passenger_user_id, userstats);
                } else {
                    UserStats * userstats = clone_user_stats(g_hash_table_lookup(stats->users, passenger_user_id));
                    (userstats -> n_flights)++;
                    g_hash_table_replace(stats->users, passenger_user_id, userstats);
                }
            } else {
                free(passenger_user_id);
            }
            if (!g_hash_table_contains(stats->flights, GINT_TO_POINTER(passenger_flight_id))) {
                int n_passengers = 1;
                g_hash_table_insert(stats->flights, GINT_TO_POINTER(passenger_flight_id), GINT_TO_POINTER(n_passengers));
            } else {
                int n_passengers = GPOINTER_TO_INT(g_hash_table_lookup(stats->flights, GINT_TO_POINTER(passenger_flight_id)));
                n_passengers++;
                g_hash_table_replace(stats->flights, GINT_TO_POINTER(passenger_flight_id), GINT_TO_POINTER(n_passengers));
            }

            free_passenger(passenger);
            free_user(user);
            free_flight(flight);
        }

        if (i < reservationslenght) {
            Reservation * reservation = getReservation(reservations_catalog, i);

            char * reservation_id = get_reservation_id(reservation);
            char * reservation_user_id = get_reservation_user_id(reservation);
            char * reservation_hotel_id = get_reservation_hotel_id(reservation);
            int rating = get_reservation_rating(reservation);
            User * user = getUser(users_catalog, reservation_user_id);
            int status = get_user_account_status(user);

            // ? QUERY 1
            if (status) {
                if (!g_hash_table_contains(stats->users, reservation_user_id)) {
                    UserStats * userstats = preenche_user_stats(user);
                    (userstats -> n_reservations)++;
                    (userstats -> total_spend) += precoReserva(reservation);
                    g_hash_table_insert(stats->users, reservation_user_id, userstats);
                } else {
                    UserStats * userstats = clone_user_stats(g_hash_table_lookup(stats->users, reservation_user_id));
                    (userstats -> n_reservations)++;
                    (userstats -> total_spend) += precoReserva(reservation);
                    g_hash_table_replace(stats->users, reservation_user_id, userstats);
                }
            } else {
                free(reservation_user_id);
            }

            Q1Reservation * q1reservation = preencheReservationDetails(reservation);
            g_hash_table_insert(stats->reservations, reservation_id, q1reservation);



            // ? QUERY 3
            if (!g_hash_table_contains(stats->hotels, reservation_hotel_id)) {
                HotelStats * hotelstats = malloc(sizeof(HotelStats));
                hotelstats -> soma_classificacoes = rating;
                hotelstats -> total_reservas = 1;
                hotelstats -> classificacao = rating;
                g_hash_table_insert(stats->hotels, reservation_hotel_id, hotelstats);
            } else {
                HotelStats * hotelstats = clone_hotel_stats(g_hash_table_lookup(stats->hotels, reservation_hotel_id));
                hotelstats -> soma_classificacoes += rating;
                hotelstats -> total_reservas++;
                hotelstats -> classificacao = (double) (hotelstats -> soma_classificacoes) / (hotelstats -> total_reservas);
                g_hash_table_replace(stats->hotels, reservation_hotel_id, hotelstats);
            }



            // ? QUERY 4
            HotelReservation * hotelreservation = preenche_hotel_reservation(reservation);
            g_ptr_array_add(stats->hreservations, hotelreservation);
    


            free_reservation(reservation);
            free_user(user);
        }

        i++;
    }

    g_ptr_array_sort(stats->hreservations, compare_hotel_reservations_wrapper);

    return stats;
}



// ? --------- Q1 ---------
Q1User * q1User(Users_catalog * users_catalog, CatalogoStats * stats, char * user_id) {
    User * utilizador = getUser(users_catalog, user_id);
    if (!utilizador || get_user_account_status(utilizador) == 0) {
        free_user(utilizador);
        return NULL;
    }
    UserStats * userstats = clone_user_stats(g_hash_table_lookup(stats->users, user_id));
    Q1User * detalhes = preencheUserDetails(utilizador, userstats);
    free_user(utilizador);
    free_user_stats(userstats);
    return detalhes;
}

Q1Flight * q1Flight(Flights_catalog * flights_catalog, CatalogoStats * stats, int flight_id) {
    Flight * voo = getFlight(flights_catalog, flight_id);
    if (!voo) {
        free_flight(voo);
        return NULL;
    }
    Q1Flight * detalhes = preencheFlightDetails(voo, GPOINTER_TO_INT(g_hash_table_lookup(stats->flights, GINT_TO_POINTER(flight_id))));
    free_flight(voo);
    return detalhes;
}

Q1Reservation * q1Reservation(CatalogoStats * stats, char * reservation_id) {
    Q1Reservation * reservationdetails = g_hash_table_lookup(stats->reservations, reservation_id);
    if (!reservationdetails) return NULL;
    return clone_reservation_details(reservationdetails);    
}



// ? --------- Q2 ---------
Q2Details * q2Flights(Users_catalog * users_catalog, Flights_catalog * flights_catalog, Passengers_catalog * passengers_catalog, char * user_id) {
    User * utilizador = getUser(users_catalog, user_id);

    if (!utilizador || get_user_account_status(utilizador) == 0) {
        free_user(utilizador);
        return NULL;
    }

    Q2Details * detalhes = malloc(sizeof(Q2Details));
    detalhes -> user_history = NULL;

    int passengerslenght = getPassengersLenght(passengers_catalog), i = 0;

    while (i < passengerslenght) {
        Passenger * passageiro = getPassenger(passengers_catalog, i);
        char * passenger_user_id = get_passenger_user_id(passageiro);
        if (strcmp(user_id, passenger_user_id) == 0) {
            int flight_id = get_passenger_flight_id(passageiro);
            Flight * voo = getFlight(flights_catalog, flight_id);
            Date * date = get_flight_schedule_departure_date(voo);
            Q2Flight * detalhesvoo = malloc(sizeof(Q2Flight));
            detalhesvoo -> id = flight_id;
            detalhesvoo -> date = date;
            detalhes -> user_history = g_list_insert_sorted(detalhes -> user_history, detalhesvoo, (GCompareFunc)q2CompareFlights);
            free_flight(voo);
        }
        free_passenger(passageiro);
        free(passenger_user_id); 
        i++;
    }

    free_user(utilizador);

    return detalhes;
}

Q2Details * q2Reservations(Users_catalog * users_catalog, Reservations_catalog * reservations_catalog, char * user_id) {
    User * utilizador = getUser(users_catalog, user_id);

    if (!utilizador || get_user_account_status(utilizador) == 0) {
        free_user(utilizador);
        return NULL;
    }

    Q2Details * detalhes = malloc(sizeof(Q2Details));
    detalhes -> user_history = NULL;

    int reservationslenght = getReservationsLenght(reservations_catalog), i = 0;

    while (i < reservationslenght) {
        Reservation * reserva = getReservation(reservations_catalog, i);
        char * reservation_user_id = get_reservation_user_id(reserva);
        if (strcmp(user_id, reservation_user_id) == 0) {
            char * reservation_id = get_reservation_id(reserva);
            Date * date = get_reservation_begin_date(reserva);
            Q2Reservation * detalhesreserva = malloc(sizeof(Q2Reservation));
            detalhesreserva -> id = reservation_id;
            detalhesreserva -> date = date;
            detalhes -> user_history = g_list_insert_sorted(detalhes -> user_history, detalhesreserva, (GCompareFunc)q2CompareReservations);
        }
        free_reservation(reserva);
        free(reservation_user_id); 
        i++;
    }

    free_user(utilizador);

    return detalhes;
}

Q2Details * q2(Users_catalog * users_catalog, Flights_catalog * flights_catalog, Passengers_catalog * passengers_catalog, Reservations_catalog * reservations_catalog, char * user_id) {
    User * utilizador = getUser(users_catalog, user_id);

    if (!utilizador || get_user_account_status(utilizador) == 0) {
        free_user(utilizador);
        return NULL;
    }

    Q2Details * detalhes = malloc(sizeof(Q2Details));
    detalhes -> user_history = NULL;

    int passengerslenght = getPassengersLenght(passengers_catalog);
    int reservationslenght = getReservationsLenght(reservations_catalog);
    int i = 0;

    while (i < passengerslenght || i < reservationslenght) {
        if (i < passengerslenght) {
            Passenger * passageiro = getPassenger(passengers_catalog, i);
            char * passenger_user_id = get_passenger_user_id(passageiro);
            if (strcmp(user_id, passenger_user_id) == 0) {
                int flight_id = get_passenger_flight_id(passageiro);
                Flight * voo = getFlight(flights_catalog, flight_id);
                Date * date = get_flight_schedule_departure_date(voo);
                Q2UserDetails * detalhesvoo = malloc(sizeof(Q2UserDetails));
                char flight_id_str[11];
                sprintf(flight_id_str, "%010d", flight_id);
                detalhesvoo -> id = strdup(flight_id_str);
                detalhesvoo -> date = date;
                detalhesvoo -> type = strdup("flight");
                detalhes -> user_history = g_list_insert_sorted(detalhes -> user_history, detalhesvoo, (GCompareFunc)q2CompareUserDetails);
                free_flight(voo);
            }
            free_passenger(passageiro);
            free(passenger_user_id); 
        }
        if (i < reservationslenght) {
            Reservation * reserva = getReservation(reservations_catalog, i);
            char * reservation_user_id = get_reservation_user_id(reserva);
            if (strcmp(user_id, reservation_user_id) == 0) {
                char * reservation_id = get_reservation_id(reserva);
                Date * date = get_reservation_begin_date(reserva);
                Q2UserDetails * detalhesreserva = malloc(sizeof(Q2UserDetails));
                detalhesreserva -> id = reservation_id;
                detalhesreserva -> date = date;
                detalhesreserva -> type = strdup("reservation");
                detalhes -> user_history = g_list_insert_sorted(detalhes -> user_history, detalhesreserva, (GCompareFunc)q2CompareUserDetails);
            }
            free_reservation(reserva);
            free(reservation_user_id); 
        }
        i++;
    }

    free_user(utilizador);

    return detalhes;
}



// ? --------- Q3 ---------
double q3(CatalogoStats * stats, char * hotel_id) {
    if (!g_hash_table_lookup(stats->hotels, hotel_id)) {
        return 0.0;
    }
    HotelStats * hotelstats = clone_hotel_stats(g_hash_table_lookup(stats->hotels, hotel_id));
    double rating = hotelstats -> classificacao;
    free_hotel_stats(hotelstats);
    return rating;
}



// ? --------- Q4 ---------
Q4Details * q4(Reservations_catalog * reservations_catalog, CatalogoStats * stats, char * hotel_id) {
    if(!g_hash_table_contains(stats->hotels, hotel_id)) {
        return NULL;
    }
    Q4Details * detalhes = malloc(sizeof(Q4Details));
    detalhes -> reservations = NULL;
    gboolean hotel_found = FALSE;
    for (int i = 0; i < stats -> hreservations -> len; i++) {
        HotelReservation *hotelreservation = g_ptr_array_index(stats->hreservations, i);
        int comparison = strcmp(hotel_id, hotelreservation->hotel_id);
        if (comparison == 0) {
            hotel_found = TRUE;
            Q4Reservation * q4reservation = preencheQ4Reservation(hotelreservation);
            detalhes->reservations = g_list_append(detalhes->reservations, q4reservation);
        } else if (hotel_found) {
            break;
        }
    }
    return detalhes;
}



// ? --------- Q5 ---------
Q5Details * q5(Flights_catalog * flights_catalog, Passengers_catalog * passengers_catalog, char * origin, char * date1, char * date2) {
    if (validate_date(date1) || validate_date(date2)) {
        return NULL;
    }
    
    Q5Details * detalhes = malloc(sizeof(Q5Details));
    detalhes -> flights = NULL;

    int passengerslenght = getPassengersLenght(passengers_catalog), i = 0, previous_flight_id = -1;

    while (i < passengerslenght) {
        Passenger * passageiro = getPassenger(passengers_catalog, i);
        int flight_id = get_passenger_flight_id(passageiro);

        if (flight_id != previous_flight_id) {
            Flight * voo = getFlight(flights_catalog, flight_id);
            char * flight_origin = get_flight_origin(voo);
            Date * date = get_flight_schedule_departure_date(voo);
            Date * begin_date = string_to_date(date1);
            Date * end_date = string_to_date(date2);

            if (strcmp(origin, flight_origin) == 0 && compare_date(begin_date, date) == 1 && compare_date(date, end_date) == 1) {
                Q5Flight * detalhesvoo = preencheQ5Flight(voo);
                detalhes -> flights = g_list_insert_sorted(detalhes -> flights, detalhesvoo, (GCompareFunc)q5CompareFlights);
            }

            previous_flight_id = flight_id;

            free_flight(voo);
            free(flight_origin);
            free_date(date);
            free_date(begin_date);
            free_date(end_date);
        }

        free_passenger(passageiro);
        i++;
    }

    return detalhes;
}



// ? --------- Q8 ---------
int q8(Reservations_catalog * reservations_catalog, CatalogoStats * stats, char * hotel_id, char * date1, char * date2) {
    int reservationslenght = getReservationsLenght(reservations_catalog), total_revenue = 0, i = 0;

    if (validate_date(date1) || validate_date(date2) || !g_hash_table_lookup(stats->hotels, hotel_id)) {
        return total_revenue;
    }

    while (i < reservationslenght) {
        Reservation * reserva = getReservation(reservations_catalog, i);

        char * reservation_hotel_id = get_reservation_hotel_id(reserva);
        Date * reservation_begin_date = get_reservation_begin_date(reserva);
        Date * reservation_end_date = get_reservation_end_date(reserva);
        Date * begin_date = string_to_date(date1);
        Date * end_date = string_to_date(date2);

        if (strcmp(hotel_id, reservation_hotel_id) == 0) {
            int nights = calculate_nights_within_range(begin_date, end_date, reservation_begin_date, reservation_end_date);
            if (nights > 0) {
                int price = get_reservation_price_per_night(reserva);
                int total = nights * price;
                total_revenue += total;
            }
        }

        free_reservation(reserva);
        free(reservation_hotel_id);
        free_date(reservation_begin_date);
        free_date(reservation_end_date);
        free_date(begin_date);
        free_date(end_date);
        i++;
    }

    return total_revenue;
}
