#ifndef WEEK_H
#define WEEK_H

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>
#include "music_manager.h"
#include "historico_manager.h"
#include <time.h>

typedef struct artistAggregate ArtistAggregate;

typedef struct weeklyAggregate WeeklyAggregate;

GHashTable* get_artist_hash(WeeklyAggregate* week);

void create_week_artist(WeeklyAggregate* week);

char* get_start_date(WeeklyAggregate* w);

char* get_end_date(WeeklyAggregate* w);

ArtistAggregate* create_artist_agg(char* x, int time, int time_top);

void inc_time_top(ArtistAggregate* x);

WeeklyAggregate* create_week(char* sd, char* ed);

char* get_artist_aggregate(ArtistAggregate* artist);

int get_time_top(ArtistAggregate* x);

int get_time(ArtistAggregate* x);

void add_time_num(ArtistAggregate* dest, int time);

void add_time(ArtistAggregate* dest, ArtistAggregate* src);

void inc_week(char *week);

void get_week_limits(char *date, char *start_date, char *end_date);

void organize_hist_week(char *id_hist);


#endif