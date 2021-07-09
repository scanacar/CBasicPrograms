//Structs
typedef struct VectorFile{
	struct VectorFile *next;
	int column;
	int *value;
	char *name;
}Vector;

typedef struct MatrixFile{
	struct MatrixFile *next;
	int row;
	int column;
	int **value;
	char *name;
}Matrix;

typedef struct {
	
	Vector *headVec;
	Matrix *headMat;

}Files;
