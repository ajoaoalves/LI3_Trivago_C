#include <glib.h>

#include "../include/date.h"
#include "../include/users.h"
#include "../include/parser.h"
#include "../include/users_catalog.h"

typedef struct users_catalog {
    GHashTable * users;
} Users_catalog;

User * getUser(Users_catalog * catalogo, char * id) {
    User * utilizador = g_hash_table_lookup(catalogo -> users, id);
    if(!utilizador) return NULL;
    return clone_user(utilizador);
}

void buildUser(char ** tokens, Users_catalog * catalogo) {
    User * utilizador = completa_user(tokens);
    if (!utilizador) return;
    char * user_id = get_user_id(utilizador);
    g_hash_table_insert(catalogo -> users, user_id, utilizador);
}

void buildUser_wrapper(char ** tokens, void * structure1, void * structure2, void * structure3) {
    return buildUser(tokens, (Users_catalog *) structure1);
}

Users_catalog * usersToCatalog(char * path) {
    Users_catalog * catalogo = malloc(sizeof(Users_catalog));
    catalogo -> users = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, free_user_void);
    parser(path, buildUser_wrapper, catalogo, NULL, NULL);
    return catalogo;
}

void free_users_catalog(Users_catalog * catalogo) {
    g_hash_table_destroy(catalogo -> users);
    free(catalogo);
}
