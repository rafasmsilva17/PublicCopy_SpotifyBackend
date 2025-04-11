#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>
#include "music_manager.h"
#include "historico_manager.h"
#include <time.h>
#include "week_manager.h"

// q4
typedef struct artistAggregate
{
    char artist[9];
    int total_time;
    int time_top;
} ArtistAggregate;

typedef struct weeklyAggregate
{
    char start_date[11];
    char end_date[11];
    GHashTable *artists;
} WeeklyAggregate;

GHashTable* get_artist_hash(WeeklyAggregate* week)
{
    return week->artists;
}

void create_week_artist(WeeklyAggregate* week)
{
    week->artists = g_hash_table_new_full(g_str_hash, g_str_equal, free, free);
}

char* get_start_date(WeeklyAggregate* w)
{
    return w->start_date;
}

char* get_end_date(WeeklyAggregate* w)
{
    return w->end_date;
}

WeeklyAggregate* create_week(char* sd, char* ed)
{
    WeeklyAggregate* week = malloc(sizeof(WeeklyAggregate));
    week->artists = NULL;
    strcpy(week->start_date, sd);
    strcpy(week->end_date, ed);
    week->artists = g_hash_table_new_full(g_str_hash, g_str_equal, free, free);

    return week;
}

ArtistAggregate* create_artist_agg(char* x, int time, int time_top)
{
    ArtistAggregate *a = malloc(sizeof(ArtistAggregate));
    if (x != NULL) strcpy(a->artist, x);
    a->total_time = time;
    a->time_top = time_top;
    return a;
}

void inc_time_top(ArtistAggregate* x)
{
    x->time_top++;
}

char* get_artist_aggregate(ArtistAggregate* artist)
{
    return artist->artist;
}

int get_time_top(ArtistAggregate* x)
{
    return x->time_top;
}

int get_time(ArtistAggregate* x)
{
    return x->total_time;
}

void add_time_num(ArtistAggregate* dest, int time)
{
    dest->total_time += time;
}

void add_time(ArtistAggregate* dest, ArtistAggregate* src)
{
    dest->total_time = src->total_time;
}

void inc_week(char *week)
{
    int year, month, day;
    sscanf(week, "%d/%d/%d", &year, &month, &day);

    struct tm time_info = {0};
    time_info.tm_year = year - 1900;
    time_info.tm_mon = month - 1;
    time_info.tm_mday = day;

    mktime(&time_info);

    time_info.tm_mday += 7;
    mktime(&time_info);
    int end_year = time_info.tm_year + 1900;
    int end_month = time_info.tm_mon + 1;
    int end_day = time_info.tm_mday;

    sprintf(week, "%d/%02d/%02d", end_year, end_month, end_day);
}

void get_week_limits(char *date, char *start_date, char *end_date)
{
    int year, month, day;
    sscanf(date, "%04d/%d/%d", &year, &month, &day);

    struct tm time_info = {0};
    time_info.tm_year = year - 1900; // tm_year é o ano desde 1900
    time_info.tm_mon = month - 1;    // tm_mon é 0-based (Janeiro = 0)
    time_info.tm_mday = day;

    mktime(&time_info);
    int weekday = time_info.tm_wday; // 0 = Domingo, 1 = Segunda, ..., 6 = Sábado

    time_info.tm_mday -= weekday;
    mktime(&time_info); // Normalizar a data
    int start_year = time_info.tm_year + 1900;
    int start_month = time_info.tm_mon + 1;
    int start_day = time_info.tm_mday;
    sprintf(start_date, "%d/%02d/%02d", start_year, start_month, start_day);

    if (end_date != NULL)
    {
        time_info.tm_mday += 6;
        mktime(&time_info); // Normalizar a data
        int end_year = time_info.tm_year + 1900;
        int end_month = time_info.tm_mon + 1;
        int end_day = time_info.tm_mday;
        sprintf(end_date, "%d/%02d/%02d", end_year, end_month, end_day);
    }
}