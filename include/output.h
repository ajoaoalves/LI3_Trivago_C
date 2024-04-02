#ifndef OUTPUT_H
#define OUTPUT_H

/**
 * @brief Produz saída formatada com base em um valor específico e no número de comando.
 *
 * Esta função produz saída formatada com base em um valor específico e no número de comando.
 *
 * @param value 
 * @param ncommand 
 */
void defaultOutput(char * details, int ncommand);

/**
 * @brief Produz saída formatada com base nas informações fornecidas, no número de comando e nas estruturas de query.
 *
 * Esta função produz saída formatada com base nas informações fornecidas, no número de comando, nas estruturas de query específicas (qstruc) e no número de output.
 *
 * @param info 
 * @param ncommand
 * @param qstruc 
 * @param i
 */
void flagOutput(char * details, int ncommand, char ** qstruc, int i);

#endif
