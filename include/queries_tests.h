#ifndef QUERIES_TESTS_H
#define QUERIES_TESTS_H

/**
 * @brief Executa uma query com base em informações fornecidas e catálogos, medindo o tempo de execução e validando o resultado.
 *
 * Esta função executa uma query com base em informações fornecidas, utilizando os catálogos de users, voos, reservas, passageiros e estatísticas.
 *
 * @param users_hash 
 * @param flights_hash 
 * @param reservations_hash 
 * @param passengers_hash 
 * @param tokens 
 * @param ncommand 
 */
void query_tests(Users_catalog * users_catalog, Flights_catalog * flights_catalog, Passengers_catalog * passengers_catalog, Reservations_catalog * reservations_catalog, CatalogoStats * stats, char ** tokens, char * path, int ncommand);

#endif
