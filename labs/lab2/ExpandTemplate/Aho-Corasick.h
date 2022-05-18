#pragma once

#include "BorTrie.h"

class AhoCorasick
{
public:
	typedef void (*Callback)(const char* substr);
	shared_ptr<BorNode> root;
	shared_ptr<BorNode> currentState;

	AhoCorasick();
	void AddString(const string& str);
	// обновить ссылки на ближайшее терминальное состояние вниз по дереву
	// сгодится при добавлении короткого слова
	// void UpdateTermsDownTrie(BorNode* currentNode);
	void Stitch();
	void Init(const vector<string>& params);
	bool Step(const char c);
	bool nodeHas(const char c) const;
	bool isRoot() const;
	bool isTerm() const;
	void Reset();
};