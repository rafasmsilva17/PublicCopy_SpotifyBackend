/**
 * @file matrix_manager.c
 * @brief Implementação das funções de gerenciamento para estatísticas.
 */

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "matrix.h"
#include "matrix_manager.h"
#include "historico_manager.h"
#include "user_manager.h"

// Índices rápidos
GHashTable* user_index_map = NULL;
GHashTable* genre_index_map = NULL;

void init_genre_index_map() {
    genre_index_map = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
    for (int i = 0; i < NUM_GENEROS; i++) {
        g_hash_table_insert(genre_index_map, g_strdup(GENEROS[i]), GINT_TO_POINTER(i));
    }
}

void create_user_genre_matrix() {
    // Obter chaves de gêneros e usuários
    GList* history_keys = getKeys_hist();
    GList* user_keys = get_keys_user_hash_table();

    num_users = g_list_length(user_keys);// Número de usuários/tamanho da matriz
    user_index_map = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);

    // Inicializar estruturas
    matriz_classificacao = malloc(num_users * sizeof(int*));
    ids_utilizadores = malloc(num_users * sizeof(char*));
    if (matriz_classificacao == NULL || ids_utilizadores == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memória para matriz_classificacao ou ids_utilizadores.\n");
        exit(1);
    }

    // Matriz toda a zeros e IDs de usuários a NULL
    for (int i = 0; i < num_users; i++) {
        matriz_classificacao[i] = calloc(NUM_GENEROS, sizeof(int));
        ids_utilizadores[i] = NULL;
        if (matriz_classificacao[i] == NULL) {
            fprintf(stderr, "Erro: Falha ao alocar memória para matriz_classificacao[%d].\n", i);
            for (int j = 0; j < i; j++) {
                free(matriz_classificacao[j]);
            }
            free(matriz_classificacao);
            free(ids_utilizadores);
            exit(1);
        }
    }

    // Adicionar todos os usuários à matriz
    int user_index = 0;
    for (GList* it = user_keys; it != NULL; it = it->next) {
        char* user_id = (char*)it->data;

        // Inserir usuário no mapa de índices
        g_hash_table_insert(user_index_map, g_strdup(user_id), GINT_TO_POINTER(user_index));
        ids_utilizadores[user_index] = g_strdup(user_id);
        user_index++;
    }

    // Preencher matriz com dados do histórico
    for (GList* it = history_keys; it != NULL; it = it->next) {
        char* history_id = (char*)it->data;
        char* user_id = get_from_hist(history_id, 'u');
        char* music_id = get_from_hist(history_id, 'm');

        int user_index = GPOINTER_TO_INT(g_hash_table_lookup(user_index_map, user_id));
        char* genre = getGenre(music_id);
        int genre_index = GPOINTER_TO_INT(g_hash_table_lookup(genre_index_map, genre));
        matriz_classificacao[user_index][genre_index]++;

        free(user_id);
        free(music_id);
        free(genre);
    }

    g_list_free(history_keys);
    g_list_free(user_keys);
}

void free_user_genre_matrix() {
    if (matriz_classificacao) {
        for (int i = 0; i < num_users; i++) {
            if (matriz_classificacao[i] != NULL) {
                free(matriz_classificacao[i]);
            }
        }
        free(matriz_classificacao);
        matriz_classificacao = NULL;
    }

    if (ids_utilizadores) {
        for (int i = 0; i < num_users; i++) {
            if (ids_utilizadores[i] != NULL) {
                g_free(ids_utilizadores[i]);
            }
        }
        free(ids_utilizadores);
        ids_utilizadores = NULL;
    }

    if (user_index_map) {
        g_hash_table_destroy(user_index_map);
        user_index_map = NULL;
    }

    if (genre_index_map) {
        g_hash_table_destroy(genre_index_map);
        genre_index_map = NULL;
    }
}