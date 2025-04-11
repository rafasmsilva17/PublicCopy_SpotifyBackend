#ifndef Q_H
#define Q_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "music.h"
#include "estatisticas.h"
#include "artist.h"
#include "music.h"
#include <glib.h>

/**
 * @brief Recebe o id de um usuário, busca os dados do usuário na tabela, e escreve as informações no arquivo de saída.
 * 
 * @param id O ID do usuário a ser buscado.
 * @param fp O arquivo de saída onde as informações do usuário serão escritas.
 */
void q1(char* id, FILE* fp, int equal);

//Recebe um número N e um parâmetro de país, e escreve no arquivo de saída as informações dos artistas de acordo com o país
void q2(char* n, char* param, FILE* fp, int equal);

typedef struct parsInt ParstrInt;

int compare(const void* a, const void* b);

void q4(char* min, char* max, FILE* fp, int equal);

//Recebe um intervalo de idades e busca os gêneros mais populares entre os usuários, escrevendo o resultado no arquivo
void q3(int agemin, int agemax, FILE* fp, int equal);


void q5(char* id, int num_rec, FILE* fp);

void q6(char* user_id,int year,int N, FILE* fp);

#endif