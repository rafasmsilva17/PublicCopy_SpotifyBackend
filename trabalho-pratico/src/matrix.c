/**
 * @file matrix.h
 * @brief Definições das entidades e funções de acesso à matriz de usuários e géneros.
 */
#include "stdio.h"
#include "matrix.h"

char* GENEROS[NUM_GENEROS] = {"Pop", "Classical", "Rock", "Country", "Jazz",
                              "Reggae", "Blues", "Electronic", "Hip Hop", "Metal"};
int** matriz_classificacao = NULL;
char** ids_utilizadores = NULL;
int num_users = 0;

int** get_matriz_classificacao() { return matriz_classificacao; }
char** get_ids_utilizadores() { return ids_utilizadores; }
int get_num_users() { return num_users; }
int get_num_generos() { return NUM_GENEROS; }