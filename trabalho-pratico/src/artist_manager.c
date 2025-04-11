#include <stdlib.h>
#include <stdio.h>
#include "artist.h"
#include "uteis.h"
#include <glib.h>

GHashTable* artist_hash_table = NULL;

void free_artist_entry(gpointer key, gpointer value, gpointer artist_data) 
{
    free_artist(value);
    free(key);
    key = NULL;
}

int get_from_artist_array_num(char* target, char*** m)
{
    Artist* artist = g_hash_table_lookup(artist_hash_table, target);
    int size;
    *m = get_from_artist_array(artist, &size);
    return size;
}

// Função para libertar uma tabela hash de artistas
void free_artist_hash_table() {
    g_hash_table_foreach(artist_hash_table, free_artist_entry, NULL);
    g_hash_table_destroy(artist_hash_table);
}

void init_hashtable_artist()
{
    artist_hash_table = g_hash_table_new(g_str_hash, g_str_equal);
}

GList* get_keys_artist_hash_table()
{
    GList* keys = g_hash_table_get_keys(artist_hash_table);
    
    return keys;
}


char* get_from_a(char* target, char i)
{
    switch (i) {
        case 'a':
            return get_artist_id(g_hash_table_lookup(artist_hash_table, target));
        case 'n':
            return get_artist_name(g_hash_table_lookup(artist_hash_table, target));
        case 'r':
            return get_artist_recipe_per_stream(g_hash_table_lookup(artist_hash_table, target));
        case 'c':
            return get_artist_country(g_hash_table_lookup(artist_hash_table, target));
        case 't':
            return get_artist_type(g_hash_table_lookup(artist_hash_table, target));
        default:
            return NULL;
    }
}


//Organiza os dados de um artista e insere na tabela hash
void organizeA (char** line)
{
    g_hash_table_insert(artist_hash_table, g_strdup(line[0]), organizeArtist(line));
}

int artist_exists(char* id)
{
    return g_hash_table_contains(artist_hash_table, id);
}