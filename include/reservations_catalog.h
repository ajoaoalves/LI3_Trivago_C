#ifndef RESERVATIONS_CATALOG_H
#define RESERVATIONS_CATALOG_H

/**
 * @brief Estrutura abstrata para representar um catálogo de reservas.
 */
typedef struct reservations_catalog Reservations_catalog;

/**
 * @brief Obtém uma estrutura de reserva com base num index.
 *
 * @param catalogo
 * @param index
 * @return Reservation*
 */
Reservation * getReservation(Reservations_catalog * catalogo, int index);

/**
 * @brief Devolver o comprimento do catálogo de reservas.
 *
 * @param catalogo
 * @return int
 */
int getReservationsLenght(Reservations_catalog * catalogo);

/**
 * @brief Wrapper para a função buildReservation.
 *
 * Esta função atua como um invólucro para a função buildReservation, facilitando a construção de reservas.
 *
 * @param tokens 
 * @param structure1 
 * @param structure2 
 * @param structure3 
 */
void buildReservation_wrapper(char **tokens, void *structure1, void *structure2, void *structure3);

/**
 * @brief Converte um arquivo em um formato específico em uma estrutura Reservations_catalog.
 *
 * Esta função recebe o caminho para um arquivo contendo informações de reservas e converte essas informações em uma estrutura Reservations_catalog.
 *
 * @param path 
 * @param structure 
 * @return Reservations_catalog*
 */
Reservations_catalog *reservationsToCatalog(char *path, void *structure);

/**
 * @brief Liberta a memória alocada para a estrutura Reservations_catalog.
 *
 * @param catalogo 
 */
void free_reservations_catalog(Reservations_catalog *catalogo);

#endif
