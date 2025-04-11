#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"
#include "parsingInputs.h"
#include "music.h"
#include "artist.h"
#include <glib.h>
#include "user.h"
#include "testes.h"
#include <time.h>
#include <sys/resource.h>
#include "albuns_manager.h"
#include "historico_manager.h"



void boot_inicial(char** argv);

void create_organize_manage_structs(FILE* user_csv, FILE* artist_csv, FILE* music_csv, FILE* fp_inputs);


#endif