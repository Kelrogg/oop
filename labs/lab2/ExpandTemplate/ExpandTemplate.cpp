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

string ExpandTemplate(string const& tpl, map<string, string> const& params)
{
	AhoCorasick trie;
	string res;
	res.reserve(tpl.length());
	size_t searchPosition = 0;

	vector<string> keys = GetMapKeys(SweepDiplicateKeys(params));
	std::sort(keys.begin(), keys.end(), std::less<string>());
	trie.Init(keys);

	char symbol;
	bool forth;
	uint16_t termLength = 0;
	uint16_t prefixLength;
	string state, pattern;
	// TODO: IDLize this
	while (searchPosition < tpl.length() || state != "")
	{
		if (searchPosition < tpl.length())
			symbol = tpl[searchPosition];
		else
			symbol = 0;

		forth = trie.nodeHas(symbol);
		
		if (!forth)
		{
			termLength = trie.currentState->GetTermLength();

			if (termLength)
				res.append(params.at(state.substr(0, termLength)));
		}
		if (trie.Step(symbol))
		{
			state.push_back(symbol);
			++searchPosition;
		}
		if (!forth)
		{
			//termLength = trie.currentState->GetTermLength();
			//
			//if (termLength)
			//	res.append(params.at(state.substr(0, termLength)));

			//if (trie.Step(symbol))
			//{
			//	state.push_back(symbol);
			//	++searchPosition;
			//}

			prefixLength = state.length() - trie.currentState->GetLength();
			res.append(state.substr(termLength, prefixLength - termLength));
			state.erase(0, prefixLength);
		}
	}
	if (res != "" && res.back() == '\0')
		res.pop_back();

	return res;	
}