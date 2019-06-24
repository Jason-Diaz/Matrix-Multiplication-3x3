/*
* Project 3: Matrix Multiplication
* Jason Diaz
*/

#include<stdio.h> 
#include<stdlib.h>
#include<pthread.h>

void inputMatrix(int matrix1[3][3], int matrix2[3][3]);
void displayMatrix(int matrix[3][3]);
void *thread_func(void *args);

struct tmatrix{
	int (*matrix1)[3];
	int (*matrix2)[3];
	int (*result)[3];
	int element;
};

int main(int argc, char *argv[]) {

	pthread_t pt[9];
	int matrix1[3][3];
	int matrix2[3][3];
	int result[3][3];
	int i;
	struct tmatrix matrix;
	
	matrix.matrix1 = matrix1;
	matrix.matrix2 = matrix2;
	matrix.result = result;
	inputMatrix(matrix1, matrix2);
	
	printf("First Matrix:\n");
	displayMatrix(matrix1);
	printf("Second Matrix:\n");
	displayMatrix(matrix2);
	
	for(i=0;i<9;i++){
	pthread_create(&pt[i],NULL,thread_func,(void *)&matrix);
	matrix.element = i;
	}
	
	printf("Result:\n");
	displayMatrix(result);
	
	for(i=0;i<9;i++){
		pthread_join(pt[i],NULL);
	}
	
	return -1;
}

/*inputMatrix: reads in the matrices from standard input */
void inputMatrix(int matrix1[3][3], int matrix2[3][3]){
	int i,j;
	int input[3]; //this will hold the three value the user inputs
	
	//first matrix
	for(i=1;i<4;i++) { //fills up the first matrix
	printf("Please enter 3 values for row %d in the first matrix:\n", i);
	scanf("%d %d %d",&input[0], &input[1], &input[2]);
	for(j=0;j<3;j++) { //this for loop occurs for every row in the first matrix
	matrix1[i-1][j] = input[j];
	}
	}
	//second matrix
	for(i=1;i<4;i++) { //fills up the second matrix
	printf("Please enter 3 values for row %d in the second matrix:\n", i);
	scanf("%d %d %d",&input[0], &input[1], &input[2]);
	for(j=0;j<3;j++) { //this for loop occurs for every row in the second matrix
	matrix2[i-1][j] = input[j];
	}
	}
}

/*displayMatrix: prints out the resultant matrix*/
void displayMatrix(int matrix[3][3]){
	int i,j;
	for(i=0;i<3;i++){ //rows
		for(j=0;j<3;j++) { //columns
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

/* *thread_func: takes as its argument a struct (casted to a (void *)) that contains*
* two pointers to double arrays containing the two input matrices, a pointer to a double array
* containing the resultant matrix, and an integer that indicates the matrix element to be 
* calculated. 
*/
void *thread_func(void *args) {
	int i, column, row, math, results = 0;
	struct tmatrix *matrix = (struct tmatrix*) args; //cast args back to a struct tmatrix sets it to a pointer
	
	row = matrix->element/3; //equation for the rows
	column = matrix->element%3; //equation for columns
	
	for(i=0;i<3;i++){
		math = (matrix->matrix1[row][i]) * (matrix->matrix2[i][column]); 
		results = results + math;
	}
	
	matrix->result[row][column] = results; //sets the result of the multiplication to the location in the result matrix
}


