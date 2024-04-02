#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/date.h"

#define ANO 2023
#define MES 10
#define DIA 1

typedef struct date {
    int day;
    int month;
    int year;
    int hour;
    int minutes;
    int seconds;
} Date;

int get_day(Date * date) {
    return date -> day;
}

int get_month(Date * date) {
    return date -> month;
}

int get_year(Date * date) {
    return date -> year;
}

int get_hour(Date * date) {
    return date -> hour;
}

int get_minutes(Date * date) {
    return date -> minutes;
}

int get_seconds(Date * date) {
    return date -> seconds;
}

int validate_date(char * str) {
    if (strlen(str) < 10) return 1;

    if (strlen(str) > 10) {
        if (str[10] != ' ') return 1;
    }

    int ano = 0, mes = 0, dia = 0, hora = 0, minutos = 0, segundos = 0;

    if (sscanf(str, "%d/%d/%d %d:%d:%d", &ano, &mes, &dia, &hora, &minutos, &segundos) < 3) return 1;

    if (mes < 1 || mes > 12) return 1;
    if (dia < 1 || dia > 31) return 1;
    if (hora < 0 || hora > 23) return 1;
    if (minutos < 0 || minutos > 59) return 1;
    if (segundos < 0 || segundos > 59) return 1;

    return 0;
}

Date * string_to_date(const char * str) {
    Date * date = malloc(sizeof(Date));

    int result = sscanf(str, "%d/%d/%d %d:%d:%d", &date -> year, &date -> month, &date -> day, &date -> hour, &date -> minutes, &date -> seconds);

    if (result < 6) {
        date -> hour = 0;
        date -> minutes = 0;
        date -> seconds = 0;
    }

    return date;
}

char * date_to_string(Date * date) {
    char * str = malloc(sizeof(char) * 20);

    if (get_hour(date) == 0 && get_minutes(date) == 0 && get_seconds(date) == 0) {
        sprintf(str, "%04d/%02d/%02d", date -> year, date -> month, date -> day);
    } else {
        sprintf(str, "%04d/%02d/%02d %02d:%02d:%02d", date -> year, date -> month, date -> day, date -> hour, date -> minutes, date -> seconds);
    }

    return str;
}

char * small_date_to_string(Date * date) {
    char * str = malloc(sizeof(char) * 11);

    sprintf(str, "%04d/%02d/%02d", date -> year, date -> month, date -> day);

    return str;
}

int compare_date(Date *date_1, Date *date_2) {
    int ano_1 = get_year(date_1);
    int ano_2 = get_year(date_2);

    if (ano_1 < ano_2) {
        return 1;
    } else if (ano_1 > ano_2) {
        return -1;
    } else {
        int mes_1 = get_month(date_1);
        int mes_2 = get_month(date_2);

        if (mes_1 < mes_2) {
            return 1;
        } else if (mes_1 > mes_2) {
            return -1;
        } else {
            int dia_1 = get_day(date_1);
            int dia_2 = get_day(date_2);

            if (dia_1 < dia_2) {
                return 1;
            } else if (dia_1 > dia_2) {
                return -1;
            } else {
                int hora_1 = get_hour(date_1);
                int hora_2 = get_hour(date_2);

                if (hora_1 < hora_2) {
                    return 1;
                } else if (hora_1 > hora_2) {
                    return -1;
                } else {
                    int minuto_1 = get_minutes(date_1);
                    int minuto_2 = get_minutes(date_2);

                    if (minuto_1 < minuto_2) {
                        return 1;
                    } else if (minuto_1 > minuto_2) {
                        return -1;
                    } else {
                        int segundo_1 = get_seconds(date_1);
                        int segundo_2 = get_seconds(date_2);

                        if (segundo_1 < segundo_2) {
                            return 1;
                        } else if (segundo_1 > segundo_2) {
                            return -1;
                        } else {
                            return 0;
                        }
                    }
                }
            }
        }
    }
}

Date * clone_date(Date * date) {
    Date * data = malloc(sizeof(Date));
    data -> day = get_day(date);
    data -> month = get_month(date);
    data -> year = get_year(date);
    data -> hour = get_hour(date);
    data -> minutes = get_minutes(date);
    data -> seconds = get_seconds(date);
    return data;
}

int idade(Date * date) {
    int ano = get_year(date);
    int mes = get_month(date);
    int dia = get_day(date);
    int age = ANO - ano;
    if (MES < mes || (MES == mes && DIA < dia)) age--;
    return age;
}

int calculateSeconds(Date * d) {
    int totalSeconds = get_seconds(d);
    int m = get_minutes(d);
    int h = get_hour(d);
    totalSeconds += m * 60;
    totalSeconds += h * 3600;
    return totalSeconds;
}

int differenceInSeconds(Date * d1, Date * d2) {
    int d11 = get_day(d1);
    int d22 = get_day(d2);
    int daysDiff = d22- d11;
    int seconds1 = calculateSeconds(d1);
    int seconds2 = calculateSeconds(d2);
    return (daysDiff * 86400) + (seconds2 - seconds1);
}

int calculate_date_difference(Date * date_1, Date * date_2) {
    int days_in_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int days1 = date_1 -> year * 365 + date_1 -> day;
    for (int i = 1; i < date_1->month; ++i) {
        days1 += days_in_month[i];
    }

    int days2 = date_2->year * 365 + date_2->day;
    for (int i = 1; i < date_2->month; ++i) {
        days2 += days_in_month[i];
    }

    int difference = days1 - days2;

    return difference;
}

int calculate_nights_within_range(Date * begin_date, Date * end_date, Date * reservation_begin_date, Date * reservation_end_date) {
    int nights = 0;

    Date * date1 = NULL;
    Date * date2 = NULL;

    if (compare_date(reservation_begin_date, begin_date) > 0) {
        date1 = clone_date(begin_date);
    } else {
        date1 = clone_date(reservation_begin_date);
    }

    if (compare_date(end_date, reservation_end_date) > 0) {
        date2 = clone_date(end_date);
    } else {
        date2 = clone_date(reservation_end_date);
    }

    nights = calculate_date_difference(date2, date1);

    if (compare_date(reservation_end_date, end_date) == -1) {
        nights++;
    }
    
    free_date(date1);
    free_date(date2);

    return nights;
}

void free_date(Date * date) {
    free(date);
}
