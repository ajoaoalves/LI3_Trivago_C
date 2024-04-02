#ifndef PAGES_H
#define PAGES_H

/**
 * @brief Imprime no terminal, em páginas, o resultado de uma interrogação.
 *
 * Esta função produz saída formatada com base numa lista de resultado e numa função que converte um elemento da lista numa string.
 *
 * @param list
 * @param toStringFunc
 */
void pages(GList * list, char * (* toStringFunc) (gpointer));

#endif
