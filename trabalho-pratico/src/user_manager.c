#include <stdlib.h>
#include <stdio.h>
#include "user.h"
#include <glib.h>
#include "data_manager.h"
#include "uteis.h"
#include "user.h"

GHashTable* user_hash_table = NULL;

void init_hashtable_user()
{
    user_hash_table = g_hash_table_new(g_str_hash, g_str_equal);
}

// Função para libertar o array de músicas curtidas
void free_liked_musics_id(gchar** liked_musics_id) {
    if (liked_musics_id != NULL) {
        for (int i = 0; liked_musics_id[i] != NULL; i++) {
            g_free(liked_musics_id[i]);
        }
        g_free(liked_musics_id);
    }
}

GList* getkeys_User() {
    
    return g_hash_table_get_keys(user_hash_table); 
}

GList* get_keys_user_hash_table()
{
    GList* keys = g_hash_table_get_keys(user_hash_table);
    
    return keys;
}

int size()
{
    return g_hash_table_size(user_hash_table);
}


void free_user_entry(gpointer key, gpointer value, gpointer user_data) 
{
    free_user(value);
    free(key);
    key = NULL;
}


// Função para libertar uma tabela hash de usuários
void free_user_hash_table() {
    g_hash_table_foreach(user_hash_table, free_user_entry, NULL);
    g_hash_table_destroy(user_hash_table);
}







// Função para organizar um usuário a partir de uma linha e adicionar à tabela hash
void organizeU(char** line) 
{
    // Adiciona o utilizador à hash table
    char* ed = g_strdup(line[0]);
    g_hash_table_insert(user_hash_table, ed, organizeUser(line)); // Duplica a chave
}


gboolean user_exists(char* id)
{
    return g_hash_table_contains(user_hash_table, id);
}

// Função para obter dados de um usuário dependendo do tipo solicitado
char* get_from_u(char* id, char i, char* age_str) {

    return get_from_user(g_hash_table_lookup (user_hash_table, id), i, age_str);
}
char** get_from_u_lm(char* id){
    return get_user_likedMusics(g_hash_table_lookup (user_hash_table, id));
}

