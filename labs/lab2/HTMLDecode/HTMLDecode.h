#pragma once

#include <iostream>
#include <string>
#include <vector>

std::string FindReplacement(const std::string& html, size_t& replacementIndex);

std::string HtmlDecode(std::string const& html);