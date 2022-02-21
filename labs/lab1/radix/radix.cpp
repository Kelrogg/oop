#include <iostream>
#include <limits>
#include "stdafx.h"
#include <unordered_map>
#include <array>

std::unordered_map<char, int> dict{
	{ '0', 0 },
	{ '1', 1 },
	{ '2', 2 },
	{ '3', 3 },
	{ '4', 4 },
	{ '5', 5 },
	{ '6', 6 },
	{ '7', 7 },
	{ '8', 8 },
	{ '9', 9 },
	{ 'A', 10 },
	{ 'B', 11 },
	{ 'C', 12 },
	{ 'D', 13 },
	{ 'E', 14 },
	{ 'F', 15 },
	{ 'G', 16 },
	{ 'H', 17 },
	{ 'I', 18 },
	{ 'J', 19 },
	{ 'K', 20 },
	{ 'L', 21 },
	{ 'M', 22 },
	{ 'N', 23 },
	{ 'O', 24 },
	{ 'P', 25 },
	{ 'Q', 26 },
	{ 'R', 27 },
	{ 'S', 28 },
	{ 'T', 29 },
	{ 'U', 30 },
	{ 'V', 31 },
	{ 'W', 32 },
	{ 'X', 33 },
	{ 'Y', 34 },
	{ 'Z', 35 }
};
std::array<char, 36> Rrr{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 
'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'V', 'X',  'Y', 'Z' };

// true => Overflow
bool CheckIntOverFlow(int num, int radix, int digit)
{
	return (num > (std::numeric_limits<int>::max() - digit) / radix);
}

// Translation: radix - основание
int StringToInt(const std::string& str, int radix, bool& wasError)
{
	//  if (str.empty())
	//  {
	//  	wasError = true;
	//  	return 1;
	//  }

	bool minus = false;
	int result = 0;
	char currCh;

	if (radix < 2 || radix > 35)
	{
		wasError = true;
		return 1;
	}

	for (size_t i = 0; i < str.size(); ++i)
	{
		currCh = std::toupper(str[i]);

		if (dict.find(currCh) != dict.end() && dict[currCh] < radix)
		{
			if (CheckIntOverFlow(result, radix, dict[currCh]))
			{
				wasError = true;
				return 0;
			}

			result = result * radix + dict[currCh];
			continue;
		}

		if (i == 0 && currCh == '-')
		{
			minus = true;
			continue;
		}

		wasError = true;
		return 0;
	}

	if (minus)
		return -result;
	return result;
};

std::string IntToString(int n, int radix, bool& wasError)
{
	std::string str;

	if (radix < 2 || radix > 35)
	{
		wasError = true;
		return "";
	}
	if (n < 0)
		str.insert(str.begin(), '-');

	while (n)
	{
		str.insert(str.begin(), Rrr[abs(n % radix)]);
		n /= radix;
	}

	return str;
};
