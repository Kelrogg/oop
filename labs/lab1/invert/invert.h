#pragma once

using Matrix3x3 = std::array<std::array<double, 3>, 3>;

struct Args
{
	std::string inputFileName{};

	Args() {}

	Args(std::string inputFile)
	{
		this->inputFileName = inputFile;
	}
};

std::optional<Args> ParseParams(int argc, char* argv[]);

struct MatrixStep 
{
public:
	int x, y;
	int size;
	MatrixStep(int size);
	int GetX();
	int GetY();
	int GetSize();
	void SetX(int x);
	void SetY(int y);
	void IncY();
	void DecY();
	void IncX();
	void DecX();
	void Step(bool way);

private:
	void CheckOutOfRange();
};


int ReadMatrix(std::string fileName, Matrix3x3& matrix);

void PrintMatrix(const Matrix3x3& matrix);
double FindAddition(const Matrix3x3& A, int y, int x, int SIZE);
Matrix3x3 Invert(const Matrix3x3& matrix, int SIZE);