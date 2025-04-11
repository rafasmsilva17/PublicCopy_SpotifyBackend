#ifndef WEEK_MANAGER_H
#define WEEK_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>
#include "music_manager.h"
#include "historico_manager.h"
#include <time.h>

#include "week.h"

void init_weekly();

void get_top10Artists_week(char *week, ArtistAggregate **top10);

void add_hash_count(GHashTable *table, ArtistAggregate **top);

int get_top10Artists(char *week1, char *week2, char **name);

void add_artist_to_aggregate(char *start_date, char *end_date, char *artist_name, int time);

void cleanup_week();

#endif