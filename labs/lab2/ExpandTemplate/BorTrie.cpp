#include "stdafx.h"
#include "BorTrie.h"

shared_ptr<BorNode> BorNode::GetLink(const char c) const
{
	LinksMap::const_iterator iter = links.find(c);
	if (iter != links.cend())
	{
		return iter->second;
	}
	return nullptr;
}

uint16_t BorNode::GetLength() const
{
	return length;
}

uint16_t BorNode::GetTermLength() const
{
	if (term)
	{
	    return term->length;
	}
	return 0;
}

bool BorNode::nodeHas(const char c) const
	{
	// return currentState->links.contains(c); // Since C++20
	if (links.find(c) != links.cend())
	{
		return 1;
	}
	return 0;
}

bool BorNode::wasTerm() const
{
	if (this && this->term)
	{
		return true;
	}
	return false;
}

bool BorNode::isTerm() const
{
	return this == term.get();
}