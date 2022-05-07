#include "stdafx.h"
#include "invert.h"

std::optional<Args> ParseParams(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Received invalid params count\n"
				  << "Usage: invert.exe <matrix file1>" << std::endl;
		exit(1);
	}

	Args args(argv[1]);
	return args;
}

MatrixStep::MatrixStep(int size)
	{
		this->x = 0;
		this->y = 0;
		this->size = size;
	}
int MatrixStep::GetX() { return x; }
int MatrixStep::GetY() { return y; }
int MatrixStep::GetSize() { return size; }
void MatrixStep::SetX(int x)
	{
		this->x = x;
	}
void MatrixStep::SetY(int y)
	{
		this->y = y;
	}
void MatrixStep::IncY()
	{
		++(this->y);
		CheckOutOfRange();
	}
void MatrixStep::DecY()
	{
		--(this->y);
		CheckOutOfRange();
	}
void MatrixStep::IncX()
	{
		++(this->x);
		CheckOutOfRange();
	}
void MatrixStep::DecX()
	{
		--(this->x);
		CheckOutOfRange();
	}
void MatrixStep::Step(bool way)
	{
		++y;

		if (way)
		{
			++x;
		}
		if (!way)
		{
			--x;
		}
		CheckOutOfRange();
	}
void MatrixStep::CheckOutOfRange()
	{
		if (y >= size)
			y -= size;
		if (x < 0)
			x += size;
		if (x >= size)
			x -= size;
	}

int ReadMatrix(std::string fileName, Matrix3x3& matrix)
{
	// cout << fstream::app << endl;		1
	// cout << fstream::binary << endl;		4
	// cout << fstream::in << endl;			8
	// cout << fstream::out << endl;		16
	// cout << fstream::trunc << endl;		32

	std::ifstream fin(fileName);
	if (!fin.is_open())
	{
		std::cerr << "Failed to open " << fileName << std::endl;
		exit(1);
	}

	for (std::_Array_iterator row = matrix.begin(), end = matrix.end(); row != end; ++row)
	{
		for (std::_Array_iterator cell = row->begin(), end = row->end(); cell != end; ++cell)
		{
			fin >> *cell;
		}
	}

	return 0;
}

void PrintMatrix(const Matrix3x3& matrix)
{
	for (std::_Array_const_iterator row = matrix.cbegin(), end = matrix.cend(); row != end; ++row)
	{
		for (std::_Array_const_iterator cell = row->cbegin(), end = row->cend(); cell != end; ++cell)
		{
			std::cout << std::fixed << std::setprecision(3) << *cell << "\t";
		}
		std::cout << std::endl;
	}
}

double FindAddition(const Matrix3x3& A, int y, int x, int SIZE)
{
	if (x < 0 || y < 0 || x >= SIZE || y >= SIZE)
	{
		std::cerr << "Incorrect index\n";
		exit(2);
	}

	double res = 0;
	double positive = 1;
	double negative = 1;
	MatrixStep stepBwd(SIZE);
	MatrixStep stepFwd(SIZE);

	// Задаём начальное положение
	stepBwd.SetX(x);
	stepBwd.SetY(y);

	stepFwd.SetX(x);
	stepFwd.SetY(y);

	for (size_t _ = 0; _ < SIZE - 1; ++_)
	{
		stepBwd.Step(false);
		stepFwd.Step(true);
		negative *= A[stepBwd.GetY()][stepBwd.GetX()];
		positive *= A[stepFwd.GetY()][stepFwd.GetX()];
	}
	res = positive - negative;

	return res;
}

Matrix3x3 Invert(const Matrix3x3& matrix,
	int SIZE)
{
	Matrix3x3 inverseMatrix;
	double det = 0;

	// Find det with algebraic additions in first column of inverse matrix
	for (int x = 0; x < SIZE; ++x)
	{
		inverseMatrix[x][0] = FindAddition(matrix, 0, x, SIZE);
		det += inverseMatrix[x][0] * matrix[0][x];
	}
	if (!det)
	{
		std::cout << "Determinant = 0 => no inverseMatrix\n";
		exit(0);
	}
	// We need to "/ det" first column from stage "Find det"
	for (int x = 0; x < SIZE; ++x)
	{
		inverseMatrix[x][0] /= det;
	}

	// Continue filling inverseMatrix from row with index 1
	for (int y = 1; y < SIZE; ++y)
	{
		for (int x = 0; x < SIZE; ++x)
		{
			inverseMatrix[x][y] = FindAddition(matrix, y, x, SIZE) / det;
		}
	}

	return inverseMatrix;
}
