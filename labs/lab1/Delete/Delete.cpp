#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <queue>

template <typename T>
using Matrix100x100 = std::array<std::array<T, 100>, 100>;

using Coord = std::pair<uint16_t, uint16_t>;

struct Node
{
	int16_t _x, _y, _dist;
	Node(int16_t x, int16_t y, int16_t dist) {
		_x = x;
		_y = y;
		_dist = dist;
	};
};

const char START = 'A', END = 'B', WALL = '#', EMPTY = ' ', PATH = '.';

bool IsValid(const Matrix100x100<short>& mat, int16_t x, int16_t y)
{
	return (x >= 0 && x < mat.size()) && (y >= 0 && y < mat[0].size()) && mat[y][x];
}

int ReadLabyrinth(std::string const& fileName, Matrix100x100<short>& mat, Coord& src, Coord& dest)
{
	// cout << fstream::app << endl;		1
	// cout << fstream::binary << endl;		4
	// cout << fstream::in << endl;			8
	// cout << fstream::out << endl;		16
	// cout << fstream::trunc << endl;		32

	char c;
	std::ifstream fin(fileName);
	if (!fin.is_open())
	{
		std::cerr << "Failed to open " << fileName << std::endl;
		exit(1);
	}

	for (size_t line = 0; line < mat.size(); ++line)
	{
		size_t lineSize = mat[line].size();
		for (size_t cell = 0; cell < lineSize; ++cell)
		{
			fin.get(c);
			if (c == '\n')
			{
				break;
			}
			mat[line][cell] = c;

			if (c == START)
			{
				src = std::make_pair(cell, line);
			}
			if (c == END)
			{
				dest = std::make_pair(cell, line);
			}
		}
	}

	return 0;
}

void PrintLabyrinth(Matrix100x100<short> const& mat, std::string const& outputFileName)
{
	std::ofstream fout(outputFileName);

	for (auto row = mat.begin(); row < mat.end(); ++row)
	{
		for (auto cell = row->begin(); (*cell) && (*cell != '\n') && cell < row->end(); ++cell)
		{
			if ((*cell) > 255)
			{
				fout << EMPTY;
				continue;
			}
			fout << static_cast<char>(*cell);
		}
		fout << std::endl;
	}
}

int Lee(Matrix100x100<short>& mat, Coord& src, Coord& dest)
{
	std::array<int16_t, 4> dx = { -1, 0, 0, 1 };
	std::array<int16_t, 4> dy = { 0, -1, 1, 0 };

	std::queue<Node> q;

	int16_t x = dest.first;
	int16_t y = dest.second;

	mat[y][x] = INT16_MAX;
	q.push({ x, y, INT16_MAX });

	while (!q.empty())
	{
		Node node = q.front();
		q.pop();

		int16_t x = node._x, y = node._y, dist = node._dist;
		for (uint8_t _ = 0; _ < 4; ++_)
		{
			int16_t xx = x + dx[_];
			int16_t yy = y + dy[_];

			if (xx == src.first && yy == src.second)
				return 0;

			if (IsValid(mat, xx, yy) && mat[yy][xx] == EMPTY)
			{
				mat[yy][xx] = dist - 1;

				q.push({ xx, yy, dist - 1});
			}
		}
	}

	return 1;
}

void RestorePath(Matrix100x100<short>& mat, Coord& src, Coord& dest)
{
	std::array<int16_t, 4> dx = { -1, 0, 0, 1 };
	std::array<int16_t, 4> dy = { 0, -1, 1, 0 };

	int16_t x = src.first;
	int16_t y = src.second;

	while (dest.first != x || dest.second != y)
	{
		for (uint8_t _ = 0; _ < 4; ++_)
		{
			int16_t xx = x + dx[_];
			int16_t yy = y + dy[_];

			if (IsValid(mat, xx, yy) && (mat[yy][xx] > mat[y][x]))
			{
				if (mat[yy][xx] == INT16_MAX)
				{
					mat[yy][xx] = END;
					mat[src.second][src.first] = START;
					return;
				}

				mat[y][x] = PATH;
				y = yy;
				x = xx;
				break;
			}
		}
	}
}

int main()
{
	Matrix100x100<short> A{};
	Coord src, dest;
	std::string finName = "labyrinth-1.txt";
	std::string foutName = "labyrinth-1-result.txt";
	
	ReadLabyrinth(finName, A, src, dest);
	Lee(A, src, dest);

	RestorePath(A, src, dest);

	PrintLabyrinth(A, foutName);
}