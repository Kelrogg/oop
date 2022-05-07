#pragma once

#include "stdafx.h"

void ReadAndPrintElementsMultipliedByMinElement(std::istream& inStream, std::ostream& outStream);

void MultiplyVectorElementsByMinElement(std::vector<float>& vec);
void PrintVector(std::ostream& outStream, const std::vector<float>& vec);
std::optional<std::vector<float>> ReadNumbers(std::istream& inStream);
