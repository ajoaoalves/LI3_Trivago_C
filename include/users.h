#ifndef USERS_H
#define USERS_H

/**
 * @brief Estrutura abstrata para representar um user.
 */
typedef struct users User;

/**
 * @brief Obtém o ID de usuário.
 *
 * @param user 
 * @return char*
 */
char *get_user_id(User *user);

/**
 * @brief Obtém o nome do user.
 *
 * @param user 
 * @return char*
 */
char *get_user_name(User *user);

/**
 * @brief Obtém a data de nascimento do user.
 *
 * @param user 
 * @return Date*
 */
Date *get_user_birth_date(User *user);

/**
 * @brief Obtém o sexo do user.
 *
 * @param user 
 * @return char
 */
char get_user_sex(User *user);

/**
 * @brief Obtém o número do passaporte do user.
 *
 * @param user 
 * @return char*
 */
char *get_user_passport(User *user);

/**
 * @brief Obtém o código do país do user.
 *
 * @param user 
 * @return char*
 */
char *get_user_country_code(User *user);

/**
 * @brief Obtém a data de criação da conta do user.
 *
 * @param user 
 * @return Date*
 */
Date *get_user_account_creation(User *user);

/**
 * @brief Obtém o status da conta do user.
 *
 * @param user 
 * @return int
 */
int get_user_account_status(User *user);

/**
 * @brief Preenche uma estrutura User com base em um array de tokens.
 *
 * @param tokens 
 * @return User*
 */
User *completa_user(char **tokens);

/**
 * @brief Clona uma estrutura User.
 *
 * @param user 
 * @return User*
 */
User *clone_user(User *user);

/**
 * @brief Liberta a memória alocada para a estrutura User.
 *
 * @param user
 */
void free_user(User *user);

/**
 * @brief Wrapper para a função free_user, adequado para uso com GHashTable.
 *
 * Esta função é projetada para ser usada com GHashTable, onde os elementos são libertados automaticamente quando a tabela é destruída.
 *
 * @param user 
 */
void free_user_void(gpointer user);

#endif

