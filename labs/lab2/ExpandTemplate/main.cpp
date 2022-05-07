#include "stdafx.h"
#include "Aho-Corasick.h"
#include "ExpandTemplate.h"

struct Args
{
	string inputName;
	string outputName;
	map<string, string> templateParams;
};

optional<Args> ParseParams(int argc, char* argv[])
{
	if (argc < 3)
	{
		return std::nullopt;
	}

	for (char** args = argv; *args; ++args)
	{
		if (std::strlen(*args))
		{
			continue;
		}
		return std::nullopt;
	}

	Args args;
	args.inputName = argv[1];
	args.outputName = argv[2];

	std::pair<string, string> templateParams;
	for (char** arg = argv + 3; *arg; ++arg)
	{
		if (std::distance(argv, arg) % 2 != 0)
		{
			templateParams.first = *arg;
		}
		else
		{
			templateParams.second = *arg;
			args.templateParams.emplace(templateParams);
		}
	}

	return args;
}

void ReadFileAndPrintStringEmplacedByPattern(Args const& args)
{
	string finName = args.inputName;
	string foutName = args.outputName;

	string res, tpl;
	std::ifstream fin(finName);
	if (!fin.is_open())
	{
		throw std::ifstream::failure("cannot open file");
	}
	std::ofstream fout(foutName);
	if (!fout.is_open())
	{
		throw std::ofstream::failure("cannot open file");
	}

	fin >> tpl;
	res = ExpandTemplate(tpl, args.templateParams);
	fout << res;
}

int main(int argc, char* argv[])
{
	optional<Args> args = ParseParams(argc, argv);
	if (args == std::nullopt)
	{
		return 1;
	}

	try
	{
		ReadFileAndPrintStringEmplacedByPattern(args.value());
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}