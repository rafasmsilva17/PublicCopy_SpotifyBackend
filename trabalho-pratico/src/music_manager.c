#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include "music.h"
#include "music_manager.h"

GHashTable* music_hash_table = NULL;

void init_hashtable_music()
{
    music_hash_table = g_hash_table_new(g_str_hash, g_str_equal);
}

int music_exists(const char* song_id)
{
    return g_hash_table_contains(music_hash_table, song_id);
}

GList* get_keys_music_hash_table()
{
    GList* keys = g_hash_table_get_keys(music_hash_table);
    return keys;
}

void free_music_hash_table() {
    GList* keys = g_hash_table_get_keys(music_hash_table);
    GList* iter = keys;
    while (iter != NULL) {
        char* key = (char*)iter->data;
        Music* music = g_hash_table_lookup(music_hash_table, key);
        free(key); 
        free_music_struct(music); 
        iter = iter->next;
    }
    g_list_free(keys);
    g_hash_table_destroy(music_hash_table);
}

char** get_music_artist(char* target){
    return get_music_artist_struct(target,g_hash_table_lookup(music_hash_table, target));
}

int get_music_time(char* target){
    return get_music_time_struct(target,g_hash_table_lookup(music_hash_table, target));
}

char* getGenre(char* id){
    return getGenre_struct(id,g_hash_table_lookup(music_hash_table, id));
}

char* get_album_name(char* target){
    return get_album_name_struct(target,g_hash_table_lookup(music_hash_table, target));
}

void organizeMusic(char** line){
    g_hash_table_insert(music_hash_table, g_strdup(line[0]), organizeMusic_struct(line));
}