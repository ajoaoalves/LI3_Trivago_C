#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <glib.h>

#include "../include/date.h"
#include "../include/users.h"

typedef struct users {
    char * id;
    char * name;
    Date * birth_date;
    char sex;
    char * passport;
    char * country_code;
    Date * account_creation;
    int account_status;
} User;

char * get_user_id(User * user) {
    return strdup(user -> id);
}

char * get_user_name(User * user) {
    return strdup(user -> name);
}

Date * get_user_birth_date(User * user) {
    return clone_date(user -> birth_date);
}

char get_user_sex(User * user) {
    return (user -> sex);
}

char * get_user_passport(User * user) {
    return strdup(user -> passport);
}

char * get_user_country_code(User * user) {
    return strdup(user -> country_code);
}

Date * get_user_account_creation(User * user) {
    return clone_date(user -> account_creation);
}

int get_user_account_status(User * user) {
    return (user -> account_status);
}

User * create_user() { 
    return malloc(sizeof(User));
}

void string_to_lower(char * str) {
    while (* str) {
        * str = tolower(* str);
        str++;
    }
}

int valida_account_status(char * str) {
    int r;
    char * copy = strdup(str);
    string_to_lower(copy);
    if (strcmp(copy, "active") == 0) {
        r = 1;
    } else if (strcmp(copy, "inactive") == 0) {
        r = 0;
    } else {
        r = 2;
    }
    free(copy);
    return r;
}

int valida_email(char * str) {
    int arroba_pos = -1;
    int dot_pos = -1;

    if (strlen(str) < 5) return 1;

    for (int i = 0; str[i]; i++) {
        if (str[i] == '@') arroba_pos = i;
        if (str[i] == '.') dot_pos = i;
    }

    if (arroba_pos == -1 || dot_pos == -1 || arroba_pos >= dot_pos) return 1;
    if (arroba_pos < 2 || dot_pos - arroba_pos < 3 || strlen(str) - dot_pos < 3) return 1;

    return 0;
}

int valida_tokens_users(char ** tokens) {
    if (strlen(tokens[0]) == 0) return 1;
    if (strlen(tokens[1]) == 0) return 1;
    if (valida_email(tokens[2]) == 1) return 1;
    if (strlen(tokens[3]) == 0) return 1;
    if (validate_date(tokens[4])) return 1;
    if (strlen(tokens[5]) == 0) return 1;
    if (strlen(tokens[6]) == 0) return 1;
    if (strlen(tokens[7]) != 2) return 1;
    if (strlen(tokens[8]) == 0) return 1;
    if (validate_date(tokens[9])) return 1;
    if (strlen(tokens[10]) == 0) return 1;
    if (valida_account_status(tokens[11]) == 2) return 1;
    Date * data_1 = string_to_date(tokens[4]);
    Date * data_2 = string_to_date(tokens[9]);
    if (compare_date(data_1,data_2) == -1) {
        free_date(data_1);
        free_date(data_2);
        return 1;
    }
    free_date(data_1);
    free_date(data_2);
    return 0;
}

User * completa_user(char ** tokens) {
    if (valida_tokens_users(tokens)) {
        FILE * file = fopen("Resultados/users_errors.csv", "a");
        int i = 0;
        if (file != NULL) {
            while(tokens[i + 1] != NULL) fprintf(file, "%s;", tokens[i++]);
            fprintf(file, "%s\n", tokens[i]);
            fclose(file);
            return NULL;
        }
    }
    User * utilizador = create_user();
    if(!utilizador) return NULL;
    utilizador -> id = strdup(tokens[0]);
    utilizador -> name = strdup(tokens[1]);
    utilizador -> birth_date = string_to_date(tokens[4]);
    utilizador -> sex = (* tokens[5]);
    utilizador -> passport = strdup(tokens[6]);
    utilizador -> country_code = strdup(tokens[7]);
    utilizador -> account_creation = string_to_date(tokens[9]);
    utilizador -> account_status = valida_account_status(tokens[11]);
    return utilizador;
}

User * clone_user(User * user) {
    User * utilizador = create_user();
    utilizador -> id = get_user_id(user);
    utilizador -> name = get_user_name(user);
    utilizador -> birth_date = get_user_birth_date(user);
    utilizador -> sex = get_user_sex(user);
    utilizador -> passport = get_user_passport(user);
    utilizador -> country_code = get_user_country_code(user);
    utilizador -> account_creation = get_user_account_creation(user);
    utilizador -> account_status = get_user_account_status(user);
    return utilizador;
}

void free_user(User * user) {
    if(user) {
        free(user -> id);
        free(user -> name);
        free_date(user -> birth_date);
        free(user -> passport);
        free(user -> country_code);
        free_date(user -> account_creation);
        free(user);
    }
}

void free_user_void(gpointer user) {
    free_user(user);
}
