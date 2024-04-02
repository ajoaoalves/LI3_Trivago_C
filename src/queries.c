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
#include "../include/output.h"
#include "../include/pages.h"
#include "../include/queries.h"

// * Funções auxiliares
int q1_id_type(char * id) {
    int res = 0;

    if (strstr(id, "Book") == id) {
        res = 3; // reservation_id
    } else if (*id >= '0' && *id <= '9') {
        res = 2; // flight_id
    } else {
        res = 1; // user_id
    }

    return res; 
}

int q2_type(char * token) {
    int res = 3; 

    if (token == NULL) {
        res = 3; // ambos
    } else if (strcmp(token, "flights") == 0){
        res = 1; // flights
    } else if (strcmp(token, "reservations") == 0){
        res = 2; // reservations
    }
    
    return res;
}



// * Queries
void q1_executer(Users_catalog * users_catalog, Flights_catalog * flights_catalog, Passengers_catalog * passengers_catalog, Reservations_catalog * reservations_catalog, CatalogoStats * stats, char ** tokens, int ncommand) {
    int id_type = q1_id_type(tokens[1]);

    if (id_type == 1) {
        Q1User * detalhes = q1User(users_catalog, stats, tokens[1]);
        char * str = userDetailsToString(detalhes);

        if (ncommand) {
            if (tokens[0][1] == 'F') {
                char * qstruc[] = {"name", "sex", "age", "country_code", "passport", "number_of_flights", "number_of_reservations", "total_spent", NULL};
                flagOutput(str, ncommand, qstruc, 1);
            } else {
                defaultOutput(str, ncommand);
            }
        } else {
            if (detalhes) {
                printf("%s\n", str);
            } else {
                printf("User not found!\n");
            }
        }
        
        free(str);
        free_userDetails(detalhes);
    }
    if (id_type == 2) {
        Q1Flight * detalhes = q1Flight(flights_catalog, stats, atoi(tokens[1]));
        char * str = flightDetailsToString(detalhes);

        if (ncommand) {
            if (tokens[0][1] == 'F') {
                char * qstruc[] = {"airline", "plane_model", "origin", "destination", "schedule_departure_date", "schedule_arrival_date", "passengers", "delay", NULL}; 
                flagOutput(str, ncommand, qstruc, 1);
            } else {
                defaultOutput(str, ncommand);
            }
        } else {
            if (detalhes) {
                printf("%s\n", str);
            } else {
                printf("Flight not found!\n");
            }
        }

        free(str);
        free_flightDetails(detalhes);
    }
    if (id_type == 3) {
        Q1Reservation * detalhes = q1Reservation(stats, tokens[1]);
        char * str = reservationDetailsToString(detalhes);

        if (ncommand) {
            if (tokens[0][1] == 'F') {
                char * qstruc[] = {"hotel_id", "hotel_name", "hotel_stars", "begin_date", "end_date", "includes_breakfast", "nights", "total_price", NULL};
                flagOutput(str, ncommand, qstruc, 1);
            } else {
                defaultOutput(str, ncommand);
            }
        } else {
            if (detalhes) {
                printf("%s\n", str);
            } else {
                printf("Reservation not found!\n");
            }
        }

        free(str);
        free_reservationDetails(detalhes);
    }
}

void q2_executer(Users_catalog * users_catalog, Flights_catalog * flights_catalog, Passengers_catalog * passengers_catalog, Reservations_catalog * reservations_catalog, char ** tokens, int ncommand) {
    int type = q2_type(tokens[2]), i = 1;

    if (type == 1) {
        Q2Details * detalhes = q2Flights(users_catalog, flights_catalog, passengers_catalog, tokens[1]);
        GList * atual = get_q2Details_list(detalhes), * temp = atual;

        if (atual == NULL) {
            defaultOutput(NULL, ncommand);
        }
        
        if (ncommand) {
            while (atual != NULL) {
                Q2Flight * detalhesvoo = (Q2Flight *)atual->data;
                char * str = q2FlightToString(detalhesvoo);

                if (tokens[0][1] == 'F') {
                    char * qstruc[] = {"id", "date", NULL};
                    flagOutput(str, ncommand, qstruc, i++);
                    if (g_list_next(atual) != NULL) {
                        defaultOutput("", ncommand);
                    }
                } else {
                    defaultOutput(str, ncommand);
                }

                free(str);
                atual = g_list_next(atual);
            }
        } else {
            pages(atual, q2FlightToStringWrapper);
        }
        
        g_list_free(temp);
        free_userFlights(detalhes);
    }
    if (type == 2) {
        Q2Details * detalhes = q2Reservations(users_catalog, reservations_catalog, tokens[1]);
        GList * atual = get_q2Details_list(detalhes), * temp = atual;

        if (atual == NULL) {
            defaultOutput(NULL, ncommand);
        }
        
        if (ncommand) {
            while (atual != NULL) {
                Q2Reservation * detalhesreserva = (Q2Reservation *)atual->data;
                char * str = q2ReservationToString(detalhesreserva);

                if (tokens[0][1] == 'F') {
                    char * qstruc[] = {"id", "date", NULL};
                    flagOutput(str, ncommand, qstruc, i++);
                    if (g_list_next(atual) != NULL) {
                        defaultOutput("", ncommand);
                    }
                } else {
                    defaultOutput(str, ncommand);
                }

                free(str);
                atual = g_list_next(atual);
            }
        } else {
            pages(atual, q2ReservationToStringWrapper);
        }
        
        g_list_free(temp);
        free_userReservations(detalhes);
    }
    if (type == 3) {
        Q2Details * detalhes = q2(users_catalog, flights_catalog, passengers_catalog, reservations_catalog, tokens[1]);
        GList * atual = get_q2Details_list(detalhes), * temp = atual;
        
        if (atual == NULL) {
            defaultOutput(NULL, ncommand);
        }

        if (ncommand) {
            while (atual != NULL) {
                Q2UserDetails * detalhesutilizador = (Q2UserDetails *)atual->data;
                char * str = q2UserDetailsToString(detalhesutilizador);

                if (tokens[0][1] == 'F') {
                    char * qstruc[] = {"id", "date", "type", NULL};
                    flagOutput(str, ncommand, qstruc, i++);
                    if (g_list_next(atual) != NULL) {
                        defaultOutput("", ncommand);
                    }
                } else {
                    defaultOutput(str, ncommand);
                }

                free(str);
                atual = g_list_next(atual);
            }
        } else {
            pages(atual, q2UserDetailsToStringWrapper);
        }
        
        g_list_free(temp);
        free_q2Details(detalhes);
    }
}

void q3_executer(CatalogoStats * stats, char ** tokens, int ncommand) {
    double detalhes = q3(stats, tokens[1]);
    char str[8];
    sprintf(str, "%.3f", detalhes);

    if (ncommand) {
        if (tokens[0][1] == 'F') {
            char * qstruc[] = {"rating", NULL};
            flagOutput(str, ncommand, qstruc, 1);
        } else {
            defaultOutput(str, ncommand);
        }    
    } else {
        if (detalhes) {
            printf("%s\n", str);
        } else {
            printf("Hotel not found!\n");
        }
    }
}

void q4_executer(Reservations_catalog * reservations_catalog, CatalogoStats * stats, char ** tokens, int ncommand) {
    int i = 1;
    Q4Details * detalhes = q4(reservations_catalog, stats, tokens[1]);
    GList * atual = get_q4Details_list(detalhes), * temp = atual;

    if (atual == NULL) {
        defaultOutput(NULL, ncommand);
    }

    if (ncommand) {
        while (atual != NULL) {
            Q4Reservation * detalhesreserva = (Q4Reservation *)atual->data;
            char * str = q4ReservationToString(detalhesreserva);

            if (tokens[0][1] == 'F') {
                char * qstruc[] = {"id", "begin_date", "end_date", "user_id", "rating", "total_price", NULL};
                flagOutput(str, ncommand, qstruc, i++);
                if (g_list_next(atual) != NULL) {
                    defaultOutput("", ncommand);
                }
            } else {
                defaultOutput(str, ncommand);
            }

            free(str);
            atual = g_list_next(atual);
        }
    } else {
        pages(atual, q4ReservationToStringWrapper);
    }

    g_list_free(temp);
    free_q4Details(detalhes);
}

void q5_executer(Flights_catalog * flights_catalog, Passengers_catalog * passengers_catalog, char ** tokens, int ncommand) {
    int i = 1;
    Q5Details * detalhes = q5(flights_catalog, passengers_catalog, tokens[1], tokens[2], tokens[3]);
    GList * atual = get_q5Details_list(detalhes), * temp = atual;

    if (atual == NULL) {
        defaultOutput(NULL, ncommand);
    }

    if (ncommand) {
        while (atual != NULL) {
            Q5Flight * detalhesvoo = (Q5Flight *)atual->data;
            char * str = q5FlightToString(detalhesvoo);

            if (tokens[0][1] == 'F') {
                char * qstruc[] = {"id", "schedule_departure_date", "destination", "airline", "plane_model", NULL};
                flagOutput(str, ncommand, qstruc, i++);
                if (g_list_next(atual) != NULL) {
                    defaultOutput("", ncommand);
                }
            } else {
                defaultOutput(str, ncommand);
            }

            free(str);
            atual = g_list_next(atual);
        }
    } else {
        pages(atual, q5FlightToStringWrapper);
    }

    g_list_free(temp);
    free_q5Details(detalhes);
}

void q8_executer(Reservations_catalog * reservations_catalog, CatalogoStats * stats, char ** tokens, int ncommand) {
    int detalhes = q8(reservations_catalog, stats, tokens[1], tokens[2], tokens[3]);
    char str[8];
    sprintf(str, "%d", detalhes);

    if (ncommand) {
        if (tokens[0][1] == 'F') {
            char *qstruc[] = {"revenue", NULL};
            flagOutput(str, ncommand, qstruc, 1);
        } else {
            defaultOutput(str, ncommand);
        }
    } else {
        if (detalhes) {
            printf("%s\n", str);
        } else {
            printf("Hotel not found or invalid interval of dates!\n");
        }
    }
}   



// * Interpretador
void query(Users_catalog * users_catalog, Flights_catalog * flights_catalog, Passengers_catalog * passengers_catalog, Reservations_catalog * reservations_catalog, CatalogoStats * stats, char ** tokens, int ncommand) {
    char valor = tokens[0][0];
    if (valor >= '1' && valor <= '9') {
        switch (valor) {
            case '1':
                if (tokens[0][1] == '0') {
                    // TODO: A Query
                    break;
                }
                if (!tokens[1]) {
                    printf("Error: Not enough information.\n");
                    break;
                }
                q1_executer(users_catalog, flights_catalog, passengers_catalog, reservations_catalog, stats, tokens, ncommand);
                break;
            case '2':
                if (!tokens[1]) {
                    printf("Error: Not enough information.\n");
                    break;
                }
                q2_executer(users_catalog, flights_catalog, passengers_catalog, reservations_catalog, tokens, ncommand);
                break;
            case '3':
                if (!tokens[1]) {
                    printf("Error: Not enough information.\n");
                    break;
                }
                q3_executer(stats, tokens, ncommand);
                break;  
            case '4':
                if (!tokens[1]) {
                    printf("Error: Not enough information.\n");
                    break;
                }
                q4_executer(reservations_catalog, stats, tokens, ncommand);
                break;
            case '5':
                if (!tokens[1] || !tokens[2] || !tokens[3]) {
                    printf("Error: Not enough information.\n");
                    break;
                }
                q5_executer(flights_catalog, passengers_catalog, tokens, ncommand);
                break;
            case '6':
                // TODO: A Query
                break;
            case '7':
                // TODO: A Query
                break;
            case '8':
                if (!tokens[1] || !tokens[2] || !tokens[3]) {
                    printf("Error: Not enough information.\n");
                    break;
                }
                q8_executer(reservations_catalog, stats, tokens, ncommand);
                break;
            case '9':
                // TODO: A Query
                break;
        }

    } else {
        printf("Error: Invalid input.\n");
    }
}
