#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "artist_manager.h"
#include "music_manager.h"
#include <glib.h> 
#include "validation.h"
#include "albuns.h"
#include "uteis.h"



// Função que verifica a estrutura de uma lista 
int valid_type_list(char* list) {
    if (list == NULL || strlen(list) < 2) return 0;

    // Verifica se começa com '[' e termina com ']'
    if (list[0] != '[' || list[strlen(list) - 1] != ']') return 0;
    
    return 1;
}


// Função que verifica a validade do domain
int valid_domain(const char* domain) {
    int len = strlen(domain);
    if (len < 3) return 0;

    int dot_pos = -1;
    for (int i = 0; i < len; i++) {
        if (domain[i] == '.') {
            dot_pos = i;
            break;
        }
        if (!islower(domain[i])) return 0;
    }
    
    if (dot_pos == -1 || dot_pos == 0 || dot_pos == len - 1) return 0; 

    int len_rstring = len - dot_pos - 1;
    if (len_rstring < 2 || len_rstring > 3) return 0;

    return 1; 
}

// Função que verifica a validade do email
int valid_email(char* email) {
    char* at_pos = strchr(email, '@');
    if (!at_pos || at_pos == email || *(at_pos + 1) == '\0') return 0;

    // Check username
    for (char* ptr = email; ptr < at_pos; ptr++) {
        if (!islower(*ptr) && !isdigit(*ptr)) return 0;
    }

    // Check domain
    return valid_domain(at_pos + 1);
}

// Função que verifica a validade da duração da música
int valid_duration(char* duration) {
    if (strlen(duration) != 8 || duration[2] != ':' || duration[5] != ':') return 0;

    int hours, minutes, seconds;
    if (sscanf(duration, "%2d:%2d:%2d", &hours, &minutes, &seconds) != 3) return 0;

    return (hours >= 0 && hours <= 99 && minutes >= 0 && minutes < 60 && seconds >= 0 && seconds < 60);
}


// Função que verifica a validade dos inputs data
int valid_date (char* date){
    
    // Verifica se a data tem o comprimento correto
    if (strlen (date) != 10) return 0;

    // Verifica se o formato das barras está correto
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
            if (date[i] != '/')
                return 0;
        } else {
            if (isdigit(date[i]) == 0)
                return 0;
        }
    }

    int year, month, day;
    sscanf (date, "%4d/%2d/%2d", &year, &month, &day); 
    
    if (month < 1 || month > 12 || day < 1 || day > 31) return 0;

    //Verificar se data está no passado
    if (year > 2024)return 0;  
    if (year == 2024 && month > 9)return 0;  
    if (year == 2024 && month == 9 && day > 9)return 0;

    return 1;
}


// Função que verifica a validade dos inputs tipo de subscrição
int valid_subs_type (char* subT){

    return (strcmp (subT, "normal") == 0 || strcmp (subT, "premium") == 0);
}


int validPlataform(char* plataform) {

    return (strcasecmp(plataform, "desktop") == 0 || strcasecmp(plataform, "mobile") == 0);
}

int valid_artist(char* artist_list) {
    if (artist_list == NULL) return 0;

    // Tokeniza a lista de artistas
    char** tokens = tokenizeLM(artist_list);
    if (tokens == NULL) return 0;

    // Verifica cada ID de artista usando a função de validação específica
    for (int i = 0; tokens[i] != NULL; i++) {
        if (!artist_exists(tokens[i])) {
            free_tokens(tokens);
            return 0;
        }
    }

    free_tokens(tokens);
    return 1;
}


//Eventualmente alterar tokenizeAID para tokenizeLM!!!!
//Ou juntar valid_songs e valid_artist numa só função
int valid_songs(char* songs_list) {
    if (songs_list == NULL) return 0;

    // Tokeniza a lista de músicas
    char** tokens = tokenizeLM(songs_list);
    if (tokens == NULL) return 0;

    // Verifica cada ID de música usando a função de validação específica
    for (int i = 0; tokens[i] != NULL; i++) {
        if (!music_exists(tokens[i])) {
            free_tokens(tokens);
            return 0;
        }
    }
    free_tokens(tokens);
    return 1;
}


// Função que verifica a validade sintática de uma linha de um csv em específico
int syntactic_validation(char** line, char type) {

    switch (type) {
        case 'B':
            return 1;
        case 'U':  
            return (valid_email(line[1]) && valid_date(line[4]) && valid_subs_type(line[6]) && valid_type_list(line[7]));
        case 'S':
            return (valid_type_list(line[2]) && !valid_type_list(line[3]) && valid_duration(line[4]));
        case 'A':
            return (valid_type_list(line[4]));
        case 'H':
            return (valid_duration(line[4]) && validPlataform(line[5]));
        default:break;
    }
    return 0;
}

// Função que verifica a validade lógica de uma linha de um csv em específico
int logic_validation (char** line, char type){
    switch (type){
        case 'B':
            return 1;
        case 'H':
            return 1;
        case 'U':
            // Verificar se as músicas estão na tabela
            if (!valid_songs(line[7])) return 0;
            return 1;
        case 'S':
            // Verificar se os artistas estão na tabela
            if (!valid_artist(line[2]) && !album_exists(line[3])) return 0;
            return 1;
        case 'A':
            // Verificar se os artistas individuais não têm elementos na lista de artistas
            if (strcasecmp(line[6], "individual") == 0) {
                if (strlen(line[4]) > 2) return 0;
            }
            return 1;
        default:break;
    }
    return 0;
}