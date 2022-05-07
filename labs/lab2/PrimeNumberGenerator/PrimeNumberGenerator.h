#pragma once

#include "stdafx.h"

constexpr int MIN_BOUND = 2;
constexpr int MAX_BOUND = 100000000;

using Sieve = std::vector<bool>;
using std::set;

std::set<int> GeneratePrimeNumbersSet(int upperBound);

std::optional<int> ParseParams(int argc, char* argv[]);

void PrintPrimes(std::ostream& output, std::set<int> const& primes);