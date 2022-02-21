#include "stdafx.h"
#include "radix.h"

int main(int argc, char* argv[])
{
	int radixOld, radixNew, num;
	std::string str;
	bool wasError;

	if (argc != 4)
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: radix.exe <source notation> <destination notation> <value>\n";
		return 1;
	}

	radixOld = StringToInt(argv[1], 10, wasError);
	radixNew = StringToInt(argv[2], 10, wasError);
	str = argv[3];

	num = StringToInt(str, radixOld, wasError);
	if (wasError)
	{
		std::cout << "Invalid number" << std::endl;
		return 1;
	}

	std::cout << IntToString(num, radixNew, wasError) << std::endl;
	if (wasError)
	{
		std::cout << "Invalid destination radix" << std::endl;
		return 1;
	}

	return 0;
}
