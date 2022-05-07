#include "stdafx.h"
#include "Aho-Corasick.h"
#include "ExpandTemplate.h"

vector<string> GetMapKeys(map<string, string> const& params)
{
	vector<string> keys;

	for (auto it = std::begin(params); it != std::end(params); ++it)
	{
		keys.push_back((*it).first);
	}

	return keys;
}

map<string, string> SweepDiplicateKeys(map<string, string> const& params)
{
	map<string, string> res;

	for (auto it = std::begin(params); it != std::end(params); ++it)
	{
		if (it->first == "")
		{
			continue;
		}

		auto resIt = res.find(it->first);
		if (resIt == res.end())
		{
			res.insert(*it);
			continue;
		}
		if (resIt->second < it->second)
		{
			resIt->second = it->second;
		}
	}
	return res;
}

uint16_t RFind(vector<bool> const& vec) 
{
	for (auto it = vec.cend(), end = vec.cbegin(); it != end; --it)
	{
		if (*it)
		{
			return std::distance(it, vec.cbegin());
		}
	}
	return 0;
}

string ExpandTemplate(string const& tpl, map<string, string> const& params)
{
	AhoCorasick trie;
	string res;
	res.reserve(tpl.length());
	size_t searchPosition = 0;

	string state, pattern;
	vector<bool> terms;
	uint16_t termLength = 0;

	const vector<string> keys = GetMapKeys(SweepDiplicateKeys(params));
	trie.Init(keys);

	while (searchPosition < tpl.length())
	{
		if (trie.currentState->isTerm())
		{
			termLength = state.length();//trie.currentState->length;
		}

		trie.Step(tpl[searchPosition]);
		state.push_back(tpl[searchPosition]);

		if (!trie.nodeHas(tpl[searchPosition]))
		{
			uint16_t currLength = trie.currentState->length;
			uint16_t prefixLength = state.length() - currLength;

			if (termLength)
			{
				pattern = state.substr(0, termLength);
				res.append(params.at(pattern));
				//res.append(state.substr(termLength, prefixLength - termLength));
				//state = state.substr(prefixLength);
				
				// Откат. Перепроверка символов
				if (prefixLength > termLength)
				{
					searchPosition -= state.length() - termLength;
					trie.Reset();
					state.clear();
				}
				if (prefixLength == termLength)
				{
					state = state.substr(termLength);
				}
			}
			if (!termLength)
			{
				res.append(state.substr(0, prefixLength));
				state = state.substr(prefixLength);
			}
		
			termLength = 0;
		}

		++searchPosition;
	}

	if (state != "")
	{
		if (termLength) // Instead: params.find(pattern) != params.end()
		{
			pattern = state.substr(0, termLength);
			res.append(params.at(pattern));
		}
		res.append(state.substr(termLength));
	}

	return res;	
}