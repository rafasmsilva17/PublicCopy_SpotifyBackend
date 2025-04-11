#ifndef ARTIST_MANAGER_H
#define ARTIST_MANAGER_H

#include <stdlib.h>
#include <stdio.h>
#include "artist.h"
#include "uteis.h"
#include <glib.h>

void free_artist_entry(gpointer key, gpointer value, gpointer artist_data);

int get_from_artist_array_num(char* target, char*** m);

// Função para libertar uma tabela hash de artistas
void free_artist_hash_table();

void init_hashtable_artist();

GList* get_keys_artist_hash_table();


char* get_from_a(char* target, char i);



//Organiza os dados de um artista e insere na tabela hash
void organizeA (char** line);

int artist_exists(char* id);

#endif