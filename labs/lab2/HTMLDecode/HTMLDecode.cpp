#include "HTMLDecode.h"
#include "stdafx.h"

const char TEMPLATES_START = '&';

const Dictionary TEMPLATES = {
	{ "&quot;", "\"" },
	{ "&apos;", "'" },
	{ "&lt;", "<" },
	{ "&gt;", ">" },
	{ "&amp;", "&" },
};

string FindReplacement(const string& html, size_t& replacementIndex)
{
	// TODO C++1z
	for (const auto& [candidate, replacement]: TEMPLATES)
	{
		if (html.compare(replacementIndex, candidate.length(), candidate) == 0)
		{
			replacementIndex += candidate.length();
			return replacement;
		}
	}

	++replacementIndex;
	return { TEMPLATES_START };
}

string HtmlDecode(string const& html)
{
	string result;
	size_t searchIndex = 0;
	while (searchIndex < html.length())
	{
		size_t replacementIndex = html.find(TEMPLATES_START, searchIndex);
		result.append(html, searchIndex, replacementIndex - searchIndex);

		if (replacementIndex == string::npos)
			break;

		string pattern = FindReplacement(html, replacementIndex);
		result.append(pattern);
		searchIndex = replacementIndex;
	}

	return result;
}