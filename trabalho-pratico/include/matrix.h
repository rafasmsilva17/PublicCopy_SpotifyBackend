/**
 * @file matrix.h
 * @brief Definições das entidades e funções de acesso à matriz de usuários e géneros.
 */

#ifndef MATRIX_H
#define MATRIX_H

#define NUM_GENEROS 10

/**
 * @brief Array de strings contendo os nomes dos gêneros.
 */
extern char* GENEROS[NUM_GENEROS];

/**
 * @brief Matriz de classificação de usuários e gêneros.
 */
extern int** matriz_classificacao;

/**
 * @brief Array de strings contendo os IDs dos usuários.
 */
extern char** ids_utilizadores;

/**
 * @brief Número de usuários.
 */
extern int num_users;

/**
 * @brief Obtém a matriz de classificação de usuários e gêneros.
 * 
 * @return Ponteiro para a matriz de classificação.
 */
int** get_matriz_classificacao();

/**
 * @brief Obtém o array de IDs dos usuários.
 * 
 * @return Ponteiro para o array de IDs dos usuários.
 */
char** get_ids_utilizadores();

/**
 * @brief Obtém o número de usuários.
 * 
 * @return Número de usuários.
 */
int get_num_users();

/**
 * @brief Obtém o número de gêneros.
 * 
 * @return Número de gêneros.
 */
int get_num_generos();

#endif 