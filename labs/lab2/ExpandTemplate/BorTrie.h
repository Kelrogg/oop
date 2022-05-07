#pragma once

#include "stdafx.h"

// Следующий класс может быть целесообразно поместить внутрь автомата среди приватных полей.

class BorNode
{
public:
	// TODO Unordered_map doesn`t work
	map<const char, shared_ptr<BorNode>> links;
	shared_ptr<BorNode> parent;
	shared_ptr<BorNode> suffixLink;
	uint16_t length;
	shared_ptr<BorNode> term;

	shared_ptr<BorNode> GetLink(const char c) const;
	bool isTerm() const;

	BorNode(shared_ptr<BorNode> suffixLink = nullptr)
		: suffixLink(suffixLink)
		, term(false)
		, length(0)
	{
	}
};

using LinksMap = map<const char, shared_ptr<BorNode>>;