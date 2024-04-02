#ifndef USERS_CATALOG_H
#define USERS_CATALOG_H

/**
 * @brief Estrutura abstrata para representar uma HashTable de usuários.
 */
typedef struct users_catalog Users_catalog;

/**
 * @brief Obtém uma estrutura de user com base em seu ID.
 *
 * @param catalogo
 * @param id 
 * @return User*
 */
User * getUser(Users_catalog * catalogo, char * id);

/**
 * @brief Wrapper para a função buildUser.
 *
 * Esta função atua como um invólucro para a função buildUser, facilitando a construção de users.
 *
 * @param tokens 
 * @param structure1 
 * @param structure2 
 * @param structure3 
 */
void buildUser_wrapper(char ** tokens, void * structure1, void * structure2, void * structure3);

/**
 * @brief Converte um arquivo CSV de users em uma estrutura Users_catalog.
 *
 * Esta função recebe o caminho para um arquivo CSV contendo informações de usuários e converte essas informações em uma estrutura Users_catalog, que é uma HashTable de usuários.
 *
 * @param path
 * @return Users_catalog*
 */
Users_catalog * usersToCatalog(char * path);

/**
 * @brief Liberta a memória alocada para a estrutura Users_catalog.
 *
 * @param catalogo
 */
void free_users_catalog(Users_catalog * catalogo);

#endif
