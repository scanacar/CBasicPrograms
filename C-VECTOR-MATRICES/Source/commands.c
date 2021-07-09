#include "functions.h"

//VecREAD
Vector* vecread (char **text, char *folderName){
	
	FILE *vInput;
	char *v	= (char*) malloc (sizeof(char)*100);
	strcpy(v,folderName);
	strcat(v,"/");
	strcat(v,text[1]);	

	if ( ( vInput = fopen(v,"r") ) != NULL ){
		
		char *vLine = (char*) malloc (sizeof(char)*200), *vArray;
		
		while (fgets(vLine,200,vInput)){
							
			if ( strcmp (vLine,"\r\n") || strcmp(vLine,"\n") ){
	
				int vIndex = 0;
				char **vText = (char **) malloc (sizeof(char*)*(vIndex+1));
				vArray = strtok(vLine," ");
				
				do{
					
					vText = (char**) realloc (vText,sizeof(char*)*(vIndex+1));
					vText[vIndex] = (char*) malloc (sizeof(char)*(strlen(vArray)+1));
					strcpy(vText[vIndex],vArray);
					
					vIndex++;
					vArray = strtok(NULL," \n");
				}while ( vArray != NULL);
			
				return createVector(text,vText,vIndex);
		
			}
			else{
				continue;
			}
		}
		fclose(vInput);
	}
	else{
		printf("Error File!\n");
	}
}
//MatREAD
Matrix* matread(char **text, char *folderName){
	FILE *mInput;
	char *m = (char*) malloc (sizeof(char)*100);
	strcpy(m,folderName);
	strcat(m,"/");
	strcat(m,text[1]);	
	
	if ( ( mInput = fopen(m,"r") ) != NULL ){
		
		char p;
		int row = 1,col = 1;
		do{
			p = getc(mInput);
			if (p == '\n'){
				p = getc (mInput);
				if (p != EOF){
					row++;
				}
			}
			if (p == ' '){
				col++;
			}
		}while(p != EOF);
		col = (col/row)+1;
		
		rewind(mInput);
		int **mArray = (int **) malloc (sizeof(int*)*row);
		int i;
		for (i=0;i<row;i++){
			mArray [i] = (int *) malloc (sizeof(int)*col);
		} 
		int r,c;
		for (r=0;r<row;r++){
			for (c=0;c<col;c++){
				fscanf (mInput,"%d",&mArray[r][c]);
			}
		}
		fclose(mInput);
		return createMatrix (text,mArray,row,col);
	}
	else{
		printf("Error File!\n");
	}
}

//getVectorAccordingtoName
/*Vector* getVectorAccordingtoName(Files *files, char *vectorName){

    Vector *p = files->headVec , *q;

    while(p && !strcmp( p->name , vectorName )){

        q=p;
        p=p->next;
    }
    if(p == NULL){
        printf("Vector yok");
    }
    else{
        return q;
    }
}

Vector* vecslice (Files *files,char **text){
	
	int i,start,stop;
	
	start = atoi(text[2]);
	stop = atoi(text[3]);
	
	Vector *newVector = newVec();
	newVector->column = stop;
	newVector->name = (char *) malloc (sizeof(char)*(strlen(text[4])+1));
	strcpy(newVector->name,text[4]);
	
	getVectorAccordingtoName(files, text[1]);
	
	for (i=start;i<stop;i++){
		
		newVector->value[i] = getVectorAccordingtoName(files, text[1])->value[i];
	}
	
	printf("vector sliced %s %d\n",newVector->name,newVector->column);
	
	for (i=start;i<stop;i++){
		
		printf("%d ",newVector->value[i]);
	}
	
	return newVector;
	
}*/
