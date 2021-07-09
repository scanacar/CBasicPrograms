#include "functions.h"

//NewFiles
Files* newFiles(){
	
	Files* files = (Files*) malloc (sizeof(Files));
	files->headMat = NULL;
	files->headVec = NULL;
	return files;
}
//NewVector
Vector* newVec(){
	
	Vector *newVector = (Vector *) malloc (sizeof(Vector));
	newVector->next = NULL;
	return newVector;
}
//NewMatrix
Matrix* newMat(){
	
	Matrix *newMatrix = (Matrix *) malloc (sizeof(Matrix));
	newMatrix->next = NULL;
	return newMatrix;
}
