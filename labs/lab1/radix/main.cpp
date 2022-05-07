#include "stdafx.h"
#include "radix.h"

int main(int argc, char* argv[])
{
	int radixOld, radixNew, num;
	std::string str;
	bool wasError = false;

	if (argc != 4)
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: radix.exe <source notation> <destination notation> <value>\n";
		return 1;
	}

	radixOld = StringToInt(argv[1], 10, wasError);
	if (wasError)
	{
		std::cout << "Invalid notation" << std::endl;
		return 1;
	}
	radixNew = StringToInt(argv[2], 10, wasError);
	if (wasError)
	{
		std::cout << "Invalid destination notation" << std::endl;
		return 1;
	}

	str = argv[3];
	num = StringToInt(str, radixOld, wasError);
	if (wasError)
	{
		std::cout << "Invalid number" << std::endl;
		return 1;
	}

	std::string resFinal = IntToString(num, radixNew, wasError);
	if (wasError)
	{
		std::cout << "Invalid destination radix" << std::endl;
		return 1;
	}
	std::cout << resFinal;

	return 0;
}
