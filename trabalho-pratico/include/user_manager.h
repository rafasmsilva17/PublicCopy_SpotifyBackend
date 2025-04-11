#ifndef USER_manager_H
#define USER_manager_H

#include <stdlib.h>
#include <stdio.h>
#include "user.h"
#include <glib.h>
#include "data_manager.h"
#include "uteis.h"
#include "user.h"

void init_hashtable_user();

// Função para libertar o array de músicas curtidas
void free_liked_musics_id(gchar** liked_musics_id);

GList* get_keys_user_hash_table();

int size();


GList* get_keys_user_hash_table();

void free_user_entry(gpointer key, gpointer value, gpointer user_data) ;
// Função para libertar uma tabela hash de usuários
void free_user_hash_table();





// Função para organizar um usuário a partir de uma linha e adicionar à tabela hash
void organizeU(char** line) ;


gboolean user_exists(char* id);

// Função para obter dados de um usuário dependendo do tipo solicitado
char* get_from_u(char* id, char i, char* age_str);

char** get_from_u_lm(char* id);



#endif