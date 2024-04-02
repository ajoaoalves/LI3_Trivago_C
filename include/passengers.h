#ifndef PASSENGER_H
#define PASSENGER_H

/**
 * @brief Estrutura abstrata para representar um passageiro.
 */
typedef struct passengers Passenger;

/**
 * @brief Obtém o ID do voo associado ao passageiro.
 *
 * @param passenger
 * @return int
 */
int get_passenger_flight_id(Passenger *passenger);

/**
 * @brief Obtém o ID do user associado ao passageiro.
 *
 * @param passenger 
 * @return char*
 */
char *get_passenger_user_id(Passenger *passenger);

/**
 * @brief Preenche uma estrutura Passenger com base em um array de tokens.
 *
 * @param tokens 
 * @param structure1 
 * @param structure2
 * @return Passenger*
 */
Passenger *completa_passenger(char **tokens, void *structure1, void *structure2);

/**
 * @brief Clona uma estrutura Passenger.
 *
 * @param passenger 
 * @return Passenger*
 */
Passenger *clone_passenger(Passenger *passenger);

/**
 * @brief Liberta a memória alocada para a estrutura Passenger.
 *
 * @param passenger
 */
void free_passenger(Passenger *passenger);

/**
 * @brief Wrapper para a função free_passenger, adequado para uso com GHashTable.
 *
 * Esta função é projetada para ser usada com GHashTable, onde os elementos são libertados automaticamente quando a tabela é destruída.
 *
 * @param passenger 
 */
void free_passenger_void(gpointer passenger);

#endif
