#include <stdio.h>
#include <stdlib.h>
#include "testes.h"

#include <glib.h>

void comp_de_ficheiros(char* f1_caminho, char* f2_caminho, int sb) 
{
    // Abrir pastas resultados
    FILE* f_resultados = fopen(f1_caminho, "r");
    FILE* f_resultados_esperados = fopen(f2_caminho, "r");
    int i = 1;
    int controlo_certas = 0;

    int mq1, mq2, mq3, mq4, mq5, mq6;
    if(sb==1) {
        mq1=30;
        mq2=40;
        mq3=45;
        mq4=55;
        mq5=75;
        mq6=65;
    } else {
        mq1=120;
        mq2=240;
        mq3=300;
        mq4=400;
        mq5=500;
        mq6=450;
    }

    int linhas[501] = { -1 }; // Inicializar todas as linhas com -1

    while (1) {
        char filename_1[32], filename_2[32];
        sprintf(filename_1, "/command%d_output.txt", i);
        sprintf(filename_2, "/command%d_output.txt", i);

        char* caminho_1 = malloc(strlen(f1_caminho) + strlen(filename_1) + 1);
        char* caminho_2 = malloc(strlen(f2_caminho) + strlen(filename_2) + 1);
        sprintf(caminho_1, "%s%s", f1_caminho, filename_1);
        sprintf(caminho_2, "%s%s", f2_caminho, filename_2);

        FILE* f1 = fopen(caminho_1, "r");
        FILE* f2 = fopen(caminho_2, "r");

        if (!f1 || !f2) {
            free(caminho_1);
            free(caminho_2);
            if (f1) fclose(f1);
            if (f2) fclose(f2);
            break;
        }

        char* line1 = NULL;
        char* line2 = NULL;
        size_t len1 = 0, len2 = 0;
        ssize_t read1 = getline(&line1, &len1, f1);
        ssize_t read2 = getline(&line2, &len2, f2);

        int linha = 1;
        int encontrou_erro = 0;

        while (read1 != -1 && read2 != -1) {
            if (strcmp(line1, line2) != 0) {
                // Registrar a linha apenas se houver erro
                linhas[i] = linha;  
                encontrou_erro = 1;
                break;  // Sai assim que encontra uma discrepância
            }
            read1 = getline(&line1, &len1, f1);
            read2 = getline(&line2, &len2, f2);
            linha++;
        }

        // Se o arquivo de um dos resultados terminou antes do outro
        if (read1 != -1 || read2 != -1) {
            if (!encontrou_erro) {
                linhas[i] = linha;
                encontrou_erro = 1;
            }
        }

        if (!encontrou_erro) {
            controlo_certas++; // Incrementa quando não há erro
        }

        // Atualizar contagem e relatar descrepâncias conforme o número de queries
        if (i == mq1) {
            printf("Q1: %d de %d testes ok\n", controlo_certas, mq1);
            for (int j = 1; j <= mq1; j++) {
                if (linhas[j] != 0) {  // Imprime só se houver erro registrado
                    printf("   Descrepância na query %d: linha %d de \"resultados/command%d_output.txt\"\n", j, linhas[j], j);
                }
            }
            controlo_certas = 0; // Resetar a contagem de acertos para a próxima query
        }

        if (i == mq2) {
            printf("Q2: %d de %d testes ok\n", controlo_certas, mq2 - mq1);
            for (int j = mq1 + 1; j <= mq2; j++) {
                if (linhas[j] != 0) {
                    printf("   Descrepância na query %d: linha %d de \"resultados/command%d_output.txt\"\n", j, linhas[j], j);
                }
            }
            controlo_certas = 0;
        }

        if (i == mq3) {
            printf("Q3: %d de %d testes ok\n", controlo_certas, mq3 - mq2);
            for (int j = mq2 + 1; j <= mq3; j++) {
                if (linhas[j] != 0) {
                    printf("   Descrepância na query %d: linha %d de \"resultados/command%d_output.txt\"\n", j, linhas[j], j);
                }
            }
            controlo_certas = 0;
        }

        if (i == mq4) {
            printf("Q4: %d de %d testes ok\n", controlo_certas, mq4 - mq3);
            for (int j = mq3 + 1; j <= mq4; j++) {
                if (linhas[j] != 0) {
                    printf("   Descrepância na query %d: linha %d de \"resultados/command%d_output.txt\"\n", j, linhas[j], j);
                }
            }
            controlo_certas = 0;
        }
        if (i == mq5) {
            printf("Q5: %d de %d testes ok\n", controlo_certas, mq5 - mq6);
            for (int j = mq6 + 1; j <= mq5; j++) {
                if (linhas[j] != 0) {
                    printf("   Descrepância na query %d: linha %d de \"resultados/command%d_output.txt\"\n", j, linhas[j], j);
                }
            }
            controlo_certas = 0;
        }

        if (i == mq6) {
            printf("Q6: %d de %d testes ok\n", controlo_certas, mq6 - mq4);
            for (int j = mq4 + 1; j <= mq6; j++) {
                if (linhas[j] != 0) {
                    printf("   Descrepância na query %d: linha %d de \"resultados/command%d_output.txt\"\n", j, linhas[j], j);
                }
            }
            controlo_certas = 0;
        }

        free(line1);
        free(line2);
        fclose(f1);
        fclose(f2);
        free(caminho_1);
        free(caminho_2);

        i++;
    }

    fclose(f_resultados);
    fclose(f_resultados_esperados);
}



