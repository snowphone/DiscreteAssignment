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
//가우스-조던 소거법 사용. 
void Solve(GaussJordan* self)
{
	//모든 대각성분이 0이 아닌지 확인하고, 
	//0인 경우, 그 아래 행들중에서 하나를 골라 그 행을 현재 행에 더한다.
	for (int diagonal = 0; diagonal < self->row; diagonal++)
	{
		if (!self->matrix[diagonal][diagonal])
		{
			for (int r = diagonal+1; r < self->row; r++)
			{
				if (self->matrix[r][diagonal])
				{
					//diagonal행 += r행
					for (int c = 0; c < self->column; c++)
					{
						self->matrix[diagonal][c] += self->matrix[r][c];
					}
					break;
				}
			}
		}
	}




	
	//[0,rowInit) 까지는 가우스 소거법 완료
	for (int diagonal = 0; diagonal < self->row; diagonal++)
	{
		//대각성분이 1이 되도록 그 행에 대해 연산한다.
		double multiplier = self->matrix[diagonal][diagonal];

		for (int c = diagonal; c < self->column; c++) { self->matrix[diagonal][c] /= multiplier; }

		//나머지 행의 rowInit열을 0으로 만드는 연산을 진행한다.
		for (int r = diagonal+1; r < self->row; r++)
		{
			//multiplier을 구한다.
			multiplier = self->matrix[r][diagonal] / self->matrix[diagonal][diagonal];

			//rowInit 이후 행에 대해서 대각성분 이전의 성분을 0으로 만든다.
			for (int c = diagonal; c < self->column; c++)
			{
				self->matrix[r][c] -= multiplier * self->matrix[diagonal][c];
			}

		}
	}

	//Gordan 소거법 사용
	//대각성분을 지정
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
