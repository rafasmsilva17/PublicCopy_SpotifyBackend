#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include "albuns.h"

GHashTable* album_hash_table = NULL;

void init_hashtable_album() {
    album_hash_table = g_hash_table_new(g_str_hash, g_str_equal);
}

void organizeAlb(char** line) {
    char* id = g_strdup(line[0]);
    Album* album = organizeAlbum(line);
    g_hash_table_insert(album_hash_table, id, album);
}

void free_album_entry(gpointer key, gpointer value, gpointer historico_data) {
    free_album(value);
    free(key);
}

void free_album_hash_table() {
    g_hash_table_foreach(album_hash_table, free_album_entry, NULL);
    g_hash_table_destroy(album_hash_table);
}

int album_exists(char* id) {
    return g_hash_table_contains(album_hash_table, id);
}