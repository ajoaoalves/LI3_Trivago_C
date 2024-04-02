#ifndef RESERVATION_H
#define RESERVATION_H

/**
 * @brief Estrutura abstrata para representar uma reserva.
 */
typedef struct reservations Reservation;

/**
 * @brief Obtém o ID da reserva.
 *
 * @param reservation
 * @return char*
 */
char *get_reservation_id(Reservation *reservation);

/**
 * @brief Obtém o ID do usuário associado à reserva.
 *
 * @param reservation 
 * @return char*
 */
char *get_reservation_user_id(Reservation *reservation);

/**
 * @brief Obtém o ID do hotel associado à reserva.
 *
 * @param reservation 
 * @return char*
 */
char *get_reservation_hotel_id(Reservation *reservation);

/**
 * @brief Obtém o nome do hotel associado à reserva.
 *
 * @param reservation 
 * @return char*
 */
char *get_reservation_hotel_name(Reservation *reservation);

/**
 * @brief Obtém a classificação (número de estrelas) do hotel associado à reserva.
 *
 * @param reservation
 * @return int
 */
int get_reservation_hotel_stars(Reservation *reservation);

/**
 * @brief Obtém a taxa da cidade associada à reserva.
 *
 * @param reservation 
 * @return int
 */
int get_reservation_city_tax(Reservation *reservation);

/**
 * @brief Obtém a data de início da reserva.
 *
 * @param reservation 
 * @return Date*
 */
Date *get_reservation_begin_date(Reservation *reservation);

/**
 * @brief Obtém a data de término da reserva.
 *
 * @param reservation 
 * @return Date*
 */
Date *get_reservation_end_date(Reservation *reservation);

/**
 * @brief Obtém o preço por noite da reserva.
 *
 * @param reservation 
 * @return int
 */
int get_reservation_price_per_night(Reservation *reservation);

/**
 * @brief Verifica se o preço inclui pequeno-almoço.
 *
 * @param reservation 
 * @return int
 */
int get_reservation_includes_breakfast(Reservation *reservation);

/**
 * @brief Obtém a classificação da reserva.
 *
 * @param reservation 
 * @return int
 */
int get_reservation_rating(Reservation *reservation);

/**
 * @brief Preenche uma estrutura Reservation com base em um array de tokens.
 *
 * @param tokens 
 * @param structure 
 * @return Reservation*
 */
Reservation *completa_reservation(char **tokens, void *structure);

/**
 * @brief Clona uma estrutura Reservation.
 *
 * @param reservation 
 * @return Reservation*
 */
Reservation *clone_reservation(Reservation *reservation);

double precoReserva(Reservation * reserva);

/**
 * @brief Liberta a memória alocada para a estrutura Reservation.
 *
 * @param reservation
 */
void free_reservation(Reservation *reservation);

/**
 * @brief Wrapper para a função free_reservation, adequado para uso com GHashTable.
 *
 * Esta função é projetada para ser usada com GHashTable, onde os elementos são libertados automaticamente quando a tabela é destruída.
 *
 * @param reservation
 */
void free_reservation_void(gpointer reservation);

#endif

