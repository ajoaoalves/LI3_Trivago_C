#ifndef EXECUTER_H
#define EXECUTER_H

/**
 * @brief Divide uma string num array de strings.
 *
 * @param line
 * @param complete_date_index1
 * @param complete_date_index2
 * @return char**
 */
char ** parse_input_line(char * line, int * complete_date_index1, int * complete_date_index2);

/**
 * @brief Inicia o processamento de um lote de comandos.
 *
 * @param argv
 * @param users_catalog
 * @param flights_catalog
 * @param reservations_catalog
 * @param passengers_catalog
 * @param stats
 */
void execute(char * argv, Users_catalog * users_catalog, Flights_catalog * flights_catalog, Reservations_catalog * reservations_catalog, Passengers_catalog * passengers_catalog, CatalogoStats * stats);

#endif
