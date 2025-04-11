#ifndef PARSING_H
#define PARSING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "user_manager.h"
#include <glib.h>
#include "discografia_manager.h"
#include "week_manager.h"

void init();

void open_files(char** argv, FILE** files);

//Função de comparação usada pelo g_list_insert_sorted para ordenar os discos dos artistas.
//Ordena em ordem decrescente com base no tempo total das músicas do disco. 
int compare_disc(gconstpointer a, gconstpointer b);


/**
 * @brief Processa um arquivo CSV, validando e organizando os dados com base no tipo fornecido.
 * 
 * Esta função lê linha por linha de um arquivo CSV, ignora o cabeçalho e processa as entradas
 * com base no tipo ('A', 'B', 'S', 'U' e 'H'). As linhas válidas são organizadas nas respectivas 
 * estruturas, enquanto as inválidas são registadas como erros.
 * 
 * @param fp Ponteiro para o arquivo CSV a ser processado.
 * @param type Tipo de dado a ser processado ('A', 'B', 'S', 'U' e 'H').
 * @param organize_func Função de organização dos dados.
 */
void processFile(FILE *fp, char tipo, void (*organize_func)(char**));


/**
 * @brief Lê e processa os arquivos de artistas, músicas e usuários, além de criar as tabelas de estatísticas.
 * 
 * Esta função utiliza a 'processFile' para processar separadamente os arquivos CSV de
 * artistas, albuns, músicas, usuários e histórico.
 * 
 * @param fpA Ponteiro para o arquivo CSV de artistas.
 * @param fpAlb Ponteiro para o arquivo CSV de albuns.
 * @param fpM Ponteiro para o arquivo CSV de músicas.
 * @param fpU Ponteiro para o arquivo CSV de usuários.
 * @param fpHist Ponteiro para o arquivo CSV de histórico.
 */
void readLine(FILE* fpA, FILE* fpM, FILE* fpU, FILE* fpAlb , FILE* fpHist);

//Tokeniza uma linha de dados separada por ponto e vírgula, retornando os tokens em um array de strings.
//A linha pode ter até 8 tokens.
void tokenize_pars(char* line, char** strings);

#endif