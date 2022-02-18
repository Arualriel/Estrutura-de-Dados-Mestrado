#include <stdio.h>
#include "Index.h"

int main(int argc, char **argv){
	
	if(argc<3){
		printf("Erro: quantidade de arquivos de entrada invalida\n");
		printf("Sintaxe: %s key file name text file name\n",argv[0]);
		return 1;
	}
	
	Index *idx;
	int *occ, i, numocc;
	char keyword[17], new_keyword[17];
	idx=NULL;
	
	if(!index_createfrom(argv[1],argv[2],&idx)){
		index_print(idx);
	}else{
		printf("Erro ao criar o indice remissivo\n");
		return 1;
	}
	
	printf("Qual a palavra-chave a procurar?\n");
	scanf(" %16[^\n]",keyword);
	
	if(!index_get(idx,keyword,&occ,&numocc)){
		printf("Ha %d ocorrencias de %s\n",numocc,keyword);
		if(numocc>0){
			printf("Ocorrencia nas linhas: ");
			for(i=0;i<numocc;i++) printf("%d ",occ[i]);
			printf("\n");
		}else{
			printf("Nao ha ocorrencias de %s \n",keyword);
		}
	}else{
		printf("A palavra %s nao pertence ao indice \n",keyword);
	}
	
	if(index_print(idx)){
		printf("Erro ao exibir o indice remissivo\n");
		return 1;
	}
	
	printf("Qual a palavra-chave a inserir?\n");
	scanf(" %16[^\n]",new_keyword);
	
	if(index_put(idx,new_keyword)){
		printf("Erro ao inserir a palavra %s",new_keyword);
		return 1;
	}else{
		printf("Indice remissivo atualizado:\n");
	}
	
	if(index_print(idx)){
		printf("Erro ao exibir o indice remissivo\n");
		return 1;
	}
	
	index_destroy(idx);
	
	return 0;
}
