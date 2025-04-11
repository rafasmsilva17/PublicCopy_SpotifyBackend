#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <glib.h>
#include <string.h>
#include "queries.h"
#include "parsingInputs.h"
#include "estatisticas.h"
#include <time.h>

// Lê linhas de um arquivo e executa diferentes tipos de consultas (q1, q2, q3) baseadas na primeira letra da linha.
// Também mede o tempo de execução de cada grupo de consultas.
void program(char* arg, double* time, int sb)
{

    // -> abrir inputs
    FILE* fp = fopen(arg, "r");

    ssize_t read;
    char* line = NULL;
    size_t len;
    int i = 1;

    //tempos queries
    struct timespec start_1, end_1;
    struct timespec start_2, end_2;
    struct timespec start_3, end_3;
    struct timespec start_4, end_4;
    struct timespec start_5, end_5;
    struct timespec start_6, end_6;

    

    while((read= getline(&line, &len, fp) != -1))
    {
        //tempos
        if (sb == 1 && i==1 && time!=NULL) clock_gettime(CLOCK_REALTIME, &start_1);
        if(sb == 1 && i==31 && time!=NULL) clock_gettime(CLOCK_REALTIME, &start_2);
        if(sb == 1 && i==41 && time!=NULL) clock_gettime(CLOCK_REALTIME, &start_3);
        if(sb == 1 && i==46 && time!=NULL) clock_gettime(CLOCK_REALTIME, &start_4);
        if(sb == 1 && i==66 && time!=NULL) clock_gettime(CLOCK_REALTIME, &start_5);
        if(sb == 1 && i==56 && time!=NULL) clock_gettime(CLOCK_REALTIME, &start_6);

        if (sb == 2 && i==1 && time!=NULL)  clock_gettime(CLOCK_REALTIME, &start_1);
        if(sb == 2 && i==121 && time!=NULL) clock_gettime(CLOCK_REALTIME, &start_2);
        if(sb == 2 && i==241 && time!=NULL) clock_gettime(CLOCK_REALTIME, &start_3);
        if(sb == 2 && i==301 && time!=NULL) clock_gettime(CLOCK_REALTIME, &start_4);
        if(sb == 2 && i==451 && time!=NULL) clock_gettime(CLOCK_REALTIME, &start_5);
        if(sb == 2 && i==401 && time!=NULL) clock_gettime(CLOCK_REALTIME, &start_6);


        int num_len = snprintf(NULL, 0, "%d", i); 
        int filename_len = 31 + num_len;  

        char* filename = (char*)malloc(filename_len + 1); 


        sprintf(filename, "./resultados/command%d_output.txt", i);
        FILE* file = fopen(filename, "a");

        int equal = 0;
        if(line[1]=='S') equal = 1;

        switch(line[0])
        {
            case '1': 
                char* id;
                char* rest;
                
                tokenize_q(line, &id, &rest);
                q1(id, file, equal); 
                
                free(id);
                free(rest);
                break;

            case '2': 
                
                char* n = NULL;
                char* param = NULL;
                
                tokenize_q(line, &n, &param);
                if (strcmp(param, "")==0) q2(n,NULL, file, equal);
                else q2(n,param, file, equal);
                

                free(n);
                free(param);
                
                break;

            case '3': 
              
                char* ageMin = NULL;
                char* ageMax = NULL;
                tokenize_q(line,&ageMin,&ageMax);
                int agemin = atoi(ageMin);
                int agemax = atoi(ageMax);
                
                q3(agemin,agemax,file,equal);
                
                free(ageMin);
                free(ageMax);
                
                break;
            case '4':
           
                char* min = NULL;
                char* max = NULL;   
                
                tokenize_q(line,&min, &max);
                q4(min,max, file, equal);
                free(min);
                free(max);
                break;
            case '5':
                
                char* userId = NULL;
                char* num_u = NULL;   
        
                tokenize_q(line, &userId, &num_u);

                int numU = atoi(num_u);

                q5(userId, numU, file);
                free(userId);
                free(num_u);
                
                break;
            case '6':
                char* user_id = NULL;
                char* y = NULL;
                char* N = NULL;
                tokenize_q6(line,&user_id,&y,&N);
                int year = atoi(y);
                int n_art;
                if(N != NULL) n_art = atoi(N);
                else n_art = 0;
                q6(user_id,year,n_art,file);
                free(user_id);
                free(y);
                break;
        }
        

        if(sb==1)
        {
            if(i==30 && time!=NULL)
            {
                clock_gettime(CLOCK_REALTIME, &end_1);
                time[0] = (end_1.tv_sec - start_1.tv_sec) + (end_1.tv_nsec - start_1.tv_nsec)/ 1.0e9;
            }
            if(i==40 && time!=NULL)
            {
                clock_gettime(CLOCK_REALTIME, &end_2);
                time[1] = (end_2.tv_sec - start_2.tv_sec) + (end_2.tv_nsec - start_2.tv_nsec)/ 1.0e9;
                clock_gettime(CLOCK_REALTIME, &start_3);
            }
            if(i==45 && time!=NULL)
            {
                clock_gettime(CLOCK_REALTIME, &end_3);
                time[2] = (end_3.tv_sec - start_3.tv_sec) + (end_3.tv_nsec - start_3.tv_nsec)/ 1.0e9;
            }
            if(i==55 && time!=NULL)
            {
                clock_gettime(CLOCK_REALTIME, &end_4);
                time[3] = (end_4.tv_sec - start_4.tv_sec) + (end_4.tv_nsec - start_4.tv_nsec)/ 1.0e9;
            }
            if(i==75 && time!=NULL)
            {
                clock_gettime(CLOCK_REALTIME, &end_5);
                time[4] = (end_5.tv_sec - start_5.tv_sec) + (end_5.tv_nsec - start_5.tv_nsec)/ 1.0e9;
                clock_gettime(CLOCK_REALTIME, &start_3);
            }
            if(i==65 && time!=NULL)
            {
                clock_gettime(CLOCK_REALTIME, &end_6);
                time[5] = (end_6.tv_sec - start_6.tv_sec) + (end_6.tv_nsec - start_6.tv_nsec)/ 1.0e9;
            }
        }
        if(sb==2)
        {
            if(i==120 && time!=NULL)
            {
                clock_gettime(CLOCK_REALTIME, &end_1);
                time[0] = (end_1.tv_sec - start_1.tv_sec) + (end_1.tv_nsec - start_1.tv_nsec)/ 1.0e9;
            }
            if(i==240 && time!=NULL)
            {
                clock_gettime(CLOCK_REALTIME, &end_2);
                time[1] = (end_2.tv_sec - start_2.tv_sec) + (end_2.tv_nsec - start_2.tv_nsec)/ 1.0e9;
            }
            if(i==300 && time!=NULL)
            {
                clock_gettime(CLOCK_REALTIME, &end_3);
                time[2] = (end_3.tv_sec - start_3.tv_sec) + (end_3.tv_nsec - start_3.tv_nsec)/ 1.0e9;
            }
            if(i==400 && time!=NULL)
            {
                clock_gettime(CLOCK_REALTIME, &end_4);
                time[3] = (end_4.tv_sec - start_4.tv_sec) + (end_4.tv_nsec - start_4.tv_nsec)/ 1.0e9;
            }
            if(i==500 && time!=NULL)
            {
                clock_gettime(CLOCK_REALTIME, &end_5);
                time[4] = (end_5.tv_sec - start_5.tv_sec) + (end_5.tv_nsec - start_5.tv_nsec)/ 1.0e9;
            }
            if(i==450 && time!=NULL)
            {
                clock_gettime(CLOCK_REALTIME, &end_6);
                time[5] = (end_6.tv_sec - start_6.tv_sec) + (end_6.tv_nsec - start_6.tv_nsec)/ 1.0e9;
            }
        }

        i++;
        fclose(file);
        free(filename);
        
    }
    free(line);
}

//Extrai o segundo e terceiro tokens de uma linha de comando e os armazena em duas variáveis
void tokenize_q(char* line, char** result1, char** result2) {
    
    char* temp_line = strdup(line);
    char* rest = temp_line;
    char* token = strtok_r(temp_line, " ", &rest);

    
    token = strtok_r(NULL, " ", &rest);
    

    if(token!=NULL)
    {
        if(token[strlen(token)-1] == '\n')token[strlen(token)-1] = '\0';
        *result1 = strdup(token);

        if(rest!=NULL)
        {
            if(rest[strlen(rest)-1] == '\n')rest[strlen(rest)-1] = '\0';
            if(rest[strlen(rest)-1] == '\"' && rest[0] == '\"'){
                rest++;
                rest[strlen(rest)-1] = '\0';
            }
            *result2 = strdup(rest);
        }
    }

    free(temp_line);
}

void tokenize_q6(char* line, char** result1, char** result2, char** result3) {
    char* temp_line = strdup(line);
    char* rest = temp_line;
    char* token = strtok_r(temp_line, " ", &rest);

    // Extrair o primeiro token (result1)
    token = strtok_r(NULL, " ", &rest);
    if (token != NULL) {
        if (token[strlen(token) - 1] == '\n') token[strlen(token) - 1] = '\0';
        *result1 = strdup(token);

        // Extrair o segundo token (result2)
        token = strtok_r(NULL, " ", &rest);
        if (token != NULL) {
            if (token[strlen(token) - 1] == '\n') token[strlen(token) - 1] = '\0';
            *result2 = strdup(token);

            // Restante da linha (result3)
            if (rest != NULL) {
                if (rest[strlen(rest) - 1] == '\n') rest[strlen(rest) - 1] = '\0';
                if (rest[strlen(rest) - 1] == '\"' && rest[0] == '\"') {
                    rest++;
                    rest[strlen(rest) - 1] = '\0';
                }
                *result3 = strdup(rest);
            } else {
                *result3 = strdup("");
            }
        } else {
            *result2 = strdup("");
            *result3 = strdup("");
        }
    } else {
        *result1 = strdup("");
        *result2 = strdup("");
        *result3 = strdup("");
    }

    free(temp_line);
}