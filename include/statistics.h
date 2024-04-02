#ifndef STATISTICS_H
#define STATISTICS_H

/**
 * @brief Estrutura abstrata para representar um catálogo de estatísticas.
 */
typedef struct cs CatalogoStats;

/**
 * @brief Estrutura abstrata para representar a informação sobre um utilizador para responder à query 1.
 */
typedef struct q1u Q1User;

/**
 * @brief Estrutura abstrata para representar a informação sobre um voo para responder à query 1.
 */
typedef struct q1f Q1Flight;

/**
 * @brief Estrutura abstrata para representar a informação sobre uma reserva para responder à query 1.
 */
typedef struct q1r Q1Reservation;

/**
 * @brief Estrutura abstrata para representar a informação sobre um utilizador para responder à query 2.
 */
typedef struct q2d Q2Details;

/**
 * @brief Estrutura abstrata para representar um voo de um utilizador.
 */
typedef struct q2f Q2Flight;

/**
 * @brief Estrutura abstrata para representar uma reserva de um utilizador.
 */
typedef struct q2r Q2Reservation;

/**
 * @brief Estrutura abstrata para representar um voo e uma reserva de um utilizador.
 */
typedef struct q2ud Q2UserDetails;

/**
 * @brief Estrutura abstrata para representar a informação sobre um hotel para responder à query 4.
 */
typedef struct q4d Q4Details;

/**
 * @brief Estrutura abstrata para representar uma reserva de um hotel.
 */
typedef struct q4r Q4Reservation;

/**
 * @brief Estrutura abstrata para representar a informação sobre um aeroporto para responder à query 5.
 */
typedef struct q5d Q5Details;

/**
 * @brief Estrutura abstrata para representar um voo de um aeroporto.
 */
typedef struct q5f Q5Flight;

/**
 * @brief Obtém uma lista com as informaçẽs necessárias para responder à query 2.
 * 
 * @param detalhes
 * @return Glist*
 */
GList * get_q2Details_list(Q2Details * detalhes);

/**
 * @brief Obtém uma lista com as informaçẽs necessárias para responder à query 4.
 * 
 * @param detalhes
 * @return Glist*
 */
GList * get_q4Details_list(Q4Details * detalhes);

/**
 * @brief Obtém uma lista com as informaçẽs necessárias para responder à query 5.
 * 
 * @param detalhes
 * @return Glist*
 */
GList * get_q5Details_list(Q5Details * detalhes);

/**
 * @brief Converte uma estrutura Q1User numa string.
 * 
 * @param detalhes
 * @return char*
 */
char * userDetailsToString(Q1User * detalhes);

/**
 * @brief Converte uma estrutura Q1Flight numa string.
 * 
 * @param detalhes
 * @return char*
 */
char * flightDetailsToString(Q1Flight *detalhes);

/**
 * @brief Converte uma estrutura Q1Reservation numa string.
 * 
 * @param detalhes
 * @return char*
 */
char * reservationDetailsToString(Q1Reservation *detalhes);

/**
 * @brief Converte uma estrutura Q2Flight numa string.
 * 
 * @param detalhesvoo
 * @return char*
 */
char * q2FlightToString(Q2Flight *detalhesvoo);

/**
 * @brief Função wrapper da q2FlightToString.
 * 
 * @param detalhesvoo
 * @return char*
 */
char * q2FlightToStringWrapper(gpointer detalhesvoo);

/**
 * @brief Converte uma estrutura Q2Reservation numa string.
 * 
 * @param detalhesreserva
 * @return char*
 */
char * q2ReservationToString(Q2Reservation *detalhesreserva);

/**
 * @brief Função wrapper da q2ReservationToString.
 * 
 * @param detalhesreserva
 * @return char*
 */
char * q2ReservationToStringWrapper(gpointer detalhesreserva);

/**
 * @brief Converte uma estrutura Q2UserDetails numa string.
 * 
 * @param detalhesutilizador
 * @return char*
 */
char * q2UserDetailsToString(Q2UserDetails *detalhesutilizador);

/**
 * @brief Função wrapper da q2UserDetailsToString.
 * 
 * @param detalhesutilizador
 * @return char*
 */
char * q2UserDetailsToStringWrapper(gpointer detalhesutilizador);

/**
 * @brief Converte uma estrutura Q4Reservation numa string.
 * 
 * @param detalhesreserva
 * @return char*
 */
char * q4ReservationToString(Q4Reservation *detalhesreserva);

/**
 * @brief Função wrapper da q4ReservationToString.
 * 
 * @param detalhesreserva
 * @return char*
 */
char * q4ReservationToStringWrapper(gpointer detalhesreserva);

/**
 * @brief Converte uma estrutura Q5Flight numa string.
 * 
 * @param detalhesvoo
 * @return char*
 */
char * q5FlightToString(Q5Flight *detalhesvoo);

/**
 * @brief Função wrapper da q5FlightToString.
 * 
 * @param detalhesvoo
 * @return char*
 */
char * q5FlightToStringWrapper(gpointer detalhesvoo);

/**
 * @brief Liberta a memória alocada para o catálogo de estatísticas.
 * 
 * @param stats
 */
void free_catalogo_stats(CatalogoStats * stats);

/**
 * @brief Liberta a memória alocada para uma estrutura Q1User.
 * 
 * @param detalhes
 */
void free_userDetails(Q1User * detalhes);

/**
 * @brief Liberta a memória alocada para uma estrutura Q1Flight.
 * 
 * @param detalhes
 */
void free_flightDetails(Q1Flight * detalhes);

/**
 * @brief Liberta a memória alocada para uma estrutura Q1Reservation.
 * 
 * @param detalhes
 */
void free_reservationDetails(Q1Reservation * detalhes);

/**
 * @brief Liberta a memória alocada para uma estrutura Q2Details composta por uma lista de voos.
 * 
 * @param detalhes
 */
void free_userFlights(Q2Details * detalhes);

/**
 * @brief Liberta a memória alocada para uma estrutura Q2Details composta por uma lista de reservas.
 * 
 * @param detalhes
 */
void free_userReservations(Q2Details * detalhes);

/**
 * @brief Liberta a memória alocada para uma estrutura Q2Details.
 * 
 * @param detalhes
 */
void free_q2Details(Q2Details * detalhes);

/**
 * @brief Liberta a memória alocada para uma estrutura Q4Details.
 * 
 * @param detalhes
 */
void free_q4Details(Q4Details * detalhes);

/**
 * @brief Função wrapper da free_q4Details.
 * 
 * @param detalhesreserva
 */
void free_q4Reservation_void(gpointer detalhesreserva);

/**
 * @brief Liberta a memória alocada para uma estrutura Q5Details.
 * 
 * @param detalhes
 */
void free_q5Details(Q5Details * detalhes);

/**
 * @brief Preenche o catálogo das estatísticas através dos restantes.
 * 
 * @param users_catalog
 * @param flights_catalog
 * @param passengers_catalog
 * @param reservations_catalog
 * @return CatalogoStats*
 */
CatalogoStats * loadstats(Users_catalog * users_catalog, Flights_catalog * flights_catalog, Passengers_catalog * passengers_catalog, Reservations_catalog * reservations_catalog);

/**
 * @brief Realiza a consulta Q1 para um user específico.
 * 
 * Esta função realiza a consulta Q1 para um user específico, fornecendo informações sobre suas reservas e voos.
 * 
 * @param users_catalog
 * @param stats
 * @param user_id
 * @return Q1User*
 */
Q1User * q1User(Users_catalog * users_catalog, CatalogoStats * stats, char * user_id);

/**
 * @brief Realiza a consulta Q1 para um voo específico.
 * 
 * Esta função realiza a consulta Q1 para um voo específico, fornecendo informações sobre seus passageiros.
 * 
 * @param flights_catalog
 * @param stats
 * @param flight_id
 * @return Q1Flight*
 */
Q1Flight * q1Flight(Flights_catalog * flights_catalog, CatalogoStats * stats, int flight_id);

/**
 * @brief Realiza a consulta Q1 para uma reserva específica.
 *
 * Esta função realiza a consulta Q1 para uma reserva específica, fornecendo informações sobre o voo associado.
 * 
 * @param stats
 * @param reservation_id
 * @return Q1Flight*
 */
Q1Reservation * q1Reservation(CatalogoStats * stats, char * reservation_id);

/**
 * @brief Realiza a consulta Q2 para obter informações sobre os voos reservados por um user.
 *
 * Esta função realiza a consulta Q2 para obter informações sobre os voos reservados por um user específico.
 * 
 * @param users_catalog
 * @param flights_catalog
 * @param passengers_catalog
 * @param user_id
 * @return Q2Details*
 */
Q2Details * q2Flights(Users_catalog * users_catalog, Flights_catalog * flights_catalog, Passengers_catalog * passengers_catalog, char * user_id);

/**
 * @brief Realiza a consulta Q2 para obter informações sobre as reservas de um user.
 *
 * Esta função realiza a consulta Q2 para obter informações sobre as reservas de um user específico.
 * 
 * @param users_catalog
 * @param reservations_catalog
 * @param user_id
 * @return Q2Details*
 */
Q2Details * q2Reservations(Users_catalog * users_catalog, Reservations_catalog * reservations_catalog, char * user_id);

/**
 * @brief Realiza a consulta Q2 para obter informações gerais sobre um user.
 *
 * Esta função realiza a consulta Q2 para obter informações gerais sobre um user específico, incluindo suas reservas e voos.
 * 
 * @param users_catalog
 * @param flights_catalog
 * @param passengers_catalog
 * @param reservations_catalog
 * @param user_id
 * @return Q2Details*
 */
Q2Details * q2(Users_catalog * users_catalog, Flights_catalog * flights_catalog, Passengers_catalog * passengers_catalog, Reservations_catalog * reservations_catalog, char * user_id);

/**
 * @brief Calcula a classificação média de um hotel com base nas reservas.
 *
 * Esta função calcula a classificação média de um hotel com base nas reservas associadas a ele.
 * 
 * @param stats
 * @param hotel_id
 * @return double
 */
double q3(CatalogoStats * stats, char * hotel_id);

/**
 * @brief Lista reservas com base no id de um hotel.
 * 
 * @param reservations_catalog
 * @param stats
 * @param hotel_id
 * @return Q4Details*
 */
Q4Details * q4(Reservations_catalog * reservations_catalog, CatalogoStats * stats, char * hotel_id);

/**
 * @brief Lista voos com base no local de origem e em um intervalo de datas.
 *
 * Esta função lista voos com base no local de origem e em um intervalo de datas especificado.
 * 
 * @param flights_catalog
 * @param passengers_catalog
 * @param origin
 * @param begin_date
 * @param end_date
 * @return Q5Details*
 */
Q5Details * q5(Flights_catalog * flights_catalog, Passengers_catalog * passengers_catalog, char * origin, char * begin_date, char * end_date);

/**
 * @brief Calcula a receita total de um hotel em um determinado intervalo de datas.
 *
 * Esta função calcula a receita total de um hotel em um determinado intervalo de datas com base nas reservas associadas a ele.
 * 
 * @param reservations_catalog
 * @param stats
 * @param hotel_id
 * @param date1
 * @param date2
 * @return double
 */
int q8(Reservations_catalog * reservations_catalog, CatalogoStats * stats, char * hotel_id, char * date1, char * date2);

#endif
