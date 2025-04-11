#ifndef USER_H
#define USER_H

#include <stdlib.h>
#include <stdio.h>
#include "user.h"
#include <glib.h>
#include "data_manager.h"
#include "uteis.h"

typedef struct user User;


// Função para obter a data de nascimento de um usuário
char* get_birth_date(User* user);

// Função para calcular a idade de um usuário com base na data de nascimento
int get_age(User* user);

// Função para contar o número de músicas curtidas de um usuário
int num_likes (User* user);

// Função para obter as músicas curtidas de um usuário
char** get_user_likedMusics(User* user);
// Função para libertar as músicas curtidas de um usuário
void free_user_likedMusics(char** lm) ;

// Função para separar as músicas curtidas de uma linha de texto
char** tokenizeLM(char* line);


// Função para criar e alocar memória para um novo usuário
User* create_user();


void free_tokens_LM(char** tokens) ;

// Função para libertar a memória de um usuário
void free_user(User* user);

// Função para organizar um usuário a partir de uma linha e adicionar à tabela hash
User* organizeUser(char** line) ;

// Função para calcular e obter a idade de um usuário
void get_user_age(char* bd, char* age_str);


// Função para obter dados de um usuário dependendo do tipo solicitado
char* get_from_user(User* user, char i, char* age_str);


#endif