#include "GaussJordan.h"

int main() {
	GaussJordan matrix;
	Set(&matrix);
	Solve(&matrix);
	
	Print(&matrix);
}
