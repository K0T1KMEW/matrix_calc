#pragma once

#include <stdio.h>
#include <malloc.h>
#include "func.h"
#include <direct.h>
#include <stdlib.h>
#include <time.h>

int** readMatrixFromFile(const char* filename, int* rows, int* cols);

void printMatrix(int** matrix, int* rows, int* cols);

int** addMatrices(int** matrix1, int** matrix2, int* rows, int* cols);

int** disMatrices(int** matrix1, int** matrix2, int* rows, int* cols);

int** multiplyMatrices(int** matrix1, int* rows1, int* cols1, int** matrix2, int* rows2, int* cols2);

int** transposition(int** matrix, int* rows, int* cols);

void check(int* rows1, int* cols1, int* rows2, int* cols2);

int determinantOfMatrix(int** matrix, int n);

void checkoperation(char operation);

void freememory(int** matrix1, int** matrix2, int** result, int* rows);

void writeToTxtFile(int** array, int rows, int cols, const char* fileName);

void writeResultToFile(int** result, int* rows, int* cols);

void writeResultofDeterminant(int result);
