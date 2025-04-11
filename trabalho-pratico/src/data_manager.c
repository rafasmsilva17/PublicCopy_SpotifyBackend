#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <sys/resource.h>

#include "parsingInputs.h"
#include "albuns_manager.h"
#include "parsing.h"

#include "data_manager.h"


void boot_inicial(char** argv)
{
    init();
    
    FILE* files[5];
    open_files(argv, files);
    
    readLine(files[0],files[1],files[2],files[3],files[4]);
    
}