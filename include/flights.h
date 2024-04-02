#ifndef FLIGHTS_H
#define FLIGHTS_H

/**
 * @brief Estrutura abstrata para representar um voo.
 */
typedef struct flights Flight;

/**
 * @brief Obtém o ID do voo.
 *
 * @param flight
 * @return int
 */
int get_flight_id(Flight *flight);

/**
 * @brief Obtém a companhia aérea do voo.
 *
 * @param flight 
 * @return char*
 */
char *get_flight_airline(Flight *flight);

/**
 * @brief Obtém o modelo da avião do voo.
 *
 * @param flight
 * @return char*
 */
char *get_flight_plane_model(Flight *flight);

/**
 * @brief Obtém o número total de assentos disponíveis no voo.
 *
 * @param flight 
 * @return int
 */
int get_flight_total_seats(Flight *flight);

/**
 * @brief Obtém o local de origem do voo.
 *
 * @param flight 
 * @return char*
 */
char *get_flight_origin(Flight *flight);

/**
 * @brief Obtém o destino do voo.
 *
 * @param flight
 * @return char*
 */
char *get_flight_destination(Flight *flight);

/**
 * @brief Obtém a data programada de partida do voo.
 *
 * @param flight
 * @return Date*
 */
Date *get_flight_schedule_departure_date(Flight *flight);

/**
 * @brief Obtém a data programada de chegada do voo.
 *
 * @param flight 
 * @return Date*
 */
Date *get_flight_schedule_arrival_date(Flight *flight);

/**
 * @brief Obtém a data real de partida do voo.
 *
 * @param flight 
 * @return Date*
 */
Date *get_flight_real_departure_date(Flight *flight);

/**
 * @brief Obtém a data real de chegada do voo.
 *
 * @param flight
 * @return Date*
 */
Date *get_flight_real_arrival_date(Flight *flight);

/**
 * @brief Cria um novo voo.
 *
 * @return Flight*
 */
Flight *create_flight();

/**
 * @brief Preenche uma estrutura Flight com base em um array de tokens.
 *
 * @param tokens 
 * @return Flight*
 */
Flight *completa_flight(char **tokens);

/**
 * @brief Clona uma estrutura Flight.
 *
 * @param flight 
 * @return Flight*
 */
Flight *clone_flight(Flight *flight);

/**
 * @brief Liberta a memória alocada para a estrutura Flight.
 *
 * @param flight 
 */
void free_flight(Flight *flight);

/**
 * @brief Wrapper para a função free_flight, adequado para uso com GHashTable.
 *
 * Esta função é projetada para ser usada com GHashTable, onde os elementos são libertados automaticamente quando a tabela é destruída.
 *
 * @param flight 
 */
void free_flight_void(gpointer flight);

#endif
