#include "stdafx.h"
#include "invert.h"

const int SIZE = 3;

int main(int argc, char* argv[])
{
	std::optional<Args> args;
    args = ParseParams(argc, argv);

	Matrix3x3 matrix;
	ReadMatrix(args->inputFileName, matrix);

	Matrix3x3 inverseMatrix = Invert(matrix, SIZE);

	PrintMatrix(inverseMatrix);
	return 0;
}