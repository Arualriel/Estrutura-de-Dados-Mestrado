#include <stdio.h> 
#include "Matrix.h"


int main(void){
	Matrix *A=NULL, *B=NULL, *C=NULL;
	float elem;
	int x=2,y=2;
	//x=3, y=2;
	//x=1,y=1;
	//x=3, y=3;
	//x=4,y=1;
	//x=2,y=3;
	//x=1,y=3;
	//x=4,y=4;
	if(!matrix_create(&A)){	
		printf("Matriz A:\n");
		matrix_print(A);
	}else{
		printf("Erro na alocacao da matriz A\n");
		return 1;
	}
	
	if(!matrix_getelem(A,x,y,&elem)){
		printf("O elemento de posicao x=%d, y=%d na matriz A eh %f \n",x,y,elem);
	}else{
		printf("Erro ao buscar elemento da posicao x=%d, y=%d na matriz A\n",x ,y);
	}
	
	elem=-2*elem+0.7;
	
	if(!matrix_setelem(A,x,y,elem)){
		printf("Elemento %f atribuido as posicoes x=%d, y=%d da matriz A\n",elem,x,y);
		matrix_print(A);
	}else{
		printf("Erro ao atribuir o elemento %f as posicoes x=%d, y=%d da matriz A\n",elem,x,y);
	}
	
	if(!matrix_transpose(A,&C)){
		printf("A transposta de A\n");
		matrix_print(C);
	}else{
		printf("Erro ao transpor A\n");
	}
	
	matrix_destroy(C);
	
	if(!matrix_create(&B)){
		printf("Matriz B:\n");
		matrix_print(B);
	}else{
		printf("Erro na alocacao da matriz B\n");
		return 1;
	}
	
	if(!matrix_getelem(B,x,y,&elem)){
		printf("O elemento de posicao x=%d, y=%d na matriz B eh %f \n",x,y,elem);
	}else{
		printf("Erro ao buscar elemento da posicao x=%d, y=%d na matriz B\n",x ,y);
	}
	
	elem=2*elem+0.5;
	
	if(!matrix_setelem(B,x,y,elem)){
		printf("Elemento %f atribuido as posicoes x=%d, y=%d da matriz B\n",elem,x,y);
		matrix_print(B);
	}else{
		printf("Erro ao atribuir o elemento %f as posicoes x=%d, y=%d da matriz B\n",elem,x,y);
	}
	
	if(!matrix_transpose(B,&C)){
		printf("A transposta de B\n");
		matrix_print(C);
	}else{
		printf("Erro ao transpor B\n");
	}
	
	matrix_destroy(C);
	
	if(!matrix_add(A,B,&C)){
		printf("C = A + B\n");
		matrix_print(C);
	}else{
		printf("Erro na soma C = A + B\n");
	}
	
	matrix_destroy(C);
	
	if(!matrix_multiply(A,B,&C)){
		printf("C = A * B\n");
		matrix_print(C);
	}else{
		printf("Erro na multiplicacao C = A * B\n");
	}		
	
	matrix_destroy(C);
		
	if(!matrix_multiply(B,A,&C)){
		printf("C = B * A\n");
		matrix_print(C);
	}else{
		printf("Erro na multiplicacao C = B * A\n");
	}
	
	matrix_destroy(A);
	matrix_destroy(B);
	matrix_destroy(C);
	
	return 0;
}
