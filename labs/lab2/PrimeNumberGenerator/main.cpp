#include "PrimeNumberGenerator.h"
#include "stdafx.h"

int main(int argc, char** argv)
{
	std::optional<int> args = ParseParams(argc, argv);

	if (args == std::nullopt)
	{
		return 1;
	}

	try
	{
		set<int> const primes = GeneratePrimeNumbersSet(args.value());
		PrintPrimes(std::cout, primes);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}
