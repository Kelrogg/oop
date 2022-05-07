// Replace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	size_t pos = 0;
	std::string result;
	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);
		result.append(subject, pos, foundPos - pos);
		if (foundPos != std::string::npos)
		{
			result.append(replacementString);
			pos = foundPos + searchString.length();
		}
		else
		{
			break;
		}
	}
	return result;
}

void CopyFileWithReplace(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;

	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << "\n";
	}
}

int main(int argc, char* argv[])
{
	if (argc != 5 && argc != 4)
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: replace.exe <inputFile> <outputFile> <searchString> (<replacementString>)\n";
		return 1;
	}

	std::ifstream inputFile(argv[1]);

	// вызываем метод is_open() у объекта input,
	// который вернет true, если файл был открыт
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}

	std::ofstream outputFile(argv[2]);

	if (!outputFile.is_open())
	{
		std::cout << "Failed to open " << argv[2] << " for output\n";
		return 1;
	}

	std::string searchString = argv[3];
	std::string replacementString = "";
	if (argc == 5)
		replacementString = argv[4];

	CopyFileWithReplace(inputFile, outputFile, searchString, replacementString);
	outputFile.flush(); // опционально - можешь убрать

	return 0;
}
