#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Structlar
typedef struct file{
	
	struct file *next;
	char *name;
	char *content;
	int numberOfWord;
	int number;
	
}File;


//Fonksiyon prototipleri
void readingFile(char *textName);
void create(char **text, File **head,int column);
void append(char **text, File **head,int column);
void replace(char **text, File **head,int column);
void Remove(char **text, File **head,int column);
void Delete(char **text, File **head,int column);
void print(char **text, File **head,int column);
void replaceHelpFunction(File *p , char *newWord, char *oldWord );
int** findNumberAndIndexOfKey(char *text, char *key, int *textCounter,int *keyCounter,int *numberOfWords,int **array);


//Main fonksiyonu
int main(int argc, char **argv){
	
	if (argc == 2){
		readingFile(argv[1]) ;	
	}
	else{
		printf("Parameter Error!\n");
	}
	return 0;
}

//Readingfile fonksiyonu
void readingFile(char *textName){
		
	FILE *input;   File *head = NULL;
	
	if ( (input = fopen(textName,"r") ) != NULL){
		
		char *givenCommands = (char*) malloc(sizeof(char)*500) , *array;   
		
		while(fgets(givenCommands,500,input) != NULL){
			
			givenCommands[ strcspn( givenCommands , "\n")] = 0;
			givenCommands[ strcspn( givenCommands , "\r\n")] = 0;
			
			printf("%s\n",givenCommands);

			int column = 0;
			char **text = (char **) malloc(sizeof(char*)*(column+1));                   
			
			array = strtok(givenCommands," ");
			do{
				text = (char**) realloc(text,sizeof(char*)*(column+1));
				text[column] = (char*) malloc(sizeof(char)*(strlen(array)+1));
				strcpy(text[column] , array);
				
				column++;
				array = strtok(NULL," ");

				
			}while( array != NULL);
			
			if(strcmp(text[0],"create") == 0){
				
				create(text,&head,column);
			}
			else if(strcmp(text[0],"append") == 0){
				
				append(text,&head,column);
				
			}
			else if(strcmp(text[0],"replace") == 0){
				
				replace(text,&head,column);
			}
			else if(strcmp(text[0],"remove") == 0){
				
				Remove(text,&head,column);
			}			
			else if(strcmp(text[0],"delete") == 0){
				
				Delete(text,&head,column);
			}
			else if(strcmp(text[0],"print") == 0){
				
				print(text,&head,column);
			}			

		}
		fclose(input);
	}
	else{
		printf("FileOpenError!\n");
	}	
}

//CREATE
void create(char **text, File **head,int column){
	
	//Oluþturma kýsmý
	File *newFile = (File *) malloc (sizeof(File)*1);
	newFile->content = NULL;
	newFile->next = NULL;
	newFile->numberOfWord=0;
	
	int i,j,k=1,r;
	char *parameter = NULL;

	for(i=1;i<column;i++){
		
		if(strcmp(text[i],"-n")==0 || strcmp(text[i],"-t")==0){ //Parametre belirleme kýsmý
			if (parameter==NULL) parameter = (char*) malloc (sizeof(char)*(strlen(text[i])+1));
			strcpy(parameter,text[i]);
			j=i;
			if(k==1){  // Cümle sonundaki nokta silinmesin diye yaptým
				r=j;
				k=0;
			} 
		}
		else if(strcmp(parameter,"-n")==0){
			newFile->name = (char*) malloc (sizeof(char)*(strlen(text[i])+1));
			strcpy(newFile->name,text[i]);
					
		}
		else if(strcmp(parameter,"-t")==0){
			
			if (j+1==i) {
				
				newFile->content = (char*) malloc (sizeof(char)*strlen(text[i])+1);
				strcpy(newFile->content,text[i]);
			}
			else {
				newFile->content = (char*) realloc (newFile->content,sizeof(char)*(strlen(newFile->content)+strlen(text[i])+1));
				strcat(newFile->content,text[i]);
			}		
			if (i+1 != column) {
				newFile->content = (char*) realloc (newFile->content,sizeof(char)*(strlen(newFile->content)+strlen(" ")+1));
				strcat(newFile->content," ");
			}

			newFile->numberOfWord++;
		}	
	}
	if(strcmp(text[r],"-n")==0) newFile->content[strlen(newFile->content)]='\0';
	else                        newFile->content[strlen(newFile->content)-1]='\0';
	
	i=1;
	//Yerleþtirme kýsmý
	if (*head == NULL ){   // Liste boþsa
		
		*head = newFile;
		newFile->number=i;
	}
	else {

		File *p = *head,*q; 
		
		while(p && strcmp(p->name,newFile->name) != 0){
			
			q=p;
			p=p->next;
			i++;
		}
		if(p && strcmp(p->name,newFile->name) == 0){
			printf("SameFileError!\n");
		}
		else{
			q->next = newFile;
			newFile->number = i;
		}	
	}	
}

//DELETE
void Delete(char **text, File **head,int column){
	
	char *dosyaismi = NULL;
	char *parameter = NULL;
	File *p, *q;
	int i;
	
	for(i=1;i<column;i++){
		
		if (strcmp(text[i],"-n")==0){
			
			parameter = (char*) malloc (sizeof(char)*(strlen(text[i])+1));
			strcpy(parameter,text[i]);

				
		}
		else if(strcmp(parameter,"-n")==0){
			
			dosyaismi = (char*) malloc (sizeof(char)*(strlen(text[i])+1));
			strcpy(dosyaismi,text[i]);
			
			p = *head;
			q = NULL;
			
			if (p == NULL) printf("NoFileError!\n");
			else{
				
				while (p && strcmp(p->name,dosyaismi)!=0){
				
					q = p;
					p = p->next;
				}
				
				if (q == NULL){  // While girmemiþse
					
					*head = p->next;
					free(p);
				}
				else{   // While a girmiþse
					
					if(p){  // Adlý dosya varsa
						q->next = p->next;
						free(p);
					}
					else{  // Yoksa
						printf("NonameFileError!\n");
					}
				}
			}
		}
	}
}

//REMOVE
void Remove(char **text, File **head,int column){
	
	int i,startindex,len;
	char *parameter = NULL;
	char *dosyaismi = NULL;
	File *p;
	
	for(i=1;i<column;i++){

		if (strcmp(text[i],"-n")==0 || strcmp(text[i],"-s")==0 || strcmp(text[i],"-l")==0 ){	
			if (parameter == NULL){
				
				parameter = (char*) malloc (sizeof(char)*(strlen(text[i])+1));
				
			}
			strcpy(parameter,text[i]);
			
		}
		else if(strcmp(parameter,"-n")==0){
			dosyaismi = (char*) malloc (sizeof(char)*(strlen(text[i])+1));
			strcpy(dosyaismi,text[i]);
		}
		else if(strcmp(parameter,"-s")==0){
			startindex = atoi(text[i]);
		}
		else if(strcmp(parameter,"-l")==0){
			len = atoi(text[i]);
		}
		
	}
	p = *head;
	while (p && strcmp(p->name,dosyaismi)!=0){	
		p = p->next;
	}
	if (p){
		if (startindex >= strlen(p->content) || (startindex + len) >= strlen(p->content)){
			printf("IndexError!\n");
		}
		else {
			for (i=startindex+len;i<strlen(p->content);i++){
				
				p->content[i-len] = p->content[i];	
			}
			p->content[strlen(p->content)-len] = '\0';	
		}	
	}
	else printf("FileError!\n");
	
}

//APPEND
void append(char **text, File **head,int column){
	
	int i,j;
	char *parameter = NULL;
	char *testarray = NULL;
	
	File *p = NULL,*q,*r = *head;
	
	for(i=1;i<column;i++){
		
		if(strcmp(text[i],"-n")==0 || strcmp(text[i],"-t")==0){
			if (parameter==NULL) parameter = (char*) malloc (sizeof(char)*(strlen(text[i])+1));
			strcpy(parameter,text[i]);
			j=i;
		}
		else if(strcmp(parameter,"-n")==0){
			
			if (*head == NULL ){   // Liste boþsa
				
				printf("ListError!\n");
			}
			else {
				p = r;
				while(p && strcmp(p->name,text[i]) != 0){
					
					q=p;
					p=p->next;
				}
				if(p && strcmp(p->name,text[i]) == 0){
					
				}
				else{
					printf("KeyError!\n");
					return;
				}	
			}
		}
		else if(strcmp(parameter,"-t")==0){
			if (i+1==column){
				
				testarray = NULL;
			}
			else if (testarray == NULL) {
				
				testarray = (char*) malloc (sizeof(char)*(strlen(text[i])+1));
				strcpy(testarray,text[i]);
			}
			else {
				testarray = (char*) realloc (testarray,sizeof(char)*(strlen(testarray)+strlen(text[i])+1));
				strcat(testarray,text[i]);
			}		
			if (i+1 != column) { 
				testarray = (char*) realloc (testarray,sizeof(char)*(strlen(testarray)+strlen(" ")+1));
				strcat(testarray," ");
			}
		}	
	}
	
	if(p && testarray != NULL){
		if(p->numberOfWord != 0){

			p->content = (char*) realloc (p->content,sizeof(char)*(strlen(p->content)+strlen(testarray)+1));
			strcat(p->content,testarray);

		}
		else if(p->numberOfWord == 0){
			
			p->content = (char*) malloc (sizeof(char)*(strlen(testarray)+1));
			strcpy(p->content,testarray);
		}
		p->numberOfWord++;	
	
	}

}

//Replace ve print -cw yardýmcý fonksiyonu
int** findNumberAndIndexOfKey(char *text, char *key, int *textCounter,int *keyCounter,int *numberOfWords,int **array){
	
	if( strlen(key) > strlen(text) ){
		return NULL;
	}
	else{
		
		if( *textCounter < strlen(text) ){
	
			if( key[*keyCounter] != text[*textCounter] ){
				
				*textCounter = (*textCounter) +1;
				*keyCounter = 0;
			}
			else{
				if( *keyCounter == strlen(key)-1 ){
					
					*numberOfWords = (*numberOfWords) +1;
					*keyCounter = 0;
					
		
					if(array == NULL)  array = (int**) malloc(sizeof(int*)* (*numberOfWords) );
					else               array = (int**) realloc( array, sizeof(int*)* (*numberOfWords) );
					
					array[ (*numberOfWords)-1] = (int*) malloc(sizeof(int)*2);
					array[ (*numberOfWords)-1][0] = *textCounter - strlen(key)+1 ;
					array[ (*numberOfWords)-1][1] = *textCounter ;
				}
				else{
					
					*keyCounter = *keyCounter +1;			
				}
				*textCounter = *textCounter +1;
			}
			findNumberAndIndexOfKey(text,key,textCounter,keyCounter,numberOfWords,array);
		}
		else{
			return array;
		}
	}	
}
//Replace Help Function
void replaceHelpFunction(File *p, char *newWord, char *oldWord ){
	
	int textCounter =0,keyCounter =0,numberOfWords=0;
	int **array = findNumberAndIndexOfKey(p->content,oldWord,&textCounter,&keyCounter,&numberOfWords,NULL); // array[0][1] finishIndex , array[0][0] startIndex;

	if(numberOfWords == 0 || array == NULL){
		return;
	}
	else{
		
		int i,j,difference;
		//Deðiþtirme kýsmý
		if( strlen(newWord) == (array[0][1] - array[0][0])+1 ){       // Lenler ayný ise
			
			for(i=array[0][0] ,j=0; i<= array[0][1] ; i++,j++){ // Yerleþtirme kýsmý
				p->content[i] = newWord[j];
			}
		}
		else if( strlen(newWord) < (array[0][1] - array[0][0])+1) {    // Yeni kelime küçükse
		
			for(i=array[0][0] ,j=0; i< array[0][0]+strlen(newWord) ; i++,j++){ // Yeni kelimeyi yerleþtirme kýsmý
				p->content[i] = newWord[j];
			}
			difference = strlen(oldWord)-strlen(newWord);
			for(i=array[0][1]+1 ; i< strlen(p->content) ; i++){  // Kaydýrma kýsmý
				
				p->content[i-difference]  = p->content[i];
			}  
			p->content[ strlen(p->content)-difference] = '\0';
		}
		
		else if( strlen(newWord) > (array[0][1] - array[0][0])+1 ){       // Yeni kelime büyükse
			
			difference = strlen(newWord) - strlen(oldWord);
			p->content = (char*) realloc (p->content,sizeof(char)*(strlen(p->content)+difference+1));

			for(i=strlen(p->content)-1  ; i>array[0][1] ; i--){ // Kaydýrma kýsmý  
				
				p->content[i+difference] = p->content[i];
			}  

			p->content[strlen(p->content)+difference] = '\0';
			
			for(i=array[0][0] ,j=0; i<= array[0][1]+difference ; i++,j++){ // Yeni kelimeyi yerleþtirme kýsmý
				p->content[i] = newWord[j];
			}
			
		}		
		replaceHelpFunction(p, newWord, oldWord );
	}
}
//REPLACE
void replace(char **text, File **head,int column){

	int i,j,r;
	File *p;
	
	for(i=1;i<column;i++){
		
		if (strcmp(text[i],"-n")==0){
			
			p = *head;
			
			while (p && strcmp(p->name,text[i+1]) !=0 ){
				
				p = p->next;
			}
		}
		else if (strcmp(text[i],"-ow")==0){
			j=i+1;
		}
		else if (strcmp(text[i],"-nw")==0){
			r=i+1;
			
			replaceHelpFunction(p,text[r],text[j]);
		}	
	}

}

//PRINT
void print(char **text, File **head,int column){
	
	int i;
	File *p;
	char *ptr;
	
	for(i=1;i<column;i++){
		
		if (strcmp(text[i],"-n")==0){
			
			p = *head;
			
			while (p && strcmp(p->name,text[i+1]) !=0 ){
				
				p = p->next;
			}
		}
		else if (strcmp(text[i],"-t")==0){
			if (p != NULL){
				
				printf("Text: %s\n",p->content);
			}
		}
		else if (strcmp(text[i],"-a")==0){
			
			p = *head;
			while (p){
				
				printf("Filename %d: %s\n",p->number,p->name);
				p = p->next;

			}
		}
		else if (strcmp(text[i],"-e")==0){
			
			char *temp = (char*) malloc (sizeof(char)*50);
			p = *head;
			
			while(p){
				
				strcpy(temp,p->name);
				ptr = strtok (temp,".");
				ptr = strtok (NULL,".");
				
				if (strcmp(ptr,text[i+1])==0){
					
					ptr = strtok (temp,".");
					printf("Filename %d: %s\nText: %s\n",p->number,ptr,p->content);
				}
				
				p = p->next;
			}
		}
		else if (strcmp(text[i],"-c")==0){
			
			char *temp = (char*) malloc (sizeof(char)*50);
			p = *head;
			
			while(p){
				
				strcpy(temp,p->name);
				ptr = strtok (temp,".");
				
				printf("Num: %d\nName: %s\nText: %s\n",p->number,ptr,p->content);
			
				p = p->next;
			}
			
		}
		else if (strcmp(text[i],"-cw")==0){
			
			if(p){
				
				int textCounter = 0,keyCounter=0,numberOfWords=0 ;	
		
		        findNumberAndIndexOfKey(p->content,text[i+1],&textCounter,&keyCounter,&numberOfWords,NULL);
				
				printf("Text: %s\nNumber Of Occurrence of \"%s\" : %d\n",p->content,text[i+1], numberOfWords );
			}
		}
		else if (strcmp(text[i],"-cs")==0){
			
			if(p){
				
				char *temp = (char*) malloc (sizeof(char)*500);
				int count=0;
				strcpy(temp,p->content);
				
				if (p->numberOfWord!=0){
					
					ptr = strtok (temp,".?!");
					while (ptr){
					
						ptr = strtok (NULL,".?!");
						count++;
					}
				}
				printf("Number Of Sentences: %d\n",count);
			}
		}
	}	
}
