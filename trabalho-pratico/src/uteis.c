#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void recuar_string(char* str, int indice) {
    int i;
    int len = strlen(str);

    for (i = indice; i < len; i++) {
        str[i] = str[i + 1];
    }

    str[len - 1] = '\0';
}


char** tokenize(char* line)
{


    char* line_copy = strdup(line);
    if (line_copy == NULL) {
        return NULL;
    }

    if ((line_copy[0] == '\"' && line_copy[1] == '[' && line_copy[2] == ']' && line_copy[3] == '\"') ||
        (line_copy[0] == '[' && line_copy[1] == ']')) {
        free(line_copy);
        return NULL;
    }

    char** strings = malloc(sizeof(char*));
    if (strings == NULL) {
        free(line_copy);
        return NULL;
    }

    size_t count = 0;
    char* token = strtok(line_copy, ",");

    while (token != NULL) {
        while (*token == ' ' || *token == '[' || *token == '\'') {
            token++;
        }

        size_t len = strlen(token);
        while (len > 0 && (token[len - 1] == ']' || token[len - 1] == '\'' || token[len - 1] == ' ')) {
            token[len - 1] = '\0';
            len--;
        }

        if ((token[0] == '\"' && token[1] == '[' && token[2] == ']' && token[3] == '\"') ||
            (token[0] == '[' && token[1] == ']')) {
            token = strtok(NULL, ",");
            continue;
        }

        strings = realloc(strings, (count + 1) * sizeof(char*));
        if (strings == NULL) {
            for (size_t i = 0; i < count; ++i) {
                free(strings[i]);
            }
            free(strings);
            free(line_copy);
            return NULL;
        }

        strings[count] = strdup(token);
        if (strings[count] == NULL) {
            for (size_t i = 0; i < count; ++i) {
                free(strings[i]);
            }
            free(strings);
            free(line_copy);
            return NULL;
        }

        count++;
        token = strtok(NULL, ",");
    }

    strings = realloc(strings, (count + 1) * sizeof(char*));
    if (strings == NULL) {
        for (size_t i = 0; i < count; ++i) {
            free(strings[i]);
        }
        free(strings);
        free(line_copy);
        return NULL;
    }

    strings[count] = NULL;
    free(line_copy);
    return strings;
}



void free_tokens(char** tokens) {
    if (tokens != NULL) {
        for (size_t i = 0; tokens[i] != NULL; ++i) {
            free(tokens[i]);  
            tokens[i] = NULL;
        }
        free(tokens);  
        tokens = NULL;
    }
}


double duas_casas_decimais(double value) {
    return floor(value * 100) / 100;
}