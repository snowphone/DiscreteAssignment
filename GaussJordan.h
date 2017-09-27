#ifndef _GAUSSJORDAN_H
#define _GAUSSJORDAN_H
#ifdef _MSC_VER
#pragma warning(disable : 4996)  
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
	static void(*setMatrix)(void*);

	double** matrix;
	unsigned int row, col;
}GaussJordan;

void setMatrix(GaussJordan * self) {

	printf("Matrix size: ");
	scanf("%d", &(self->row));
	self->col = self->row + 1;
	puts("input elements: ");
	self->matrix = (double**)malloc(sizeof(double*) * self->row);
	self->matrix[0] = (double*)malloc(sizeof(double) * self->row * self->col);
	for (int i = 1; i<self->row; ++i) {
		self->matrix[i] = self->matrix[i - 1] + self->col;
	}
	double* p = &(self->matrix[0][0]);
	for (int i = 0; i < self->row * self->col; i++)
	{
		scanf("%d", p++);
	}
}
void print(GaussJordan* self)
{
	for (int i = 0; i < self->row; i++)
	{
		for (int j = 0; j < self->col; j++)
		{
			printf("%d ", self->matrix[i][j]);
		}
		puts("");
	}
}

#endif // !_GAUSSJORDAN_H
