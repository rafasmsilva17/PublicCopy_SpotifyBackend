#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"
#include "parsingInputs.h"
#include "music_manager.h"
#include "artist.h"
#include <glib.h>
#include "user.h"
#include "testes.h"
#include "limpeza.h"
#include <time.h>
#include <sys/resource.h>

int main(int argc, char** argv){

// -> Verificar se o main recebe dois inputs
    if (argc < 4){
        fprintf (stderr, "Missing Path.\n");
    }

    double time[6] = {0};
    
    boot_inicial(argv);

    int sb = 0;
    printf("##PROGRAMA DE TESTES##\n");
    printf("Testes small (1) ou big (2): ");
    if(scanf("%d", &sb)!=1 || sb<1 || sb>2) {
        printf("Erro ao ler entrada\n");
        return 0;
    }

    struct timespec start, end;
    double elapsed;
    clock_gettime(CLOCK_REALTIME, &start);
    
    program(argv[2],time, sb);
    

// -> abrir pasta resultados e resultados esperados  (precisa de ser alterado para a pasta geral)
    char* caminho_resultados = "resultados";
    comp_de_ficheiros(caminho_resultados,argv[3], sb);

    //Imprimir Memória
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    printf("Memória Utilizada: %ld KB\n", r_usage.ru_maxrss);

    //tempos de queries
    printf("Tempos de execução:\n");
    printf("    Q1: %.1f ms\n",time[0]*1000);
    printf("    Q2: %.1f ms\n",time[1]*1000);
    printf("    Q3: %.1f ms\n",time[2]*1000);
    printf("    Q4: %.1f ms\n",time[3]*1000);
    printf("    Q5: %.1f ms\n",time[4]*1000);
    printf("    Q6: %.1f ms\n",time[5]*1000);

    //imprimir temp
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/ 1.0e9;
    printf("Total Time: %.0fs\n",elapsed);

    return 0;
}