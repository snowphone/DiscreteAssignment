#ifndef _GAUSSJORDAN_H
#define _GAUSSJORDAN_H

#ifdef _MSC_VER
#pragma warning(disable : 4996)  
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef float Type;
typedef struct {
	//static void(*Set)(void*);

	Type** matrix;
	unsigned int row, column;
}GaussJordan;


void Print(GaussJordan* self)
{
	puts("output result: ");
	for (int i = 0; i < self->row; i++)
	{
		for (int j = 0; j < self->column; j++)
		{
			printf("%g ", self->matrix[i][j]);
		}
		puts("");
	}
}
//���콺-���� �ҰŹ� ���. 
void Solve(GaussJordan* self)
{
	//��� �밢������ 0�� �ƴ��� Ȯ���ϰ�, 
	//0�� ���, �� �Ʒ� ����߿��� �ϳ��� ��� �� ���� ���� �࿡ ���Ѵ�.
	for (int diagonal = 0; diagonal < self->row; diagonal++)
	{
		if (!self->matrix[diagonal][diagonal])
		{
			for (int r = diagonal+1; r < self->row; r++)
			{
				if (self->matrix[r][diagonal])
				{
					//diagonal�� += r��
					for (int c = 0; c < self->column; c++)
					{
						self->matrix[diagonal][c] += self->matrix[r][c];
					}
					break;
				}
			}
		}
	}




	
	//[0,rowInit) ������ ���콺 �ҰŹ� �Ϸ�
	for (int diagonal = 0; diagonal < self->row; diagonal++)
	{
		//�밢������ 1�� �ǵ��� �� �࿡ ���� �����Ѵ�.
		double multiplier = self->matrix[diagonal][diagonal];

		for (int c = diagonal; c < self->column; c++) { self->matrix[diagonal][c] /= multiplier; }

		//������ ���� rowInit���� 0���� ����� ������ �����Ѵ�.
		for (int r = diagonal+1; r < self->row; r++)
		{
			//multiplier�� ���Ѵ�.
			multiplier = self->matrix[r][diagonal] / self->matrix[diagonal][diagonal];

			//rowInit ���� �࿡ ���ؼ� �밢���� ������ ������ 0���� �����.
			for (int c = diagonal; c < self->column; c++)
			{
				self->matrix[r][c] -= multiplier * self->matrix[diagonal][c];
			}

		}
	}

	//Gordan �ҰŹ� ���
	//�밢������ ����
	for (int diagonal = self->row - 1; diagonal >= 0; diagonal--)
	{
		for (int r = diagonal-1; r >= 0; r--)
		{
			double multiplier = self->matrix[r][diagonal] / self->matrix[diagonal][diagonal];
			self->matrix[r][diagonal] -= multiplier * self->matrix[diagonal][diagonal];
			self->matrix[r][self->column-1] -= multiplier * self->matrix[diagonal][self->column-1];
		}
	}

}
void Set(GaussJordan * self)
{

	printf("Matrix size: ");
	scanf("%u", &(self->row));
	self->column = self->row + 1;
	puts("input elements: ");
	self->matrix = (Type**)malloc(sizeof(Type*) * self->row);
	self->matrix[0] = (Type*)malloc(sizeof(Type) * self->row * self->column);
	for (int i = 1; i < self->row; ++i) {
		self->matrix[i] = self->matrix[i - 1] + self->column;
	}
	Type* p = &(self->matrix[0][0]);
	for (int i = 0; i < self->row * self->column; i++)
	{
		scanf("%f", p++);
	}
}


#endif // !_GAUSSJORDAN_H
