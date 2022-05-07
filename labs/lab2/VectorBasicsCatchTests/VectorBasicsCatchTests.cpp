#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../VectorBasics/VectorBasics.h"

TEST_CASE("Not sorted numbers vector")
{
	std::istringstream iss("5 54 1 2.3 1 -45.68");
	std::ostringstream oss;
	ReadAndPrintElementsMultipliedByMinElement(iss, oss);
	REQUIRE(oss.str() == "2086.662 -45.680 -45.680 -105.064 -228.400 -2466.720 \n");
}

TEST_CASE("Sorted numbers vector")
{
	std::istringstream iss("2 4 6 ");
	std::ostringstream oss;
	ReadAndPrintElementsMultipliedByMinElement(iss, oss);
	REQUIRE(oss.str() == "4.000 8.000 12.000 \n");
}

TEST_CASE("Revert sorted numbers vector")
{
	std::istringstream iss("8 6 5 4 3 2");
	std::ostringstream oss;
	ReadAndPrintElementsMultipliedByMinElement(iss, oss);
	REQUIRE(oss.str() == "4.000 6.000 8.000 10.000 12.000 16.000 \n");
}

TEST_CASE("Wrong numbers vector")
{
	std::istringstream iss("1 22 bukva 11");
	std::ostringstream oss;

	REQUIRE(oss.str() == "");
}

TEST_CASE("Empty vector")
{
	std::istringstream iss("");
	std::ostringstream oss;

	REQUIRE(oss.str() == "");
}