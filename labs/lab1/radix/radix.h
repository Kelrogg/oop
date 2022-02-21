#pragma once

#include <array>
#include <iostream>
#include <limits>
#include <unordered_map>

std::string IntToString(int n, int radix, bool& wasError);
int StringToInt(const std::string& str, int radix, bool& wasError);