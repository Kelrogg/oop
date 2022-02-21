#include "invert.h"
#include <iomanip>

const int SIZE = 3;

struct DiagStep
{
	size_t x, y, size;
	DiagStep(size_t size)
	{
		this->x = 0;
		this->y = 0;
		this->size = size;
	}

	size_t getX() { return x; }

	size_t getY() { return y; }

	size_t getY() { return size; }

	int setX(size_t x) 
	{
		this->x = x;
		return 0;
	}

	int setY(size_t y)
	{
		this->y = y;
		return 0;
	}

	int makeStep(bool way)
	{
		if (way)
		{
			++x;
			++y;
			if (x >= size)
				x -= size;
			if (y >= size)
				y -= size;
		}
		if (!way)
		{
			--x;
			++y;
			if (x < 0)
				x += size;
			if (y >= size)
				y -= size;
		}

		return 0;
	}
};

int freeMemory(int** matrix) {
	for (size_t i = 0; i < SIZE; ++i)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

int findAddition(int** A, size_t y, size_t x, size_t SIZE)
{
	if (x < 0 || y < 0 || x >= SIZE || y >= SIZE)
	{
		std::cout << "Incorrect index" << std::endl;
		freeMemory(A);
		exit(2);
	}

	int res = 0;
	long double positive;
	long double negative;
	DiagStep stepBwd(SIZE);
	DiagStep stepFwd(SIZE);

	for (size_t i = 0; i < SIZE - 1; ++i)
	{
		negative, positive = A[0][i];
		stepFwd.setX(i);
		stepFwd.setY(0);
		stepBwd.setX(i);
		stepBwd.setY(0);

		for (size_t _ = 0; _ < SIZE - 1; ++_)
		{
			stepFwd.makeStep(true);
			stepBwd.makeStep(false);

			if (stepFwd.getY() == y)
				stepFwd.setY(y + 1);

			if (stepFwd.getX() == x)
				stepFwd.setX(x + 1);

			if (stepBwd.getY() == y)
				stepBwd.setY(y + 1);

			if (stepBwd.getX() == x)
				stepBwd.setX(x - 1);

			positive *= A[stepFwd.getY()][stepFwd.getX()];
			negative *= A[stepBwd.getY()][stepBwd.getX()];
		}
		res += positive - negative;
	}

	return res;
}

int main(int argc, char* argv[])
{
	long double det = 0;
	int** inverseMatrix = new int*[SIZE];
	for (size_t i = 0; i < SIZE; ++i)
	{
		inverseMatrix[i] = new int[SIZE];
	}
	
	// Allocate
	int** matrix = new int* [SIZE];
	for (size_t i = 0; i < SIZE; ++i)
	{
		matrix[i] = new int[SIZE];
	}

	// Find det with algebraic additions in first row of inverse matrix
	for (size_t x = 0; x < SIZE; ++x)
	{
		inverseMatrix[0][x] = findAddition(matrix, 0, x, SIZE);
		if (x&1)
		{
			det -= inverseMatrix[0][x] * matrix[0][x];
		}
		if (!x&1)
		{
			det += inverseMatrix[0][x] * matrix[0][x];
		}
	}
	if (!det)
	{
		std::cout << "Determinant = 0 => no inverseMatrix" << std::endl;
		freeMemory(matrix);
		freeMemory(inverseMatrix);
		return 0;
	}
	// Continue filling inverseMatrix form rows with index 1
	for (size_t y = 1; y < SIZE; ++y)
	{
		for (size_t x = 0; x < SIZE; ++x)
		{
			inverseMatrix[y][x] = findAddition(matrix, y, x, SIZE) / det;
		}
	}

	// Output
	for (size_t y = 0; y < SIZE; ++y)
	{
		for (size_t x = 0; x < SIZE; ++x)
		{
			std::cout << std::fixed << std::setprecision(3) << inverseMatrix[y][x] << "  ";
		}
		std::cout << std::endl;
	}

	freeMemory(matrix);
	freeMemory(inverseMatrix);
	// matrix = nullptr;
	return 0;
}
