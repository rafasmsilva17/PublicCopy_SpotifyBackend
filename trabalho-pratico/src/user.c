#include <stdlib.h>
#include <stdio.h>
#include "user.h"
#include <glib.h>
#include "data_manager.h"
#include "uteis.h"

typedef struct user{
    gchar username[9];
    gchar* email;
    gchar* first_name;
    gchar* last_name;
    gchar birth_date[11];
    gchar* country;
    gchar** liked_musics_id;
}User;



// Função para obter a data de nascimento de um usuário
char* get_birth_date(User* user){
    return g_strdup(user->birth_date);
}

// Função para calcular a idade de um usuário com base na data de nascimento
int get_age(User* user)
{
    
    char* bd = get_birth_date(user);
    
    if (user == NULL || bd == NULL) {
        return -1;  
    }
    
    int year, month, day;
    int age = 0;
    
    
    sscanf(bd, "%4d/%2d/%2d", &year, &month, &day);
    

    age = 2024 - year;
    if (month > 9 || (month == 9 && day > 9)) {
        age--;  
    }
    
    return age;

}

// Função para contar o número de músicas curtidas de um usuário
int num_likes (User* user){
    int length = 0;
    while (user->liked_musics_id[length] != NULL) {
        length++;
    }
    return length;
}

// Função para obter as músicas curtidas de um usuário
char** get_user_likedMusics(User* user){
    int numlikes = num_likes(user);
    char** lm = malloc(sizeof(char*) * (numlikes+1));
    if(!lm) return NULL;

    for(int i = 0; i<numlikes;i++){
        lm[i] = strdup(user->liked_musics_id[i]);
    }
    lm[numlikes] = NULL;
    return lm;
}

// Função para libertar as músicas curtidas de um usuário
void free_user_likedMusics(char** lm) {
    for (int i = 0; lm[i] != NULL; i++) {
        free(lm[i]);
    }
    free(lm);
}


// Função para criar e alocar memória para um novo usuário
User* create_user()
{
    User* new = malloc(sizeof(User));
    new->email = NULL;
    new->first_name = NULL;
    new->last_name = NULL;
    new->country = NULL;
    new->liked_musics_id = NULL;
    return new;
}


void free_tokens_LM(char** tokens) {
    if (tokens != NULL) {
        for (size_t i = 0; tokens[i] != NULL; ++i) {
            free(tokens[i]);  // Libera cada string alocada
            tokens[i]=NULL;
        }
        free(tokens);  // Libera o array de ponteiros
        tokens = NULL;
    }
}


// Função para separar as músicas curtidas de uma linha de texto
char** tokenizeLM(char* line)
{
    char* line_copy = strdup(line);  // Faz uma cópia da linha original
    if (line_copy == NULL) {
        perror("strdup failed");
        return NULL;
    }

    // Inicializa o ponteiro para armazenar os tokens
    char** strings = malloc(sizeof(char*)); 
    if (strings == NULL) {
        perror("malloc failed");
        free(line_copy);
        return NULL;
    }

    size_t count = 0;
    char* token = strtok(line_copy, ",");  // Divide a linha por vírgulas

    while (token != NULL) {
        // Remove espaços em branco à esquerda
        while (*token == ' ' || *token == '[' || *token == '\'') {
            token++;
        }

        // Remove caracteres '[' e ']' e apaga espaços em branco à direita
        size_t len = strlen(token);
        while (len > 0 && (token[len - 1] == ']' || token[len - 1] == '\'' || token[len - 1] == ' ')) {
            token[len - 1] = '\0';
            len--;
        }

        // Realoca o espaço para armazenar o próximo token
        strings = realloc(strings, (count + 1) * sizeof(char*));
        if (strings == NULL) {
            perror("realloc failed");
            // Libera memória antes de retornar
            for (size_t i = 0; i < count; ++i) {
                free(strings[i]);
            }
            free(strings);
            free(line_copy);
            return NULL;
        }

        strings[count] = strdup(token);  // Aloca e copia o token
        if (strings[count] == NULL) {
            perror("strdup failed");
            // Libera memória antes de retornar
            for (size_t i = 0; i < count; ++i) {
                free(strings[i]);
            }
            free(strings);
            free(line_copy);
            return NULL;
        }

        count++;
        token = strtok(NULL, ",");  // Continua para o próximo token
    }

    // Marca o final da lista de tokens
    strings = realloc(strings, (count + 1) * sizeof(char*));  // Realoca para garantir espaço para o NULL
    strings[count] = NULL;  
    free(line_copy);  // Libera a cópia da linha
    return strings;
}


// Função para libertar a memória de um usuário
void free_user(User* user) {
    if (user != NULL) {
        g_free(user->email);
        user->email = NULL; // Definindo para NULL após liberar
        g_free(user->first_name);
        user->first_name = NULL; // Definindo para NULL após liberar
        g_free(user->last_name);
        user->last_name = NULL; // Definindo para NULL após liberar
        g_free(user->country);
        user->country = NULL; // Definindo para NULL após liberar

        free_tokens_LM(user->liked_musics_id);
        user->liked_musics_id = NULL; // Definindo para NULL após liberar

        g_free(user); // Liberando a estrutura User
        user = NULL;
    }
}

// Função para organizar um usuário a partir de uma linha e adicionar à tabela hash
User* organizeUser(char** line) 
{
    User* user = create_user();
    strcpy(user->username, line[0]);

    user->email = g_strdup(line[1]);
  
    user->first_name = g_strdup(line[2]); 

    user->last_name = g_strdup(line[3]);  

    strcpy(user->birth_date, line[4]);

    user->country = g_strdup(line[5]);    

    user->liked_musics_id = tokenizeLM(line[7]);


    return user;
}

// Função para calcular e obter a idade de um usuário

void get_user_age(char* bd, char* age_str) {
    int year, month, day;
    int r = 0;

    sscanf(bd, "%4d/%2d/%2d", &year, &month, &day);

    r = 2024 - year - 1;
    if (month < 9 || (month == 9 && day <= 9)) r++;

    
    sprintf(age_str, "%d", r);
    
    
}


// Função para obter dados de um usuário dependendo do tipo solicitado
char* get_from_user(User* user, char i, char* age_str) {
    switch (i) {
        case 'u':
            return strdup(user->username);
        case 'e':
            return strdup(user->email);
        case 'f':
            return strdup(user->first_name);
        case 'l':
            return strdup(user->last_name);
        case 'b':
            get_user_age(user->birth_date, age_str);
            return age_str;
        case 'c':
            return strdup(user->country);
        default:
            return NULL;
    }
}



