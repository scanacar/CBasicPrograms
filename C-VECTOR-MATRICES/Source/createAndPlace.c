#include "functions.h"

//ZeroVector
Vector* createVecZeros(char **text){
	
	Vector *newVector = newVec();
	newVector->name = (char*) malloc (sizeof(char)*(strlen(text[1])+1));         strcpy(newVector->name,text[1]);
	newVector->column = atoi(text[2]);
	newVector->value = (int *) malloc (sizeof(int)*(atoi(text[2])));
		
	printf("created vector %s %d\n",newVector->name,newVector->column);
	
	int i;
	for (i=0;i<newVector->column;i++){
		newVector->value[i] = 0;
	}
	for (i=0;i<newVector->column;i++){
		printf("%d ",newVector->value[i]);
	}
	printf("\n");
	
	return newVector;	
}
//ZeroMatrix
Matrix* createMatZeros(char **text){
		
	Matrix *newMatrix = newMat();
	newMatrix->name = (char*) malloc (sizeof(char)*(strlen(text[1])+1));       strcpy(newMatrix->name,text[1]);
	newMatrix->row = atoi(text[2]);
	newMatrix->column = atoi(text[3]);
	newMatrix->value = (int **) malloc (sizeof(int*)*(atoi(text[2])));
	
	printf("created matrix %s %d %d\n",newMatrix->name,newMatrix->row,newMatrix->column);
	
	int i,j;
	for (i=0;i<newMatrix->row;i++){
		newMatrix->value[i] = (int*) malloc (sizeof(int)*(atoi(text[3])));
	}
	for (i=0;i<newMatrix->row;i++){
		for (j=0;j<newMatrix->column;j++){
			newMatrix->value[i][j]= 0;
		}
	}
	for (i=0;i<newMatrix->row;i++){
		for (j=0;j<newMatrix->column;j++){
			printf("%d ",newMatrix->value[i][j]);
		}
		printf("\n");
	}
	return newMatrix;
}
//CreateVector
Vector* createVector(char **text,char **vText, int vIndex){
	
	Vector *newVector = newVec();
	newVector->column = vIndex;
	newVector->name = (char *) malloc (sizeof(char)*(strlen(text[1]+1)));       strcpy(newVector->name,text[1]);
	newVector->value = (int *) malloc (sizeof(int)*(vIndex));

	int i;
	for (i=0;i<newVector->column;i++){
		
		newVector->value[i] = atoi(vText[i]); 
	}
	
	printf("read vector %s %d\n",newVector->name,newVector->column);

	for (i=0;i<newVector->column;i++){
		printf("%d ",newVector->value[i]);
	}
	printf("\n");
	
	return newVector;
}
//CreateMatrix
Matrix* createMatrix(char **text,int **mArray,int row,int col){
	
	int i,j;

	Matrix *newMatrix = newMat();
	newMatrix->row = row;
	newMatrix->column = col;
	newMatrix->name = (char *) malloc (sizeof(char)*(strlen(text[1]+1)));
	strcpy(newMatrix->name,text[1]);
	
	newMatrix->value = (int **) malloc (sizeof(int*)*row);
	for (i=0;i<newMatrix->row;i++){
		newMatrix->value[i] = (int *) malloc (sizeof(int)*col);
	}
	
	for (i=0;i<newMatrix->row;i++){
		for(j=0;j<newMatrix->column;j++){
			newMatrix->value[i][j] = mArray[i][j];
		}
	}
	
	printf("read matrix %s %d %d\n",newMatrix->name,newMatrix->row,newMatrix->column);
	
	for (i=0;i<newMatrix->row;i++){
		for (j=0;j<newMatrix->column;j++){
			printf("%d ",newMatrix->value[i][j]);
		}
		printf("\n");
	}
	
	return newMatrix;
}
//PlaceVector
void placeVector(Files *files , Vector *newVector){
	
	if (files->headVec == NULL){
		files->headVec = newVector;
	}
	else{
		Vector *p = files->headVec, *q;
		
		while (p && strcmp(p->name,newVector->name) != 0){
			q=p;
			p=p->next;
		}
		if (p && strcmp(p->name,newVector->name)==0){
			printf("Same Vector!\n");
		}
		else{
			q->next = newVector;
		}
	}
}
//PlaceMatrix
void placeMatrix(Files *files , Matrix *newMatrix){
	
	if (files->headMat == NULL){
		files->headMat = newMatrix;
	}
	else{
		Matrix *p = files->headMat, *q;
		
		while (p && strcmp(p->name,newMatrix->name) != 0){
			q=p;
			p=p->next;
		}
		if (p && strcmp(p->name,newMatrix->name)==0){
			printf("Same Matrix!\n");
		}
		else{
			q->next = newMatrix;
		}
	}
}
