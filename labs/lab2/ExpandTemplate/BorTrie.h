#pragma once

#include "stdafx.h"

// Следующий класс может быть целесообразно поместить внутрь автомата среди приватных полей.

class BorNode
{
public:
	// TODO Unordered_map doesn`t work
	map<const char, shared_ptr<BorNode>> links;
	shared_ptr<BorNode> suffixLink;
	shared_ptr<BorNode> term;
	uint16_t length;

	shared_ptr<BorNode> GetLink(const char c) const;
	uint16_t GetTermLength() const;
	uint16_t GetLength() const;
	bool nodeHas(const char c) const;
	bool wasTerm() const;
	bool isTerm() const;

	BorNode(shared_ptr<BorNode> suffixLink = nullptr)
		: suffixLink(suffixLink)
		, term(nullptr)
		, length(0)
	{
	}
};

using LinksMap = map<const char, shared_ptr<BorNode>>;