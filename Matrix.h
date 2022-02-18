
/* Tipo abstrato de dado Matrix */


/* Tipo do dado do programa exportado */

typedef struct matrix Matrix;


/* Funcoes utilizadas */


/* Aloca e retorna a matriz criada */

int matrix_create(Matrix** m);

/* Libera a memoria alocada para matriz */

int matrix_destroy(Matrix* m);

/* Imprime a matriz */

int matrix_print(const Matrix* m);

/* Retorna o resultado da soma das matrizes dadas */

int matrix_add(const Matrix* m, const Matrix* n, Matrix** r);

/* Retorna o resultado da multiplicacao das matrizes dadas */

int matrix_multiply(const Matrix* m, const Matrix* n, Matrix** r);

/* Retorna a matriz transposta da matriz dada */

int matrix_transpose(const Matrix* m, Matrix** r);

/* Retorna o elemento da linha x e coluna y da matriz */

int matrix_getelem(const Matrix* m, int x, int y, float* elem);

/* Atribui ao elemento da linha x e coluna y da matriz o valor de elem */

int matrix_setelem(Matrix* m, int x, int y, float elem);
