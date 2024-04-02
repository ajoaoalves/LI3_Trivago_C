#ifndef PASSENGERS_CATALOG_H
#define PASSENGERS_CATALOG_H

/**
 * @struct passengers_catalog
 * @brief Estrutura abstrata para representar um catálogo de passageiros.
 */
typedef struct passengers_catalog Passengers_catalog;

/**
 * @brief Obtém uma estrutura de passageiro com base num index.
 *
 * @param catalogo
 * @param index
 * @return Passanger*
 */
Passenger * getPassenger(Passengers_catalog * catalogo, int index);

/**
 * @brief Devolver o comprimento do catálogo de passageiros.
 *
 * @param catalogo
 * @return int
 */
int getPassengersLenght(Passengers_catalog * catalogo);

/**
 * @brief Wrapper para a função buildPassenger.
 *
 * Esta função atua como um invólucro para a função buildPassenger, facilitando a construção de passageiros.
 *
 * @param tokens 
 * @param structure1 
 * @param structure2 
 * @param structure3 
 */
void buildPassenger_wrapper(char **tokens, void *structure1, void *structure2, void *structure3);

/**
 * @brief Converte um arquivo em um formato específico em uma estrutura Passengers_catalog.
 *
 * Esta função recebe o caminho para um arquivo contendo informações de passageiros e converte essas informações em uma estrutura Passengers_catalog.
 *
 * @param path 
 * @param structure1 
 * @param structure2 
 * @return Um ponteiro para a estrutura Passengers_catalog resultante.
 */
Passengers_catalog *passengersToCatalog(char *path, void *structure1, void *structure2);

/**
 * @brief Liberta a memória alocada para a estrutura Passengers_catalog.
 *
 * @param catalogo A estrutura Passengers_catalog a ser libertada.
 */
void free_passengers_catalog(Passengers_catalog *catalogo);

#endif
