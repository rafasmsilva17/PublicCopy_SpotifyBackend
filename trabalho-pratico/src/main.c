#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "data_manager.h"
#include "estatisticas.h"
#include "testes.h"
#include "limpeza.h"
#include <time.h>
#include <sys/resource.h>

#include "user.h"


int main(int argc, char** argv){

// -> Verificar se o main recebe dois inputs
    if (argc < 3){
        fprintf (stderr, "Missing Path.\n");
    }

    boot_inicial(argv);
    program(argv[2],NULL,0);

    limpeza();
    return 0;
}

