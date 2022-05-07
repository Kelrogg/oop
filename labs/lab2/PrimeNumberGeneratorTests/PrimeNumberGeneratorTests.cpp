#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../PrimeNumberGenerator/PrimeNumberGenerator.h"

TEST_CASE("Correct upperBound")
{
	auto primeBelow25 = GeneratePrimeNumbersSet(25);
	REQUIRE(primeBelow25.size() == 9);

	auto primeBelow100 = GeneratePrimeNumbersSet(100);
	REQUIRE(primeBelow100.size() == 25);

	auto primeBelow1000 = GeneratePrimeNumbersSet(1000);
	REQUIRE(primeBelow1000.size() == 168);
}

TEST_CASE("Wrong max bound")
{
	REQUIRE_THROWS_AS(GeneratePrimeNumbersSet(MAX_BOUND + 1), std::out_of_range);
}

TEST_CASE("Wrong min bound")
{
	REQUIRE_THROWS_AS(GeneratePrimeNumbersSet(MIN_BOUND - 1), std::out_of_range);
}

TEST_CASE("Heavy case")
{
	auto const primes = GeneratePrimeNumbersSet(100000000);
	REQUIRE(primes.size() == 5761455);
}