#include "PrimeNumberGenerator.h"
#include "stdafx.h"

set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound < MIN_BOUND || upperBound > MAX_BOUND)
	{
		throw std::out_of_range("Invalid upper bound value");
	}

	set<int> result;
	Sieve isPrime(upperBound + 1, true);

	result.insert(2);
	const double sizeSquareRoot = std::sqrt(isPrime.size());

	for (int i = 3; i < isPrime.size(); i += 2)
	{
		if (isPrime[i])
		{
			result.insert(i);

			if (i < sizeSquareRoot)
			{
				for (size_t j = i * i; j < isPrime.size(); j += i)
				{
					isPrime[j] = false;
				}
			}
		}
	}

	return result;
}

std::optional<int> ParseParams(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Received invalid params count\n"
				  << "Usage: PrimeNumberGenerator.exe <upperBound>" << std::endl;
		exit(1);
	}

	int args;
	try
	{
		args = std::stoi(argv[1]);
	}
	catch (const std::exception&)
	{
		std::cerr << "Invalid upper bound" << std::endl;
		return std::nullopt;
	}

	return args;
}

void PrintPrimes(std::ostream& output, std::set<int> const& primes)
{
	std::copy(primes.begin(), primes.end(), std::ostream_iterator<int>(output, " "));
	output << std::endl;
}
