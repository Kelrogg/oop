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

bool BorNode::isTerm() const
{
	return term;
}