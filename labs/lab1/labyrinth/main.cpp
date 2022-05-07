#include "stdafx.h"
#include "labyrinth.h"

int main(int argc, char* argv[])
{
	std::optional<Args> args;
	args = ParseParams(argc, argv);

	Labyrinth(args->_inputFileName, args->_outputFileName);

	return 0;
}