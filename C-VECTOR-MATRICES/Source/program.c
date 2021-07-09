#include "functions.h"

//Program
void Program(char *folderName,char *txtName){
	
	FILE *input; Files *files = newFiles();

	if (  (  input = fopen(txtName,"r")  )  != NULL ){
		
		char *lines = (char*) malloc (sizeof(char)*500), *array;
		
		while (fgets(lines,500,input) != NULL){
			
			if ( strcmp(lines,"\r\n") || strcmp(lines,"\n") ){
				
				int index = 0;
				char **text = (char**) malloc (sizeof(char*)*(index+1));
				
				array = strtok (lines," ");
				
				do{
					
					text = (char**) realloc (text,sizeof(char*)*(index+1));
					text [index] = (char*) malloc (sizeof(char)*strlen(array)+1);
					strcpy(text[index], array);
					
					index++;
					array = strtok (NULL," \n");					
					
				}while (array != NULL);
				
				if (strcmp(text[0],"veczeros") == 0){
					
					placeVector(files , createVecZeros(text) );
	
				}
				
				else if (strcmp(text[0],"matzeros") == 0){
					
					placeMatrix(files , createMatZeros(text) );
					
				}
				else if (strcmp(text[0],"vecread") == 0){
					
					placeVector(files , vecread(text,folderName));
					
				}
				else if (strcmp(text[0],"matread") == 0){
					
					placeMatrix (files, matread(text,folderName));
				}/*
				else if (strcmp(text[0],"vecstack") == 0){

				}
				else if (strcmp(text[0],"matstack") == 0){

				}
				else if (strcmp(text[0],"mvstack") == 0){

				}
				else if (strcmp(text[0],"pad") == 0){

				}
				else if (strcmp(text[0],"padval") == 0){

				}
				else if (strcmp(text[0],"vecslice") == 0){
					placeVector (files, vecslice(files,text));
				}
				else if (strcmp(text[0],"matslicecol") == 0){

				}
				else if (strcmp(text[0],"matslicerow") == 0){

				}
				else if (strcmp(text[0],"matslice") == 0){

				}
				else if (strcmp(text[0],"add") == 0){

				}
				else if (strcmp(text[0],"multiply") == 0){

				}
				else if (strcmp(text[0],"subtract") == 0){

				}
				*/
				
			}
			else {
				continue;
			}
			
		}
		fclose(input);	
	}
	else{
		printf("Error File!\n");
	}
}
