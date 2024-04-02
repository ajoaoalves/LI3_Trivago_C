#ifndef MENUS_H
#define MENUS_H

#include "../include/statistics.h"

/**
 * @brief Imprime o menu de opções
 */
void menuUI();

/**
 * @brief Lê interrogações a partir do terminal e imprime o seu resultado
 * 
 * @param users_catalog
 * @param flights_catalog
 * @param reservations_catalog
 * @param passengers_catalog
 * @param stats
 */
void start_menu(Users_catalog * users_catalog, Flights_catalog * flights_catalog, Reservations_catalog * reservations_catalog, Passengers_catalog * passengers_catalog, CatalogoStats * stats);

#endif
