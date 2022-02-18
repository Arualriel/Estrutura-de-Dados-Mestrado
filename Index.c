/* Programa com funcoes para criar e manipular indices remissivos */
#include <stdio.h>		/* Biblioteca de entrada e saida */
#include <string.h>		/* Biblioteca utilizada para manipular cadeias de caracteres em C */
#include <stdlib.h>		/* Biblioteca padrao do C que contem funcoes 
						 * para o gerenciamento de memoria, processos, 
						 * conversao de tipos, etc */
#include <time.h>		/* Biblioteca utilizada para manipular datas e horarios */
#include "Index.h"		/* TAD Index */
#include <ctype.h>		/* Biblioteca utilizada para manipular caracteres */


#define M 193		/* tamanho da tabela hash */

struct reg{			/* conteudo de cada no apontado pelos nos da tabela hash */
	char word[17];
	int occur[100];
	struct reg* next;
};

struct index{		/* conteudo do indice remissivo */
	const char *text;
	Reg *tab[M];
	
};

static int hash(const char *key, int *k){		/* funcao que fornece a posicao da tabela que apontara para o proximo no alocado */
	int tam, soma=0;
	tam=strlen(key);
	int peso[tam];
	for(int i=0; i<tam; i++){		/* atribui pesos aleatorios a cada caractere da palavra chave */
		peso[i]=rand()%M;
		soma=soma+key[i]*peso[i];
	}
	*k=soma%M;
	return *k;
}

int index_createfrom(const char *key_file, const char *text_file, Index** idx){		/* funcao que cria o indice remissivo */
	Index *vec;		/* ponteiro para o indice */
	Reg *new, *aux;		/* ponteiros utilizados para percorrer a tabela e os nos apontados por ela */
	char word1[17], test2[100], test1[17], word2[100], *pos, *sub;		/* variaveis utilizadas para buscar a palavra no texto */
	int i, signal, h, linha, k, cont;		/* criterios de parada */
	FILE *key, *text;		/* ponteiros para o arquivo do texto e para o arquivo de palavras-chave */
	sub=NULL;
	cont=0;
	pos=NULL;
	srand(time(NULL));		/* inicia o contador de tempo para os pesos aleatorios da funcao hash */
	key=fopen(key_file,"rt");		/* abre o arquivo de palavras-chave */
	text=fopen(text_file,"rt");		/* abre o arquivo do texto */
	*idx=(Index*)malloc(sizeof(Index));		/* aloca o no que mantem o indice remissivo */
	(*idx)->text=text_file;
	vec=*idx;
	for(i=0; i<M; i++){ 
		(*idx)->tab[i]=NULL;		/* inicializa os nos da tabela */
	}
	test1[0]=' ';
	if(*idx){
		while(!feof(key)){		/* percorre o arquivo de palavras-chave */
			fgets(word1,17,key);		/* le a palavra-chave */
			if(strcmp(test1,word1)!=0){		/* garante que uma palavra nao sera alocada duas vezes seguidas */
				if(word1[strlen(word1)-1]=='\n') word1[strlen(word1)-1]='\0';		/* finaliza a cadeia de caracteres lida com '\0' */
				for(i=0; i<strlen(word1);i++){
					if(isupper(word1[i])) word1[i]=tolower(word1[i]);		/* converte os caracteres lidos para minusculo */
				}
				strcpy(test1,word1);
				h=hash(word1,&h);		/* obtem a posicao do no da tabela que apontara para o no da nova palavra-chave */
				aux=((*idx)->tab)[h];
				if(aux==NULL){		/* a posicao h da tabela apontara para no da nova palavra */
					((*idx)->tab)[h]=(Reg*)malloc(sizeof(Reg));		/* aloca o no da nova palavra */
					new=((*idx)->tab)[h];
					for(i=0;i<17;i++) (new->word)[i]=word1[i];
					new->next=NULL;
					((*idx)->tab)[h]=new;
				}else{		/* busca na posicao h o no que ira apontar para o no da nova palavra */
					new=aux;
					while(new->next!=NULL){
						new=new->next;
					}
					((*idx)->tab)[h]=(Reg*)malloc(sizeof(Reg));		/* aloca o no da nova palavra */
					new->next=((*idx)->tab)[h];
					new->next->next=NULL;
					for(i=0;i<17;i++) (new->next->word)[i]=word1[i];
					new=new->next;
					((*idx)->tab)[h]=aux;
				}
				linha=1;
				k=0;
				for(i=0;i<100;i++) (new->occur)[i]=0;		/* inicializa o vetor de ocorrencias da palavra-chave */
				rewind(text);		/* volta ao inicio do arquivo do texto */
				test2[0]='_';
				while(!feof(text)){		/* percorre o arquivo do texto */
					fgets(word2,100,text);		/* le a linha do arquivo de texto */
					if(strcmp(test2,word2)!=0){		/* evita que uma linha seja lida duas vezes consecutivas */
						if(word2[strlen(word2)-1]=='\n') word2[strlen(word2)-1]='\0';		/* finaliza a linha lida com '\0' */
						for(i=0; i<strlen(word2);i++){
							if(isupper(word2[i])) word2[i]=tolower(word2[i]);		/* converte os caracteres da linha lida para minusculo */
						}
						strcpy(test2,word2);
						signal=0;
						pos=strstr(word2, word1);		/* localiza a palavra-chave na linha do texto se ela existir no mesmo */
						while(pos!=NULL){
							sub=word2;
							cont=0;
							if(sub!=pos){
								while((sub+1!=pos)&&(pos!=NULL)){		/* localiza a posicao do inicio da palavra na linha */
									sub=sub+1;
									cont=cont+1;
								}
							}
							if(pos!=NULL){		/* atribui a posicao k do vetor de ocorrencias a linha em que a palavra esta */
								if((cont==0)&&(sub==pos)){
									signal=1;
								}
								if((((ispunct(word2[cont]))||(word2[cont]==' '))||(cont==0))&&((ispunct(word2[cont+strlen(word1)+1]))
									||((word2[cont+strlen(word1)+1]==' ')||(word2[cont+strlen(word1)+1]=='\0')))){
									signal=1;
								}
							}
							sub=sub+2;
							pos=strstr(sub,word1);
						}
						pos=NULL;
						sub=NULL;
						if(signal==1){
							(new->occur)[k]=linha;
							k=k+1;
						}
						linha=linha+1;
					}
				}
				strcpy(test1,word1);
			}
		}
		*idx=vec;		/* atualiza o indice */
		fclose(key);		/* fecha o arquivo de palavras-chave */
		fclose(text);		/* fecha o arquivo do texto */
		return 0;
	}else{
		fclose(key);		/* fecha o arquivo de palavras-chave */
		fclose(text);		/* fecha o arquivo do texto */
		return 1;
	}
}

int index_print(const Index *idx){		/* funcao que exibe o indice remissivo em ordem alfabetica */
	if(idx!=NULL){
		Reg *new,*node,*aux,*head, *aux1;		/* ponteiros utilizados para percorrer os itens da tabela e criar uma 
												 * lista que exibira as palavras em ordem alfabetica */
		int i, k, cont, total;		/* criterios de parada */
		total=0;
		head=(Reg*)malloc(sizeof(Reg));		/* aloca o primeiro no da lista */
		node=head;
		aux=node;
		for(i=0;i<M;i++){		/* cria a lista a ser ordenada */
			if(idx->tab[i]!=NULL){
				new=idx->tab[i];
				while(new!=NULL){
					if(node==head){		/* copia os dados do no corrente da tabela para o no da lista e o posiciona na mesma */
						strcpy(node->word,new->word);
						for(int k=0; k<100; k++) node->occur[k]=new->occur[k];
						node->next=NULL;
						aux=node;
						head=node;
						total=total+1;
						node=NULL;
					}else{
						total=total+1;
						node=(Reg*)malloc(sizeof(Reg));
						strcpy(node->word,new->word);
						for(k=0; k<100; k++) node->occur[k]=new->occur[k];
						node->next=NULL;
						aux->next=node;
						aux=node;
					}
					new=new->next;
				}
			}
		}
		node=head;
		aux=head;
		new=head;
		aux1=head;
		cont=0;
		while(cont<total){		/* ordena os nos da lista para exibi-los em ordem alfabetica */
			aux=node;
			new=node;
			cont=cont+1;
			while(new!=NULL){
				aux1=aux;
				aux=new;
				new=new->next;
				if(new!=NULL){
					if(strcmp(new->word,aux->word)<0){		/* reposicionando o no de acordo com a ordem */
						if(aux==head){
							head=new;
							node=head;
							aux1=head;
						}else{
							aux1->next=new;
						}
						aux->next=new->next;
						new->next=aux;
						aux=new;
						new=new->next;
					}
				}
			}
		}
		new=head;
		printf("\nIndice:\n");
		while(new!=NULL){		/* exibe a lista ordenada (palavras e vetor de ocorrencias) */
			if(new!=NULL){
				printf("\n%s:",new->word);
				for(i=0; i<100; i++){ 
					if(new->occur[i]!=0){
						printf(" %d",new->occur[i]);
					}
				}
			}
			new=new->next;
		}
		printf("\n\n");
		new=head;
		aux=head;
		while(new->next!=NULL){		/* libera a memoria utilizada para construir a lista */
			aux=new;
			new=new->next;
			if(new->next==NULL){
				free(new);
				aux->next=NULL;
				new=head;
			}
		}
		if(head->next==NULL){
			free(head);
			head=NULL;
			new=NULL;
			aux=NULL;
			aux1=NULL;
			new=NULL;
			return 0;
		}else{
			return 1;
		}
	}else{
		return 1;
	}
}

int index_destroy(Index *idx){		/* funcao que libera a memoria utilizada para construir o indice remissivo */
	if(idx!=NULL){
		Reg *aux, *new, *node;		/* ponteiros utilizados para percorrer os nos apontados pelos nos da tabela */
		Index *vec;		/* ponteiro para o indice */
		int i, cont, cont2;		/* criterios de parada */
		cont=0;
		vec=idx;
		cont2=0;
		for(i=0;i<M;i++){ 		/* conta as posicoes nao nulas da tabela */
			if(vec->tab[i]!=NULL) cont2=cont2+1;
		}
		aux=vec->tab[0];
		for(i=0;i<M;i++){		/* percorre a tabela e libera a memoria alocada para os nos das palavras-chave */
			aux=vec->tab[i];
			if(aux!=NULL){
				while(node!=aux){
					new=aux;
					node=new;
					while(new->next!=NULL){
						node=new;
						new=new->next;
					}
					node->next=NULL;
					free(new);		/* libera a memoria alocada para o no */
				}
				vec->tab[i]=NULL;
				cont=cont+1;		/* conta quantas posicoes da tabela estao sendo liberadas */
			}
		}
		idx=vec;
		if((cont==cont2)&&(vec->tab[M-1]==NULL)){		/* verifica se os elementos da tabela estao todos nulos */
			free(idx);		/* libera a memoria alocada para o indice */
			idx=NULL;
			vec=NULL;
			aux=NULL;
			new=NULL;
			node=NULL;
			return 0;
		}else{
			return 1;
		}
	}else{
		return 1;
	}
	
}

int index_get(const Index *idx, const char *key, int **occurrences, int *num_occurrences){		/* funcao que busca uma palavra no indice e retorna 
																								 *o vetor de ocorrencias e o numero de ocorrencias */
	if(idx!=NULL){
		const Index *vec;		/* ponteiro para o indice */
		Reg *new;		/* ponteiro utilizado para percorrer os nos apontados pelos nos da tabela */
		const char *word;		/* variavel utilizada para armazenar a palavra a ser buscada */
		int i, j, tam, cont, fo, found, occ[100];		/* criterios de parada e vetor de ocorrencias */
		word=key;
		vec=idx;
		cont=0;
		found=0;
		for(i=0; i<M; i++){		/* percorre a tabela */
			new=vec->tab[i];
			if(new!=NULL){
				while(new!=NULL){		/* busca a palavra */
					if(new!=NULL){
						fo=0;
						tam=strlen(word);
						for(j=0;j<tam;j++){
							if((new->word)[j]==tolower(word[j])) fo=fo+1;		/* converte os caracteres da palavra lida para minusculo 
																				 * e verifica se a mesma ja existe no indice */
						}
						if(fo==tam){		/* verifica se a palavra foi encontrada */
							found=1;
							for(j=0; j<100; j++){
								if((new->occur)[j]!=0){		/* copia os elementos do vetor de ocorrencias para o vetor a ser retornado */
									occ[j]=new->occur[j];
									*occurrences=&occ[j];
									*occurrences=*occurrences+1;
									cont=cont+1;		/* conta o numero de ocorrencias */
								}
							}
							*occurrences=*occurrences-cont;
							*num_occurrences=cont;		/* atribui o numero de ocorrencias a variavel a ser retornada */
						}
					}
					new=new->next;
				}
			}
		}
		if(found!=0){
			return 0;
		}else{
			return 1;
		}
		
	}else{
		return 1;
	}
}

int index_put(Index *idx, const char *key){		/* funcao que insere no indice uma nova palavra chave ou atualiza 
												 * suas ocorrencias se a mesma ja existir no indice */
	if(idx!=NULL){
		FILE *text;		/* ponteiro para o arquivo do texto */
		Reg *new, *aux;		/* ponteiros utilizados para percorrer os nos apontados pelos nos da tabela */
		const char *word1;		/* variavel utilizada para armazanenar a palavra a ser buscada / inserida */
		char *pos, *sub, test[100], word2[100];		/* variaveis utilizadas para buscar a palavra no texto */
		int i, signal, ind, h, k, j, tam, linha, cont, fo,found;		/* criterios de parada */
		word1=key;
		text=fopen(idx->text,"rt");		/* abre o arquivo do texto */
		found=0;
		ind=0;
		cont=0;
		for(i=0; i<M; i++){		/* percorre a tabela */
			new=idx->tab[i];
			if(new!=NULL){
				while(new!=NULL){			/* busca a palavra */
					if(new!=NULL){
						fo=0;
						tam=strlen(word1);
						for(j=0;j<tam;j++){
							if((new->word)[j]==tolower(word1[j])) fo=fo+1;		/* converte os caracteres da palavra a ser buscada para minusculo 
																				 * e verifica se a palavra existe no indice */
						}
						if(fo==tam){		/* verifica se a palavra foi encontrada */
							found=1;
							ind=i;		/* guarda a posicao da tabela que aponta para onde a palavra esta */
						}
					}
					new=new->next;
				}
			}
		}
		
		if(found==0){
			h=hash(key,&h);		/* obtem a posicao do no da tabela que apontara 
								 * para onde o no da nova palavra sera alocado, caso ela nao exista no indice */
			new=(idx->tab)[h];
			aux=new;
			if((idx->tab)[h]==NULL){		/* o no da posicao h da tabela apontara para o novo no a ser alocado */
				(idx->tab)[h]=(Reg*)malloc(sizeof(Reg));		/* aloca o no da nova palavra */
				new=(idx->tab)[h];
				for(i=0;i<17;i++) (new->word)[i]=tolower(word1[i]);
				new->next=NULL;
				(idx->tab)[h]=new;
			}else{		/* busca na posicao h da tabela o no que ira apontar para o novo no */
				while(new->next!=NULL){
					new=new->next;
				}
				(idx->tab)[h]=(Reg*)malloc(sizeof(Reg));
				new->next=(idx->tab)[h];
				new->next->next=NULL;
				for(i=0;i<17;i++) (new->next->word)[i]=tolower(word1[i]);
				new=new->next;
				idx->tab[h]=aux;
			}
			linha=1;
			k=0;
			for(i=0;i<100;i++) (new->occur)[i]=0;		/* inicializa o vetor de ocorrencias */
			rewind(text);		/* volta ao inicio do arquivo do texto */
			test[0]='_';
			while(!feof(text)){		/* percorre o arquivo do texto */
				fgets(word2,100,text);		/* le a linha do texto */
				if(strcmp(test,word2)!=0){		/* evita que uma linha seja lida duas vezes consecutivas */
					if(word2[strlen(word2)-1]=='\n') word2[strlen(word2)-1]='\0';		/* finaliza a linha lida com '\0' */
					for(i=0; i<strlen(word2);i++){
						if(isupper(word2[i])) word2[i]=tolower(word2[i]);		/* converte os caracteres da linha lida para minusculo */
					}
					strcpy(test,word2);
					signal=0;
					pos=strstr(word2, word1);		/* localiza a palavra-chave na linha do texto se ela existir no mesmo */
					while(pos!=NULL){
						sub=word2;
						cont=0;
						if(sub!=pos){
							while((sub+1!=pos)&&(pos!=NULL)){		/* localiza a posicao do inicio da palavra na linha */
								sub=sub+1;
								cont=cont+1;
							}
						}
						if(pos!=NULL){		/* atribui a posicao k do vetor de ocorrencias a linha em que a palavra esta */
							if((cont==0)&&(sub==pos)){
								signal=1;
							}
							if((((ispunct(word2[cont]))||(word2[cont]==' '))||(cont==0))&&((ispunct(word2[cont+strlen(word1)+1]))
								||((word2[cont+strlen(word1)+1]==' ')||(word2[cont+strlen(word1)+1]=='\0')))){
								signal=1;
							}
						}
						sub=sub+2;
						pos=strstr(sub,word1);
					}
					pos=NULL;
					sub=NULL;
					if(signal==1){
						(new->occur)[k]=linha;
						k=k+1;
					}
					linha=linha+1;
				}
			}
		}else{
			new=(idx->tab)[ind];		/* aponta para a posicao da tabela em que a palavra esta, se ela existe no indice */
			linha=1;
			k=0;
			for(i=0;i<100;i++) (new->occur)[i]=0;		/* reinicializa o vetor de ocorrencias da palavra */
			rewind(text);		/* volta ao inicio do arquivo do texto */
			test[0]='_';
			while(!feof(text)){		/* percorre o arquivo do texto */
				fgets(word2,100,text);		/* le a linha do arquivo do texto */
				if(strcmp(test,word2)!=0){		/* evita que a mesma linha seja lida duas vezes consecutivas */
					if(word2[strlen(word2)-1]=='\n') word2[strlen(word2)-1]='\0';		/* finaliza a linha lida com '\0' */
					for(i=0; i<strlen(word2);i++){
						if(isupper(word2[i])) word2[i]=tolower(word2[i]);		/* converte os caracteres da linha lida para minusculo */
					}
					strcpy(test,word2);
					signal=0;
					pos=strstr(word2, word1);		/* localiza a palavra-chave na linha do texto se ela existir no mesmo */
					while(pos!=NULL){
						sub=word2;
						cont=0;
						if(sub!=pos){
							while((sub+1!=pos)&&(pos!=NULL)){		/* localiza a posicao do inicio da palavra na linha */
								sub=sub+1;
								cont=cont+1;
							}
						}
						if(pos!=NULL){		/* atribui a posicao k do vetor de ocorrencias a linha em que a palavra esta */
							if((cont==0)&&(sub==pos)){
								signal=1;
							}
							if((((ispunct(word2[cont]))||(word2[cont]==' '))||(cont==0))&&((ispunct(word2[cont+strlen(word1)+1]))
								||((word2[cont+strlen(word1)+1]==' ')||(word2[cont+strlen(word1)+1]=='\0')))){
								signal=1;
							}
						}
						sub=sub+2;
						pos=strstr(sub,word1);
					}
					pos=NULL;
					sub=NULL;
					if(signal==1){
						(new->occur)[k]=linha;
						k=k+1;
					}
					linha=linha+1;

				}
			}			
		}
		fclose(text);		/* fecha o arquivo do texto */
		return 0;
		
	}else{
		return 1;
	}
}
