#ifndef FLIGHTS_CATALOG_H
#define FLIGHTS_CATALOG_H

/**
 * @brief Estrutura abstrata para representar um catálogo de voos.
 */
typedef struct flights_catalog Flights_catalog;

/**
 * @brief Obtém uma estrutura de voo com base no seu ID.
 *
 * @param catalogo
 * @param id 
 * @return Flight*
 */
Flight *getFlight(Flights_catalog * catalogo, int id);

/**
 * @brief Wrapper para a função buildFlight.
 *
 * Esta função atua como um invólucro para a função buildFlight, facilitando a construção de voos.
 *
 * @param tokens 
 * @param structure1 
 * @param structure2 
 * @param structure3 
 */
void buildFlight_wrapper(char **tokens, void *structure1, void *structure2, void *structure3);

/**
 * @brief Converte um arquivo em um formato específico em uma estrutura Flights_catalog.
 *
 * Esta função recebe o caminho para um arquivo contendo informações de voos e converte essas informações em uma estrutura Flights_catalog.
 *
 * @param path 
 * @return Flights_catalog*
 */
Flights_catalog *flightsToCatalog(char *path);

/**
 * @brief Liberta a memória alocada para a estrutura Flights_catalog.
 *
 * @param catalogo
 */
void free_flights_catalog(Flights_catalog *catalogo);

#endif
