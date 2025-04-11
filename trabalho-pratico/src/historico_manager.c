#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include "historico.h"


GHashTable* historico_hash_table = NULL;

void init_hashtable_historico()
{
    historico_hash_table = g_hash_table_new(g_str_hash, g_str_equal);
}

// Função para organizar um usuário a partir de uma linha e adicionar à tabela hash
void organizeHist(char** line) 
{
    // Adiciona o utilizador à hash table
    char* ed = g_strdup(line[0]);
    g_hash_table_insert(historico_hash_table, ed, organizehistorico(line)); // Duplica a chave
}

void free_historico_entry(gpointer key, gpointer value, gpointer historico_data) 
{
    free_historico(value);
    free(key);
    key = NULL;
}


void free_historico_hash_table() {
    g_hash_table_foreach(historico_hash_table, free_historico_entry, NULL);
    g_hash_table_destroy(historico_hash_table);
}

GList* getKeys_hist()
{
    return g_hash_table_get_keys(historico_hash_table);
}

char* get_from_hist(char* id, char x)
{
    return get_from_history(g_hash_table_lookup (historico_hash_table, id), x);
}