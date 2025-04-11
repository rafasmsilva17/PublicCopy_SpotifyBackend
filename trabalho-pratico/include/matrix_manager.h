/**
 * @file matrix_manager.h
 * @brief Declarações das funções de gerenciamento para a matriz de usuários e géneros.
 */

#ifndef MATRIX_MANAGER_H
#define MATRIX_MANAGER_H

/**
 * @brief Inicializa o mapa de índices de gêneros.
 */
void init_genre_index_map();

/**
 * @brief Cria a matriz de classificação de usuários e gêneros.
 */
void create_user_genre_matrix();

/**
 * @brief Liberta a memória alocada para a matriz de classificação de usuários e gêneros.
 */
void free_user_genre_matrix();

#endif