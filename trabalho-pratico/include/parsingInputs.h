#ifndef PARSING_INPUTS_H
#define PARSING_INPUTS_H


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <glib.h>
#include <string.h>
#include <time.h>

// Lê linhas de um arquivo e executa diferentes tipos de consultas (q1, q2, q3) baseadas na primeira letra da linha.
// Também mede o tempo de execução de cada grupo de consultas.
void program(char* arg, double* time, int sb);

//Extrai o segundo e terceiro tokens de uma linha de comando e os armazena em duas variáveis
void tokenize_q(char* line, char** result1, char** result2);

void tokenize_q6(char* line, char** result1, char** result2, char** result3);

#endif