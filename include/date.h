#ifndef DATE_H
#define DATE_H

/**
 * @brief Estrutura abstrata para representar uma data e hora.
 */
typedef struct date Date;

/**
 * @brief Obtém o dia da data.
 *
 * @param date 
 * @return int
 */
int get_day(Date *date);

/**
 * @brief Obtém o mês da data.
 *
 * @param date 
 * @return int
 */
int get_month(Date *date);

/**
 * @brief Obtém o ano da data.
 *
 * @param date 
 * @return int
 */
int get_year(Date *date);

/**
 * @brief Obtém a hora da data.
 *
 * @param date 
 * @return int
 */
int get_hour(Date *date);

/**
 * @brief Obtém os minutos da data.
 *
 * @param date
 * @return int
 */
int get_minutes(Date *date);

/**
 * @brief Obtém os segundos da data.
 *
 * @param date 
 * @return int
 */
int get_seconds(Date *date);

/**
 * @brief Verifica se uma string representa uma data válida.
 *
 * @param str 
 * @return int
 */
int validate_date(char *str);

/**
 * @brief Converte uma string em uma estrutura Date.
 *
 * @param str 
 * @return Date*
 */
Date *string_to_date(const char *str);

/**
 * @brief Converte uma estrutura Date numa string com data e hora.
 *
 * @param date 
 * @return char*
 */
char *date_to_string(Date *date);

/**
 * @brief Converte uma estrutura Date numa string apenas com data.
 *
 * @param date 
 * @return char*
 */
char *small_date_to_string(Date * date);

/**
 * @brief Compara duas datas para determinar se a primeira é anterior à segunda.
 *
 * @param date_1
 * @param date_2 
 * @return int
 */
int compare_date(Date *date_1, Date *date_2);

/**
 * @brief Clona uma estrutura Date.
 *
 * @param date 
 * @return Date*
 */
Date *clone_date(Date *date);

/**
 * @brief Calcula a idade com base na data de nascimento.
 *
 * @param date
 * @return int
 */
int idade(Date *date);

/**
 * @brief Calcula o total de segundos desde uma data de referência.
 *
 * @param d 
 * @return int
 */
int calculateSeconds(Date *d);

/**
 * @brief Calcula a diferença em segundos entre duas datas.
 *
 * @param d1 
 * @param d2
 * @return int
 */
int differenceInSeconds(Date *d1, Date *d2);

/**
 * @brief Calcula a diferença em dias entre duas datas.
 *
 * @param date1 
 * @param date2
 * @return int
 */
int calculate_date_difference(Date *date1, Date *date2);

/**
 * @brief 
 *
 * @param begin_date 
 * @param end_date
 * @param reservation_begin_date
 * @param reservation_end_date
 * @return int
 */
int calculate_nights_within_range(Date * begin_date, Date * end_date, Date * reservation_begin_date, Date * reservation_end_date);

/**
 * @brief Liberta a memória alocada para a estrutura Date.
 *
 * @param date
 */
void free_date(Date *date);

#endif
