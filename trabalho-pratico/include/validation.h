#ifndef VALIDATION_H
#define VALIDATION_H
#include <glib.h>


/**
 * @brief Verifica se uma string é uma lista válida.
 * 
 * A lista é válida se começa com '[' e termina com ']'.
 * 
 * @param list A string que representa a lista.
 * @return 1 se for válida, 0 caso contrário.
 */
int valid_type_list(char* list);


/**
 * @brief Verifica a validade de um domínio.
 * 
 * Um domínio válido deve conter apenas letras minúsculas, 
 * um ponto no meio e um sufixo de 2 a 3 caracteres.
 * 
 * @param domain A string que representa o domínio.
 * @return 1 se for válido, 0 caso contrário.
 */
int valid_domain (const char* domain);


/**
 * @brief Verifica se um e-mail é válido.
 * 
 * O e-mail é válido se contém exatamente um '@', 
 * caracteres válidos no nome do usuário e um domínio válido.
 * 
 * @param email A string que representa o e-mail completo.
 * @return 1 se for válido, 0 caso contrário.
 */
int valid_email (char* email);


/**
 * @brief Verifica se uma duração no formato HH:MM:SS é válida.
 * 
 * @param duration A string que representa a duração.
 * @return 1 se for válida, 0 caso contrário.
 */
int valid_duration(char* duration);


/**
 * @brief Verifica se uma data está em formato válido e se não é uma data passada.
 * 
 * A data deve estar no formato YYYY/MM/DD, respeitando os limites.
 * 
 * @param date A string que representa a data.
 * @return 1 se for válida, 0 caso contrário.
 */
int valid_date (char* date);


/**
 * @brief Verifica se uma data está no passado.
 * 
 * A data deve ser anterior a 2024/09/09.
 * 
 * @param date A string que representa a data.
 * @return 1 se for válida, 0 caso contrário.
 */
int valid_past_date (char* date);


/**
 * @brief Verifica se um tipo de subscrição é válido.
 * 
 * Tipos válidos são "normal" e "premium".
 * 
 * @param subT A string que representa o tipo de subscrição.
 * @return 1 se for válido, 0 caso contrário.
 */
int valid_subs_type (char* subT);

/** 
 * @brief Verifica se o tipo de plataforma é válido.
 * 
 * Tipos válidos são variações entre maiúsculas e minúsculas de "desktop" e "mobile".
 * 
 * @param plataform String que representa o tipo de plataforma.
 * @return 1 se for válida, 0 caso contrário.
*/
int validPlataform(char* plataform);

/**
 * @brief Liberta memória alocada para tokens.
 * 
 * @param tokens Array de strings a ser libertado.
 */
void free_tokens(char** tokens);


/**
 * @brief Verifica se uma lista de IDs de artistas é válida.
 * 
 * A lista é válida se todos os IDs estão presentes na tabela com os artistas válidos.
 * 
 * @param artist_list A string com a lista de IDs de artistas.
 * @return 1 se for válida, 0 caso contrário.
 */
int valid_artist(char* artist_list);


/**
 * @brief Verifica se uma lista de músicas é válida.
 * 
 * A lista é válida se todos os IDs estão presentes na tabela com as músicas válidas.
 * 
 * @param songs_list A string com a lista de IDs de músicas.
 * @return 1 se for válida, 0 caso contrário.
 */
int valid_songs (char* songs_list);


/**
 * @brief Valida sintaticamente uma linha de um CSV.
 * 
 * Faz uso das funções acima, de modo a verificar a validade de uma linha.
 * Nos casos 'U' e 'S' verifica ainda se existem os IDs nas respetivas tabelas.
 * 
 * @param line Array de strings representando os campos da linha.
 * @param type Tipo da linha ('U', 'S', ou 'A').
 * @return 1 se for válida, 0 caso contrário.
 */
int syntactic_validation(char** line, char type);


/**
 * @brief Valida logicamente uma linha de um CSV.
 * 
 * Faz uso das funções acima, de modo a verificar a validade de uma linha.
 * Nos casos 'U' e 'S' verifica ainda se existem os IDs nas respetivas tabelas.
 * 
 * @param line Array de strings representando os campos da linha.
 * @param type Tipo da linha ('U', 'S', ou 'A').
 * @return 1 se for válida, 0 caso contrário.
 */
int logic_validation (char** line, char type);



#endif