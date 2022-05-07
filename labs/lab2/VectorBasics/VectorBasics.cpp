#include "stdafx.h"
#include "VectorBasics.h"

void ReadAndPrintElementsMultipliedByMinElement(std::istream& inStream, std::ostream& outStream)
{
	auto vec = ReadNumbers(inStream);
	if (!vec.has_value()) 
	{
		throw std::invalid_argument("Wrong numbers");
	}

	MultiplyVectorElementsByMinElement(vec.value());
	PrintVector(outStream, vec.value());
}

void MultiplyVectorElementsByMinElement(std::vector<float>& vec)
{
	std::sort(vec.begin(), vec.end());

	auto it = std::begin(vec);
	float min = *it;

	std::transform(vec.begin(), vec.end(), vec.begin(), [&min](const float element) { return element * min; });
}

void PrintVector(std::ostream& outStream, const std::vector<float>& vec)
{
	for (auto it = vec.cbegin(); it != vec.cend(); ++it)
	{
		outStream << std::fixed << std::setprecision(3) << *it << " ";
	}
	outStream << std::endl;
}

std::optional<std::vector<float>> ReadNumbers(std::istream& inStream)
{
	std::vector<float> vec;

	std::copy(std::istream_iterator<float>(inStream), std::istream_iterator<float>(), std::back_inserter(vec));

	return { vec };
}
