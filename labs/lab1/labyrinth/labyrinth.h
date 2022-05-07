#pragma once
#include "stdafx.h"

using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::array;
using std::queue;
using std::string;
using std::make_pair;

template <typename T>
using Matrix100x100 = std::array<std::array<T, 100>, 100>;

using Coord = pair<int16_t, int16_t>;

struct Node
{
	int16_t _x, _y, _dist;
	Node(int16_t x, int16_t y, int16_t dist);
};
struct Args
{
	std::string _inputFileName{};
	std::string _outputFileName{};

	Args() {}

	Args(const std::string& inputFile, const std::string& outputFile)
	{
		_inputFileName = inputFile;
		_outputFileName = outputFile;
	}
};

std::optional<Args> ParseParams(int argc, char* argv[]);

int ReadLabyrinth(string const& fileName, Matrix100x100<short>& mat, Coord& src, Coord& dest);

int Lee(Matrix100x100<short>& mat, Coord& src, Coord& dest);

void RestorePath(Matrix100x100<short>& mat, Coord& src);

void Labyrinth(string const& inputFileName, string const& outputFileName);

void PrintLabyrinth(Matrix100x100<short> const& mat, string const& outputFileName);
