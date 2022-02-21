// crypt.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "stdafx.h"

#pragma pack(push, 1)
struct bitsDivider
{
	unsigned one : 1;
	unsigned two : 1;
	unsigned three : 1;
	unsigned four : 1;
	unsigned five : 1;
	unsigned six : 1;
	unsigned seven : 1;
	unsigned eight: 1;
};
#pragma pack(pop)
// sizeof(bitsDivider) = 1 !!!
// Почему не работают ни unsigned int, ни unsigned char

union charDivider
{
	char symbol;
	bitsDivider bitChar;
};

void shuffleBits(charDivider &cd)
{
	// swap(eight, five)
	char temp = cd.bitChar.eight;
	cd.bitChar.eight = cd.bitChar.five;
	cd.bitChar.five = temp;

	// swap(four, one)
	temp = cd.bitChar.four;
	cd.bitChar.four = cd.bitChar.one;
	cd.bitChar.one = temp;

	// swap(seven, six)
	temp = cd.bitChar.seven;
	cd.bitChar.seven = cd.bitChar.six;
	cd.bitChar.six = temp;

	// swap(three, two)
	temp = cd.bitChar.three;
	cd.bitChar.three = cd.bitChar.two;
	cd.bitChar.two = temp;
}

void reshuffleBits(charDivider &cd)
{
	// swap(eight, five)
	char temp = cd.bitChar.eight;
	cd.bitChar.eight = cd.bitChar.five;
	cd.bitChar.five = temp;

	// swap(four, one)
	temp = cd.bitChar.four;
	cd.bitChar.four = cd.bitChar.one;
	cd.bitChar.one = temp;

	// swap(seven, six)
	temp = cd.bitChar.seven;
	cd.bitChar.seven = cd.bitChar.six;
	cd.bitChar.six = temp;

	// swap(three, two)
	temp = cd.bitChar.three;
	cd.bitChar.three = cd.bitChar.two;
	cd.bitChar.two = temp;
}

void writeEncrypted(std::istream& inputFile, std::ostream& outputFile, char key)
{
	charDivider cd;
	while (1)
	{
		inputFile.get(cd.symbol);
		if (!inputFile)
			break;
		cd.symbol ^= key;
		shuffleBits(cd);
		outputFile << cd.symbol;
	}
}

void writeDecrypted(std::istream& inputFile, std::ostream& outputFile, char key)
{
	charDivider cd;
	while (1)
	{
		inputFile.get(cd.symbol);
		if (!inputFile)
			break;

		reshuffleBits(cd);
		cd.symbol ^= key;

		outputFile << cd.symbol;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: crypt.exe crypt <input file> <output file> <key> \n";
		return 1;
	}
	std::string method = argv[1];

	if (method != "crypt" && method != "decrypt")
	{
		std::cout << "Failed to read method " << argv[1] << std::endl;
		std::cout << "(first argument can be crypt/decrypt)" << std::endl;
		return 1;
	}

	std::ifstream inputFile(argv[2], std::ios::binary);

	if (!inputFile.is_open())
	{
		std::cout << "Failed to open " << argv[2] << " for reading\n";
		return 1;
	}

	std::ofstream outputFile(argv[3], std::ios::binary);

	if (!outputFile.is_open())
	{
		std::cout << "Failed to open " << argv[3] << " for reading\n";
		return 1;
	}

	// key
	if (static_cast<std::string>(argv[4]).size() >= 3)
	{
		std::cout << "Key must be in range 0..255" << std::endl;
		return 1;
	}
	
	int str = std::stoi(argv[4]);	//	Since c++11

	if (str < 0 || str > 255)
	{
		std::cout << "Key must be in range 0..255" << std::endl;
		return 1;
	}
	char key = str;

	if (method == "crypt")
	{
		writeEncrypted(inputFile, outputFile, key);	// Two functions to avoid checking string every input symbol
	}
	if (method == "decrypt")
	{
		writeDecrypted(inputFile, outputFile, key);	// Two functions to avoid checking string every input symbol
	}
	
	return 0;
}