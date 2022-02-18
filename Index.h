
/* Tipo abstrato de dado Index */


/* Tipo do dado do programa exportado */



typedef struct reg Reg; /* Registro dentro da tabela */ 

typedef struct index Index; /* Indice remissivo */

/* Funcoes utilizadas */


/* Cria o indice remissivo como uma tabela hash a partir dos arquivos key_file (de palavras-chave) e text_file (texto) */

int index_createfrom(const char *key_file, const char *text_file, Index** idx);

/* Busca no indice a palavra-chave e devolve suas ocorrencias e o numero de ocorrencias */

int index_get(const Index *idx, const char *key, int **occurrences, int *num_occurrences);

/* Insere no indice uma nova palavra-chave e suas ocorrencias no texto ou atualiza as ocorrencias da mesma se ela ja existir no indice */

int index_put(Index *idx, const char *key);

/* Imprime o indice remissivo */

int index_print(const Index *idx);

/* Libera a memoria alocada para o indice remissivo */

int index_destroy(Index *idx);
