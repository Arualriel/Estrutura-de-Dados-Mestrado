/* Programa com funcoes para criar e manipular matrizes esparsas */

#include <stdio.h>     /* Biblioteca de entrada e saida */
#include <stdlib.h>     /* Biblioteca padrao do C que contem funcoes 
						 * para o gerenciamento de memoria, processos, 
						 * conversao de tipos, etc */
#include "Matrix.h"    /* TAD Matrix */

struct matrix{    /* conteudo de cada no da estrutura */
	int line;
	int column;
	float info;
	struct matrix* right;
	struct matrix* below;
};

typedef struct matrix Matrix;    /* tipo dos nos da estrutura */

int matrix_create(Matrix** m){    /* funcao que cria a matriz atraves dos dados passados por input pelo usuario */
	Matrix *newline, *newcolumn, *aux, *new, *node, *head;    /* ponteiros para criar e percorrer a estrutura */
	int lin, col, contl, contc, errado, erro, coluna, stop;    /* variaveis usadas como criterio de parada */
	float info;
	errado=0;
	erro=0;
	contl=0;
	stop=1;
	contc=0;
	*m=(Matrix*)malloc(sizeof(Matrix));    /* cria o no "cabeca" que mantem a estrutura */
	new=*m;
	aux=new;
	head=*m;
	head->line=-1;
	head->column=-1;
	head->below=aux;
	head->right=aux;
	head->info=0.0;
	scanf("%d",&lin);    /* leitura da dimensao da matriz */
	scanf("%d",&col);
	if(*m){
		do{    /* alocacao dos nos cabeca das linhas da matriz */
			*m=(Matrix*)malloc(sizeof(Matrix));
			newline=*m;
			newline->line=-1;
			newline->column=-1;
			newline->info=-1.0;
			newline->right=newline;
			newline->below=new;
			aux->below=newline;
			aux=newline;
			contl=contl+1;
		}while(contl<lin);
		aux=head;
		do{    /* alocacao dos nos cabeca das colunas da matriz */
			*m=(Matrix*)malloc(sizeof(Matrix));
			newcolumn=*m;
			newcolumn->line=-1;
			newcolumn->column=-1;
			newcolumn->info=-1.0;
			newcolumn->below=newcolumn;
			aux->right=newcolumn;
			newcolumn->right=new;
			aux=newcolumn;
			contc=contc+1;
		}while(contc<col);
		aux=head;
		contl=0;
		contc=0;
		while(stop!=0){    /* insercao dos dados passados pelo usuario na estrutura */
			contl=0;
			contc=0;
			erro=0;
			scanf("%d",&stop);
			if(stop!=0){     /* aloca o novo no */	
				scanf("%d",&coluna);
				scanf("%f",&info);
				if((coluna>col)||(stop>lin)) errado=1;
				if(info!=0.0){		
					*m=(Matrix*)malloc(sizeof(Matrix));
					node=*m;
					node->line=stop;
					node->column=coluna;
					node->info=info;		
					while(contl<node->line){    /* encontra a posicao que o novo no ira ocupar */
						aux=new;
						new=new->below;
						contl=contl+1;
					}
					while((node->column>new->column)&&(erro==0)){
						aux=new;
						new=new->right;
						contc=contc+1;
						if((contc>0)&&(new->column==-1)){
							erro=1;
						}
					}
					aux->right=node;    /* posiciona o novo no na linha */
					node->right=new;
					contl=0;
					contc=0;
					aux=head;
					new=head;
					while(contc<node->column){
						aux=new;
						new=new->right;
						contc=contc+1;
					}
					erro=0;
					while((node->line>new->line)&&(erro==0)){
						aux=new;
						new=new->below;
						contl=contl+1;
						if((contl>0)&&(new->line==-1)){
							erro=1;
						}
					}
					aux->below=node;    /* posiciona o no na coluna */
					node->below=new;
				}
			}
			aux=head;
			new=head;
		}	
		*m=head;    /* atualiza a matriz */
		if(errado==0){
			return 0;
		}else{
			return 1;
		}
	}else{
		return 1;
	}
}

int matrix_print(const Matrix* m){    /* funcao que exibe a matriz */
	if(m!=NULL){
		Matrix *aux, *new;    /* ponteiros para percorrer a matriz */
		int contl, contc, retorno, i, cont1, cont2, sinal, j;    /* criterios de parada */
		float zero;    /* variavel que ajudara a preencher a matriz com zeros */
		retorno=1;
		zero=0.0;
		contl=0;
		contc=0;
		new=m->right;
		while(new->info!=0.0){    /* conta o numero de coluna da matriz */
			aux=new;
			new=new->right;
			contc=contc+1;
		}
		new=m->below;
		while(new->info!=0.0){    /* conta o numero de linhas da matriz */
			aux=new;
			new=new->below;
			contl=contl+1;
		}
		aux=m->below;
		new=m->below;
		printf("Matriz: \n");
		printf("[");
		for(i=1;i<=contl;i++){    /* percorre a matriz e exibe os elementos diferentes dos nos cabeca */
			printf("[");
			sinal=1;
			for(j=1;j<=contc;j++){
				if(aux->right->column!=-1){
					aux=aux->right;
					if((sinal==1)&&(aux->column>1)){
						cont2=1;
						while(cont2<aux->column){
							printf(" %f ",zero);
							sinal=sinal+1;
							cont2=cont2+1;
						}
					}
					if(printf(" %f ",aux->info)) retorno=0;
					sinal=sinal+1;
					cont1=aux->column;
					while(cont1<(aux->right->column)-1){
						printf(" %f ",zero);
						sinal=sinal+1;
						cont1=cont1+1;
					}
				}else if((sinal<=contc)){
					printf(" %f ",zero);
					sinal=sinal+1;
				}
			}
			aux=new->below;
			new=aux;
			if((i==contl)&&(j==contc+1)){
				printf("]]\n");
			}else{
				printf("],\n");
			}
		}	
		if(retorno==0){ 
			return 0;
		}else{ 
			return 1;
		}
	}else{
		return 1;
	}	
}

int matrix_destroy(Matrix* m){    /* funcao que devolve a memoria utilizada para alocar os nos da matriz */
	if(m!=NULL){
		Matrix *aux1, *aux2, *new;    /* ponteiros para percorrer a matriz */
		int contc, contl1, contl2;    /* criterios de parada */
		while(m->below!=m){
			aux1=m;
			new=m->right;
			aux2=m;
			contc=1;
			contl1=0;
			contl2=0;
			while(new->right->info!=0.0){    /* conta as colunas e percorre-as para encontrar a ultima coluna */
				aux1=new;
				new=new->right;
				contc=contc+1;
			}
			aux1=new;
			while(new->below!=aux1){    /* conta as linhas e percorre-as para encontrar o ultimo elemento da matriz */
				aux2=new;
				new=new->below;
				contl1=contl1+1;
			}
			aux1=m;
			if(new->line!=-1){
				while(contl2!=new->line){
					aux1=aux1->below;
					contl2=contl2+1;
				}
			}
			while((aux1->right!=new)&&(contc!=1)){
				aux1=aux1->right;
			}
			if((new->line==-1)&&(contl1==0)){    /* libera o no encontrado */
				aux1->right=m;
				new->below=NULL;
				new->right=NULL;
				free(new);
				new=NULL;
			}else if((new->line==-1)&&(contc==1)){
				aux2->below=m;
				new->below=NULL;
				new->right=NULL;
				free(new);
				new=NULL;
			}else{
				aux1->right=new->right;
				aux2->below=new->below;
				new->below=NULL;
				new->right=NULL;
				free(new);
				new=NULL;
			}
		}
		aux1=m;
		aux2=m;
		if((m->right==m)&&(m->below==m)){    /* verifica se o no foi liberado */
			m->below=NULL;
			m->right=NULL;
			free(m);
			m=NULL;
			aux1=NULL;
			aux2=NULL;
		}	
	}
	if(m==NULL){
		return 0;
	}else{
		return 1;
	}
}

int matrix_transpose(const Matrix* m, Matrix** r){    /* funcao que transpoe uma matriz */
	if(m!=NULL){
		Matrix *newline, *newcolumn, *aux, *auxm, *new, *node, *head;    /* ponteiros para criar a matriz r e percorrer as matrizes m e r */
		int linT, colT, contl, contc, erro;    /* criterios de parada */
		erro=0;
		contl=0;
		contc=0;
		linT=0;
		colT=0;
		auxm=m->right;
		while(auxm->info!=0.0){    /* conta as linhas da matriz m */
			linT=linT+1;
			auxm=auxm->right;
		}
		auxm=m->below;
		while(auxm->info!=0.0){    /* conta as colunas da matriz m */
			colT=colT+1;
			auxm=auxm->below;
		}
		*r=(Matrix*)malloc(sizeof(Matrix));    /* aloca o no "cabeca" da matriz r */
		new=*r;
		aux=new;
		head=*r;
		head->line=-1;
		head->column=-1;
		head->below=aux;
		head->right=aux;
		head->info=0.0;
		if(*r){
			do{    /* aloca os nos cabeca das linhas de r */
				*r=(Matrix*)malloc(sizeof(Matrix));
				newline=*r;
				newline->line=-1;
				newline->column=-1;
				newline->info=-1.0;
				newline->right=newline;
				newline->below=new;
				aux->below=newline;
				aux=newline;
				contl=contl+1;
			}while(contl<linT);
			aux=head;
			do{    /* aloca os nos cabeca das colunas de r */
				*r=(Matrix*)malloc(sizeof(Matrix));
				newcolumn=*r;
				newcolumn->line=-1;
				newcolumn->column=-1;
				newcolumn->info=-1.0;
				newcolumn->below=newcolumn;
				aux->right=newcolumn;
				newcolumn->right=new;
				aux=newcolumn;
				contc=contc+1;
			}while(contc<colT);
			aux=head;
			new=head;
			auxm=m->below;
			while(auxm->info!=m->info){    /* percorre a matriz m */
				while(auxm->right->line!=-1){
					contl=0;
					contc=0;
					erro=0;
					auxm=auxm->right;
					if(auxm->line!=-1){
						*r=(Matrix*)malloc(sizeof(Matrix));    /* aloca o novo no na matriz r */
						node=*r;
						node->line=auxm->column;
						node->column=auxm->line;
						node->info=auxm->info;				
						while(contl<node->line){    /* procura a posicao que o novo no ocupara */
							aux=new;
							new=new->below;
							contl=contl+1;
						}
						while((node->column>new->column)&&(erro==0)){
							aux=new;
							new=new->right;
							contc=contc+1;
							if((contc>0)&&(new->column==-1)){
								erro=1;
							}
						}
						aux->right=node;    /* posiciona o novo no na linha */
						node->right=new;
						contl=0;
						contc=0;
						aux=head;
						new=head;
						while(contc<node->column){
							aux=new;
							new=new->right;
							contc=contc+1;
						}
						erro=0;
						while((node->line>new->line)&&(erro==0)){
							aux=new;
							new=new->below;
							contl=contl+1;
							if((contl>0)&&(new->line==-1)){
								erro=1;
							}
						}
						aux->below=node;    /* posiciona o novo no na coluna */
						node->below=new;
					}
					aux=head;
					new=head;
				}
				auxm=auxm->right;
				auxm=auxm->below;	
			}		
			*r=head;    /* atualiza a matriz */
			return 0;
		}else{
			return 1;
		}
	}else{
		return 1;
	}
}

int matrix_getelem(const Matrix* m, int x, int y, float* elem){    /* funcao que encontra um elemento na matriz */
	int contl, contc;    /* criterios de parada */
	Matrix  *new;    /* ponteiro que percorrera a matriz */
	contc=0;
	contl=0;
	new=m->below;
	while(new!=m){    /* conta o numero de linhas */
		new=new->below;
		contl=contl+1;
	}
	new=m->right;
	while(new!=m){    /* conta o numero de colunas */
		new=new->right;
		contc=contc+1;
	}
	if(((m!=NULL)&&((x>0)&&(y>0)))&&((y<=contc)&&(x<=contl))){
		contl=1;
		contc=0;
		new=m->below;
		while(contl<x){    /* conta as linhas ate a posicao x (se existir) da matriz e as percorre */
			new=new->below;
			contl=contl+1;	
		}
		while((new->column<y)&&(contc<y)){    /* conta as colunas ate a posicao y (se existir) da matriz e as percorre */
			new=new->right;
			contc=contc+1;
		}
		if((new->line==x)&&(new->column==y)){    /* verifica se o elemento existe na matriz e o retorna */
			*elem=new->info;
			return 0;
		}else{
			*elem=0.0;
			return 0;
		}
	}else{
		return 1;
	}
}

int matrix_setelem(Matrix* m, int x, int y, float elem){    /* funcao que atribui um valor a um no da matriz */
	int contl, contc;    /* criterios de parada */
	Matrix *aux1, *aux2, *new, *node;    /* ponteiros que percorrerao a matriz */
	contc=0;
	contl=0;
	new=m->below;
	while(new!=m){    /* conta o numero de linhas */
		new=new->below;
		contl=contl+1;
	}
	new=m->right;
	while(new!=m){    /* conta o numero de colunas */
		new=new->right;
		contc=contc+1;
	}
	if((m!=NULL)&&(((x>0)&&(y>0))&&((x<=contl)&&(y<=contc)))){
		contl=1;
		contc=0;
		aux1=m->below;
		aux2=m->below;
		new=m->below;
		while(contl<x){    /* conta e percorre as linhas da matriz */
			aux1=new;
			new=new->below;
			contl=contl+1;
		}
		while((new->column<y)&&(contc<y)){    /* conta e percorre as colunas da matriz */
			aux2=new;
			new=new->right;
			contc=contc+1;
		}
		contc=1;
		if((new->line==x)&&(new->column==y)){    /* verifica se o elemento existe na matriz a atribui o valor */
			if(elem!=0.0){
				new->info=elem;
			}else{
				aux2->right=new->right;
				aux1=m->right;
				while(contc<new->column){
					aux1=aux1->right;
					contc=contc+1;
				}
				while(aux1->below!=new){
					aux1=aux1->below;
				}
				aux1->below=new->below;
				new->right=NULL;
				new->below=NULL;
				free(new);
				new=NULL;
			}
			return 0;
		}else{    /* aloca o no se ele nao existir */
			if(contl==1){
				aux2=aux1;
			}else{
				aux2=aux1->below;
			}
			new=aux2;
			contc=0;
			contl=0;
			if(elem!=0.0){		
				node=(Matrix*)malloc(sizeof(Matrix));
				node->line=x;
				node->column=y;
				node->info=elem;		
				while((contc<y)&&(new->column<y)){     /*encontra a posicao que o novo no ira ocupar */
					aux2=new;
					new=new->right;
					contc=contc+1;
				}
				node->right=aux2->right;    /* posiciona o novo no na linha */
				aux2->right=node;
				new=m->right;
				contc=1;
				while(contc<y){
					aux2=new;
					new=new->right;
					contc=contc+1;
				}
				while((contl<x)&&(new->below->line!=-1)){
					new=new->below;
					contl=contl+1;
				}
				node->below=new->below;    /* posiciona o novo no na coluna */
				new->below=node;
			}
			return 0;
		}	
	}else{
		return 1;
	}
}
int matrix_add(const Matrix* m, const Matrix* n, Matrix** r){    /* funcao que soma duas matrizes */
	if((m!=NULL)&&(n!=NULL)){
		Matrix *newline, *newcolumn, *aux, *auxn, *auxm, *new, *node, *head;    /* ponteiros para criar a matriz r e percorrer as matrizes r, m e n */
		int linm, colm, linn, coln, contl, contc, erro;     /* criterios de parada */
		erro=0;
		contl=0;
		contc=0;
		linn=0;
		coln=0;	
		linm=0;
		colm=0;
		auxn=n->right;
		auxm=m->right;
		while(auxm->info!=0.0){    /* conta o numero de colunas de m */
			colm=colm+1;
			auxm=auxm->right;
		}
		auxm=m->below;
		while(auxm->info!=0.0){    /* conta o numero de linhas de m */
			linm=linm+1;
			auxm=auxm->below;
		}	
		while(auxn->info!=0.0){    /* conta o numero de colunas de n */
			coln=coln+1;
			auxn=auxn->right;
		}
		auxn=n->below;
		while(auxn->info!=0.0){    /* conta o numero de linhas de n */
			linn=linn+1;
			auxn=auxn->below;
		}
		if((linm==linn)&&(colm==coln)){    /* verifica se as matrizes possuem as mesmas dimensoes */
			*r=(Matrix*)malloc(sizeof(Matrix));    /* aloca o no cabeca de r */
			new=*r;
			aux=new;
			head=*r;
			head->line=-1;
			head->column=-1;
			head->below=aux;
			head->right=aux;
			head->info=0.0;
			if(*r){
				do{    /* aloca os nos cabeca das linhas de r */
					*r=(Matrix*)malloc(sizeof(Matrix));
					newline=*r;
					newline->line=-1;
					newline->column=-1;
					newline->info=-1.0;
					newline->right=newline;
					newline->below=new;
					aux->below=newline;
					aux=newline;
					contl=contl+1;
				}while(contl<linm);
				aux=head;
				do{    /* aloca os nos cabeca das colunas */
					*r=(Matrix*)malloc(sizeof(Matrix));
					newcolumn=*r;
					newcolumn->line=-1;
					newcolumn->column=-1;
					newcolumn->info=-1.0;
					newcolumn->below=newcolumn;
					aux->right=newcolumn;
					newcolumn->right=new;
					aux=newcolumn;
					contc=contc+1;
				}while(contc<colm);
				aux=head;
				new=head;
				auxm=m->below;
				auxn=n->below;
				while(auxm->info!=m->info){    /* percorre a matriz m */
					while(auxm->right->line!=-1){
						contl=0;
						contc=0;
						erro=0;
						auxm=auxm->right;
						if(auxm->line!=-1){
							*r=(Matrix*)malloc(sizeof(Matrix));    /* aloca o novo no de r com o valor do no de m */
							node=*r;
							node->line=auxm->line;
							node->column=auxm->column;
							node->info=auxm->info;				
							while(contl<node->line){    /* encontra em r a posicao na qual o novo no deve ficar */
								aux=new;
								new=new->below;
								contl=contl+1;
							}
							while((node->column>new->column)&&(erro==0)){
								aux=new;
								new=new->right;
								contc=contc+1;
								if((contc>0)&&(new->column==-1)){
									erro=1;
								}
							}
							aux->right=node;    /* posiciona o no na linha de r */
							node->right=new;
							contl=0;
							contc=0;
							aux=head;
							new=head;
							while(contc<node->column){
								aux=new;
								new=new->right;
								contc=contc+1;
							}
							erro=0;
							while((node->line>new->line)&&(erro==0)){
								aux=new;
								new=new->below;
								contl=contl+1;
								if((contl>0)&&(new->line==-1)){
									erro=1;
								}
							}
							aux->below=node;    /* posiciona o no na coluna de r */
							node->below=new;
						}
						aux=head;
						new=head;
					}
					auxm=auxm->right;
					auxm=auxm->below;	
				}
				while(auxn->info!=n->info){    /* percorre a matriz n */
					while(auxn->right->line!=-1){
						contl=0;
						contc=0;
						erro=0;
						auxn=auxn->right;
						if(auxn->line!=-1){
							aux=head;
							new=head;
							while(contl<auxn->line){    /* encontra o elemento a ser somado com o elemento de m */
								aux=new;
								new=new->below;
								contl=contl+1;
							}
							while((contc<auxn->column)&&(new->column<auxn->column)){
								aux=new;
								new=new->right;
								contc=contc+1;
								
							}
							if((contc==new->column)||(new->column==auxn->column)){
								if((auxn->info+new->info)!=0.0){
									new->info=auxn->info+new->info;	   /* soma os elementos de m e n e armazena no novo no de r */
								}else{
									aux->right=new->right;
									aux=head;
									contc=0;
									while(contc<new->column){
										aux=aux->right;
										contc=contc+1;
									}
									while(aux->below!=new){
										aux=aux->below;
									}
									aux->below=new->below;
									new->right=NULL;
									new->below=NULL;
									free(new);
									new=NULL;
								}
							}else{    /* aloca o elemento de n em r se nao existir elemento correspondente em m */
								*r=(Matrix*)malloc(sizeof(Matrix));
								node=*r;
								node->line=auxn->line;
								node->column=auxn->column;
								node->info=auxn->info;
								contc=0;
								while((node->column>new->column)&&(erro==0)){    /* encontra a posicao que o novo no deve ocupar */
									aux=new;
									new=new->right;
									contc=contc+1;
									if((contc>0)&&(new->column==-1)){
										erro=1;
									}
								}
								aux->right=node;    /* posiciona o no na linha de r */
								node->right=new;
								contl=0;
								contc=0;
								aux=head;
								new=head;
								while(contc<node->column){
									aux=new;
									new=new->right;
									contc=contc+1;
								}
								erro=0;
								while((node->line>new->line)&&(erro==0)){
									aux=new;
									new=new->below;
									contl=contl+1;
									if((contl>0)&&(new->line==-1)){
										erro=1;
									}
								}
								aux->below=node;    /* posiciona o no na coluna de r */
								node->below=new;			
							}
						}
						aux=head;
						new=head;
					}
					auxn=auxn->right;
					auxn=auxn->below;			
				}
				*r=head;    /* atualiza a matriz r */
			}
			return 0;
		}else{
			*r=NULL;
			return 1;
		}
	}else{
		return 1;
	}
}
int matrix_multiply(const Matrix* m, const Matrix* n, Matrix** r){    /* funcao que multiplica as matrizes m e n e armazena o resultado na matriz r */
	if((m!=NULL)&&(n!=NULL)){
		Matrix *newline, *newcolumn, *aux, *auxn, *auxm, *new, *node, *head;    /* ponteiros para criar a matriz r e percorrer as matrizes m, n e r */
		int i, j, k, linm, colm, conta, linn, coln, contl, contc, erro, sinal1, sinal2;     /* criterios de parada */
		float elem1, elem2, mult, soma;    /* variaveis que armazenam os elementos a serem multiplicados, a mutiplicacao e a soma */
		conta=0;
		erro=0;
		contl=0;
		contc=0;
		linn=0;
		coln=0;	
		linm=0;
		colm=0;
		auxn=n->below;
		auxm=m->below;
		while(auxm->info!=0.0){    /* conta as linhas de m */
			linm=linm+1;
			auxm=auxm->below;
		}
		auxm=m->right;
		while(auxm->info!=0.0){    /* conta as colunas de m */
			colm=colm+1;
			auxm=auxm->right;
		}	
		while(auxn->info!=0.0){    /* conta as linhas de n */
			linn=linn+1;
			auxn=auxn->below;
		}
		auxn=n->right;
		while(auxn->info!=0.0){    /* conta as colunas de n */
			coln=coln+1;
			auxn=auxn->right;
		}
		if(colm==linn){    /* verifica se a multiplicacao pode ser efetuada */
			*r=(Matrix*)malloc(sizeof(Matrix));    /* aloca o no cabeca de r */
			new=*r;
			aux=new;
			head=*r;
			head->line=-1;
			head->column=-1;
			head->below=aux;
			head->right=aux;
			head->info=0.0;
			if(*r){
				do{    /* aloca os nos cabeca das linhas de r */
					*r=(Matrix*)malloc(sizeof(Matrix));
					newline=*r;
					newline->line=-1;
					newline->column=-1;
					newline->info=-1.0;
					newline->right=newline;
					newline->below=new;
					aux->below=newline;
					aux=newline;
					contl=contl+1;
				}while(contl<linm);
				aux=head;
				do{    /* aloca os nos cabeca das colunas de r */
					*r=(Matrix*)malloc(sizeof(Matrix));
					newcolumn=*r;
					newcolumn->line=-1;
					newcolumn->column=-1;
					newcolumn->info=-1.0;
					newcolumn->below=newcolumn;
					aux->right=newcolumn;
					newcolumn->right=new;
					aux=newcolumn;
					contc=contc+1;
				}while(contc<coln);
				aux=head;
				new=head;
			}
			auxm=m->below;
			auxn=n->right;
			aux=head->right;
			new=head->below;
			for(i=1;i<=linm;i++){    /* percorre a matriz r */
				for(j=1;j<=coln;j++){
					mult=1.0;
					soma=0.0;
					for(k=1;k<=colm;k++){
						sinal1=matrix_getelem(m,i,k,&elem1);
						sinal2=matrix_getelem(n,k,j,&elem2);
						if((sinal1==0)&&(sinal2==0)){    /* faz a multiplicacao dos elementos de m e n */
							mult=elem1*elem2;
							soma=mult+soma;
						}
					}
					if(soma!=0.0){
						conta=0;
						erro=0;
						while((aux->below->line<i)&&(erro==0)){
							aux=aux->below;
							conta=conta+1;
							if((conta>0)&&(aux->below->line==-1)){
								erro=1;
							}
						}
						*r=(Matrix*)malloc(sizeof(Matrix));    /* aloca o no r(i,j) na matriz r */
						node=*r;
						node->line=i;
						node->column=j;
						node->info=soma;
						node->right=new->right;    /* posiciona o no na linha */
						node->below=aux->below;    /* posiciona o no na coluna */
						aux->below=node;
						new->right=node;
						new=node;
						aux=node->below;
						
					}
					aux=aux->right;
				}
				new=new->right;
				new=new->below;
				aux=aux->right;
			}
			*r=head;    /* atualiza a matriz r */
			return 0;
		}else{
			*r=NULL;
			return 1;
		}
	}else{
		return 1;
	}
}
