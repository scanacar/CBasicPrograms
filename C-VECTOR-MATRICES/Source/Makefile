
output: matrixman.o program.o newObject.o createAndPlace.o commands.o
	gcc matrixman.o program.o newObject.o createAndPlace.o commands.o -o matrixman
	
matrixman.o: matrixman.c
	gcc -c matrixman.c

program.o: program.c functions.h
	gcc -c program.c

newObject.o: newObject.c functions.h
	gcc -c newObject.c

createAndPlace.o: createAndPlace.c functions.h
	gcc -c createAndPlace.c
	
commmands.o: commands.c functions.h
	gcc -c commands.c
	
clean:
	rm *.o matrixman