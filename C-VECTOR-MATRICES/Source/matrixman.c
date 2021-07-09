#include "functions.h"

//Main
int main(int argc, char **argv){
	
	if (argc == 3){
		Program(argv[1],argv[2]);
	}
	else{
		printf("Parameter error!\n");
	}
	return 0;
}
