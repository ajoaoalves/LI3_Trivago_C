#ifndef EXECUTER_TESTS_H
#define EXECUTER_TESTS_H

/**
 * @brief Inicia o processamento de um lote de comandos de testes.
 *
 * @param input
 * @param ouput
 * @param users_catalog
 * @param flights_catalog
 * @param reservations_catalog
 * @param passengers_catalog
 * @param stats
 */
void execute_tests(char * input, char * output, Users_catalog * users_catalog, Flights_catalog * flights_catalog, Reservations_catalog * reservations_catalog, Passengers_catalog * passengers_catalog, CatalogoStats * stats);

#endif
