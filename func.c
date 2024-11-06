#define _CRT_SECURE_NO_WARNINGS
#include "func.h"
#include <malloc.h>
#include <stdio.h>
#include <direct.h>
#include <stdlib.h>

void printMatrix(int** matrix, int* rows, int* cols) {
	for (int i = 0; i < *rows; i++) {
		for (int j = 0; j < *cols; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

void freememory(int** matrix1, int** matrix2, int** result, int* rows) {
	for (int i = 0; i < *rows; i++) {
		free(matrix1[i]);
		free(matrix2[i]);
		free(result[i]);
	}
	free(matrix1);
	free(matrix2);
	free(result);
}

int** readMatrixFromFile(const char* filename, int* rows, int* cols) {
	FILE* file = fopen(filename, "r");
	if (!file) {
		fprintf(stderr, "Error: Unable to open file %s\n", filename);
		exit(1);
	}
	int num;
	int rowCount = 0, colCount = 0;
	while (fscanf_s(file, "%d", &num) == 1) {
		colCount++;
		if (fgetc(file) == '\n') {
			rowCount++;
		}
	}
	*rows = rowCount + 1;
	*cols = colCount / (rowCount + 1);

	fseek(file, 0, SEEK_SET);

	int** matrix = (int**)malloc(*rows * sizeof(int*));
	if (matrix != NULL) {
		for (int i = 0; i < *rows; i++) {
			matrix[i] = (int*)malloc(*cols * sizeof(int));
		}
	}

	int row = 0, col = 0;
	rewind(file);
	while (fscanf(file, "%d", &num) == 1) {
		matrix[row][col] = num;
		col++;
		if (fgetc(file) == '\n') {
			row++;
			col = 0;
		}
	}

	fclose(file);
	return matrix;
}

// Функция для сложения матриц
int** addMatrices(int** matrix1, int** matrix2, int* rows, int* cols) {
	int** result = (int**)malloc((*rows) * sizeof(int*));
	for (int i = 0; i < *rows; i++) {
		result[i] = (int*)malloc((*cols) * sizeof(int));
		for (int j = 0; j < *cols; j++) {
			result[i][j] = matrix1[i][j] + matrix2[i][j];
		}
	}
	return result;
}

// Функция для вычитания матриц
int** disMatrices(int** matrix1, int** matrix2, int* rows, int* cols) {
	int** result = (int**)malloc(*rows * sizeof(int*));
	for (int i = 0; i < *rows; i++) {
		result[i] = (int*)malloc(*cols * sizeof(int));
		for (int j = 0; j < *cols; j++) {
			result[i][j] = matrix1[i][j] - matrix2[i][j];
		}
	}
	return result;
}

// Функция для умножения матриц
int** multiplyMatrices(int** matrix1, int* rows1, int* cols1, int** matrix2, int* rows2, int* cols2) {
	if (*cols1 != *rows2) {
		//fprintf(stderr, "Error: Matrices cannot be multiplied. Columns in matrix1 must be equal to rows in matrix2\n");
		printf("Error: Matrices cannot be multiplied. Columns in matrix1 must be equal to rows in matrix2\n");
		exit(1);
	}

	int** result = (int**)malloc(*rows1 * sizeof(int*));
	for (int i = 0; i < *rows1; i++) {
		result[i] = (int*)malloc(*cols2 * sizeof(int));
		for (int j = 0; j < *cols2; j++) {
			result[i][j] = 0;
			for (int k = 0; k < *cols1; k++) {
				result[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}
	return result;
}

// Фукнция транспонирования матрицы
int** transposition(int** matrix, int* rows, int* cols) {
	int** result = (int**)malloc(*cols * sizeof(int*));
	for (int i = 0; i < *cols; i++) {
		result[i] = (int*)malloc(*rows * sizeof(int));
		for (int j = 0; j < *rows; j++) {
			result[i][j] = matrix[j][i];
		}
	}
	return result;
}

// фукнция проверки перед операцией
void check(int* rows1, int* cols1, int* rows2, int* cols2) {
	if (*rows1 != *rows2 || *cols1 != *cols2) {
		printf("Error: Matrices have different dimensions\n");
		//return -1;
		exit(1);
	}
}

// Функция для вычисления определителя квадратной матрицы
int determinantOfMatrix(int** matrix, int n) {
	int det = 0;
	if (n == 1) {
		return matrix[0][0];
	}
	else if (n == 2) {
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	}
	else {
		int** temp = (int**)malloc((n - 1) * sizeof(int*));
		for (int i = 0; i < n - 1; i++) {
			temp[i] = (int*)malloc((n - 1) * sizeof(int));
		}
		for (int i = 0; i < n; i++) {
			int temp_i = 0, temp_j = 0;
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					if (j != 0 && k != i) {
						temp[temp_i][temp_j++] = matrix[j][k];
						if (temp_j == n - 1) {
							temp_i++;
							temp_j = 0;
						}
					}
				}
			}
			int sign = (i % 2 == 0) ? 1 : -1;
			det += sign * matrix[0][i] * determinantOfMatrix(temp, n - 1);
		}
		for (int i = 0; i < n - 1; i++) {
			free(temp[i]);
		}
		free(temp);
	}
	return det;
}

void checkoperation(char operation) {
	if (operation != '+' || operation != '-' || operation != '*' || operation != 't' || operation != 'd') {
		printf("wrond operation\n");
		return -1;
	}
}

void writeResultToFile(int** result, int* rows, int* cols) {
	char filename[100];
	time_t current_time = time(NULL);
	time_t raw_time;
	struct tm* tm_info;
	time(&raw_time);
	tm_info = localtime(&raw_time);

	strftime(filename, 100, "Results/result__%d_%m_%Y__%H_%M_%S.txt", tm_info);
	FILE* file = fopen(filename, "w");

	if (file == NULL) {
		printf("unsucces");
		return;
	}
	for (int i = 0; i < *rows; i++) {
		for (int j = 0; j < *cols; j++) {
			fprintf(file, "%d ", result[i][j]);
		}
		fprintf(file, "\n");
	}
	fclose(file);
	printf("success: %s\n", filename);
}

void writeResultofDeterminant(int result) {
	char filename[100];
	time_t current_time = time(NULL);
	time_t raw_time;
	struct tm* tm_info;
	time(&raw_time);
	tm_info = localtime(&raw_time);
	strftime(filename, 100, "Results/result__%d_%m_%Y__%H_%M_%S.txt", tm_info);
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		printf("unsucces");
		return;
	}
	fprintf(file, "%d", result);
	fclose(file);
	printf("success: %s\n", filename);
}