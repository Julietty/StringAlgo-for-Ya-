#pragma once
#include "Base.h"
#include <map>

using std::string;
using std::map;
using std::shared_ptr;
using std::weak_ptr;

class TTrieNode {
private:
	std::vector<TStringID> terminal_;
	map<char,shared_ptr<TTrieNode>> edges;
	weak_ptr<TTrieNode> parentnode_;
	char parentsymbol_;
	size_t height_;
	weak_ptr<TTrieNode> suf_link_;
	weak_ptr<TTrieNode> hard_suf_link_; 
	TTrieNode();
	TTrieNode(weak_ptr<TTrieNode> parentnode, char parentsymbol, size_t height);
	shared_ptr<TTrieNode> next(char nextsymbol);
	void setEdge(char nextsymbol, shared_ptr<TTrieNode> nextnode);
	void maketerminal(TStringID id, bool allowsame);
	bool isEdge(char newchar) const;
	size_t height() const;
	char parentsymbol() const;
	weak_ptr<TTrieNode> parent() const;
	friend class TStaticTemplateMatcher; 
	friend class TDynamicTemplateMatcher;
	friend class TNaiveTemplateMatcher;
	friend class TTrie;
};

class TTrie{
protected:
	shared_ptr<TTrieNode> root_;
	bool allowsametemplates;
public:
	TTrie();

	shared_ptr<TTrieNode> getroot();
	shared_ptr<TTrieNode> addstring(const string &newstring, TStringID id);
	shared_ptr<TTrieNode> addReverseString(const string &newstring, TStringID id);
	
};
