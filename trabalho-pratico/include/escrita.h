#ifndef ESCRITA
#define ESCRITA

#include <stdio.h>
#include <stdlib.h>

void escreve_barra(FILE *fp);

void escreve_q1_u(FILE *fp, int equal, char *email, char *full_n, char *last_name, char *country, char *age_str);

void escreve_q1_a(FILE *fp, int equal, char *name, char *type, char *country, int num, double receita);

void escreve_q2(FILE *fp, int equal, char *name, char *type, int horas, int minutos, int segundos, char *country);

void escreve_q3(FILE *fp, int equal, char *genre, int likes);

void escreve_q4(FILE *fp, int equal, char *genre, char *name, int maxI);

void escreve_q5(FILE *fp, char *recomendados);

void escreve_q6(FILE *fp, char *time_list, int num_time, char *most_artist, char *most_date, char *most_genre, char *most_album, int most_list_hour);

void escreve_q6_2(FILE *fp, char *artist, int num_art, char *formated);

/**
 * @brief Escreve linhas inválidas num ficheiro CSV de erros.
 * 
 * Cada tipo de erro ('U', 'S', ou 'A') gera um ficheiro correspondente,
 * onde são impressas as linhas inválidas no formato CSV.
 * 
 * @param line Array de strings que representa a linha inválida.
 * @param type Tipo da linha ('U', 'S', ou 'A').
 */
void escreve_erros (char** line, char type);

#endif