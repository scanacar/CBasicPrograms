#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Prototype of functions


void Program(char *folderName,char *txtName);


//In commands.c
Vector* vecread (char **text,char *folderName); 
Matrix* matread (char **text,char *folderName);
//Vector* getVectorAccordingtoName(Files *files, char *vectorName);

//In newObject.c
Files* newFiles();
Vector* newVec();
Matrix* newMat();

//In createAndPlace.c
Vector* createVecZeros(char **text);
Vector* createVector(char **text,char **vText, int vIndex);
//Vector* vecslice(Files *files,char **text);
void placeVector(Files *files , Vector *newVector);

Matrix* createMatZeros(char **text);
Matrix* createMatrix(char **text,int **mArray,int row,int col);
void placeMatrix(Files *files , Matrix *newMatrix);
