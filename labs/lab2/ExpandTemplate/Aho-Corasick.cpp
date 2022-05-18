#include "stdafx.h"
#include "BorTrie.h"
#include "Aho-Corasick.h"

AhoCorasick::AhoCorasick()
{
	root = shared_ptr<BorNode>(new BorNode);
	currentState = root;
}

void AhoCorasick::AddString(const string& str)
{
	shared_ptr<BorNode> currentNode = root;
	for (std::string::const_iterator it = str.cbegin(); it != str.cend(); ++it)
	{
		shared_ptr<BorNode> childNode = currentNode->GetLink(*it);
		if (!childNode)
		{
			childNode = shared_ptr<BorNode>(new BorNode(root));
			childNode->length = currentNode->length + 1;

			currentNode->links.emplace(*it, childNode);
		}

		currentNode = childNode;
	}
	currentNode->term = currentNode;
}

/* void AhoCorasick::UpdateTermsDownTrie(shared_ptr<BorNode> node)
{
	if (!node)
	{
		return;
	}
	node->term = node;

	// bfs
	queue<shared_ptr<BorNode>> q;
	q.push(node);
	while (!q.empty())
	{
		shared_ptr<BorNode> currentNode = q.front();
		q.pop();

		for (LinksMap::iterator iter = currentNode->links.begin();
			 iter != currentNode->links.end(); ++iter)
		{
			const char symbol = iter->first;
			shared_ptr<BorNode> child = iter->second;

			if (!child->isTerminal()) // TODO !!!
			{
				child->term = node;
				q.push(child);
			}
		}
	}
};*/

void AhoCorasick::Stitch()
{ // bfs
	queue<shared_ptr<BorNode>> q;
	q.push(root);

	while (!q.empty())
	{
		shared_ptr<BorNode> currentNode = q.front();
		q.pop();

		if (currentNode->isTerm())
		{
			currentNode->suffixLink = root;
		}

		for (LinksMap::const_iterator iter = currentNode->links.cbegin();
			 iter != currentNode->links.cend(); ++iter)
		{
			const char symbol = iter->first;
			shared_ptr<BorNode> child = iter->second;

			if (!child->isTerm())
			{
			    child->term = currentNode->term;
			}

			// Defining .suffixLink for the childnode
			shared_ptr<BorNode> tempNode = currentNode->suffixLink;
			while (tempNode)
			{
				shared_ptr<BorNode> suffixLinkCandidate = tempNode->GetLink(symbol);
				if (suffixLinkCandidate)
				{
					child->suffixLink = suffixLinkCandidate;
					break;
				}
				tempNode = tempNode->suffixLink;
			}

			q.push(child);
		}
	}
}

void AhoCorasick::Init(const vector<string>& params)
{
	for (auto it = std::begin(params); it != std::end(params); ++it)
	{
		AddString(*it);
	}
	Stitch();
}

/* string AhoCorasick::GetWord() const
{
	string res;
	LinksMap links;
	shared_ptr<BorNode> temp = currentState->term;

	while (temp)
	{
		links = temp->parent->links;
		auto it = std::find_if(std::begin(links), std::end(links), [temp](const std::pair<char, shared_ptr<BorNode>>& edge) {
			return edge.second == temp;
		});

		temp = temp->parent;
		res.push_back(it->first);
	}

	return res;
}*/

bool AhoCorasick::nodeHas(const char c) const
{
	return currentState->nodeHas(c);
}

bool AhoCorasick::Step(const char c)
{
	while (currentState)
	{
		shared_ptr<BorNode> candidate = currentState->GetLink(c);
		if (candidate)
		{
			currentState = candidate;
			return true;
		}
		currentState = currentState->suffixLink;
		if (currentState->wasTerm())
		{
			return false;
		}
	}
	currentState = root;
	return true;
}

bool AhoCorasick::isRoot() const 
{
	return currentState == root;
}

bool AhoCorasick::isTerm() const
{
	return currentState->isTerm();
}

void AhoCorasick::Reset()
{
	currentState = root;
}

/* void printTermsForCurrentState(Callback callback) const
	{
		if (currentState->isTerminal())
		{
			callback(words[currentState->out].c_str());
		}
		shared_ptr<BorNode> tempNode = currentState->term;
		while (tempNode)
		{
			callback(words[tempNode->out].c_str());
			tempNode = tempNode->term;
		}
	}*/

/* void search(const char* str, Callback callback)
{
	currentState = &root;
	for (; *str; ++str)
	{
		cout << *str << ':' << endl;
		step(*str);
		printTermsForCurrentState(callback);
	}
}*/
