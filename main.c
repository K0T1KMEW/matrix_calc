#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <direct.h>
#include <malloc.h>
#include "func.h"
#include <time.h>
int main() {
	char operation;
	printf("enter operation (+, -, *, t(transposition), d(find determind))\noperation: ");
	scanf_s("%c", &operation, 1);
	printf("\n");
	checkoperation(operation);

	int rows1, cols1, rows2, cols2;
	int** matrix1 = readMatrixFromFile("matrix1.txt", &rows1, &cols1);
	int** matrix2 = readMatrixFromFile("matrix2.txt", &rows2, &cols2);
	
	if (operation == '+') {
		check(&rows1, &cols1, &rows2, &cols2);
		printf("matrix 1:\n");
		printMatrix(matrix1, &rows1, &cols1);
		printf("\n");
		printf("matrix 2:\n");
		printMatrix(matrix2, &rows2, &cols2);
		printf("\n");
		int** result = addMatrices(matrix1, matrix2, &rows1, &cols1);
		printf("Result:\n");
		printMatrix(result, &rows1, &cols2);
		writeResultToFile(result, &rows1, &cols1);
		freememory(matrix1, matrix2, result, &rows1);
	}
	if (operation == '-') {
		check(&rows1, &cols1, &rows2, &cols2);
		printf("matrix 1:\n");
		printMatrix(matrix1, &rows1, &cols1);
		printf("\n");
		printf("matrix 2:\n");
		printMatrix(matrix2, &rows2, &cols2);
		printf("\n");
		int** result = disMatrices(matrix1, matrix2, &rows1, &cols1);
		printf("Result:\n");
		printMatrix(result, &rows1, &cols2);
		writeResultToFile(result, &rows1, &cols1);
		freememory(matrix1, matrix2, result, &rows1);
	}
	if (operation == '*') {
		printf("matrix 1:\n");
		printMatrix(matrix1, &rows1, &cols1);
		printf("\n");
		printf("matrix 2:\n");
		printMatrix(matrix2, &rows2, &cols2);
		printf("\n");
		int** result = multiplyMatrices(matrix1, &rows1, &cols1, matrix2, &rows2, &cols2);
		printf("Result:\n");
		printMatrix(result, &rows1, &cols2);
		writeResultToFile(result, &rows1, &cols1);
		freememory(matrix1, matrix2, result, &rows1);
	}
	if (operation == 't') {
		printf("matrix:\n");
		printMatrix(matrix1, &rows1, &cols1);
		printf("\n");
		int** result = transposition(matrix1, &rows1, &cols1);
		printf("Result:\n");
		printMatrix(result, &rows1, &cols2);
		writeResultToFile(result, &rows1, &cols1);
		freememory(matrix1, matrix2, result, &rows1);
	}
	if (operation == 'd') {
		printf("matrix: \n");
		printMatrix(matrix1, &rows1, &cols1);
		printf("\n");
		int determinant = determinantOfMatrix(matrix1, rows1);
		printf("detemind of matrix: %d\n", determinant);
		//writeResultToFile(result, &rows1, &cols1, operation, determinant);
		writeResultofDeterminant(determinant);
	}
	return 0;
}