#include "trie.h"
	TTrieNode::TTrieNode():terminal_(),edges(),parentnode_(),parentsymbol_(),
		height_(),suf_link_(), hard_suf_link_() {
	}
	TTrieNode::TTrieNode(weak_ptr<TTrieNode> parentnode, char parentsymbol, size_t height):terminal_(),
		edges(),parentnode_(parentnode),parentsymbol_(parentsymbol),height_(height),
		suf_link_(), hard_suf_link_()  {
	}
	shared_ptr<TTrieNode> TTrieNode::next(char nextsymbol) {
		return edges[nextsymbol];
	}
	void TTrieNode::setEdge(char nextsymbol, shared_ptr<TTrieNode> nextnode) {
		if (edges.count(nextsymbol)) 
			throw std::logic_error("Trie edge override");
		else edges[nextsymbol] = nextnode;
	}
	void TTrieNode::maketerminal(TStringID id, bool allowsame) {
		if (!terminal_.empty() && !allowsame) 
			throw std::logic_error("string already exists");
		terminal_.push_back(id);
	}

	bool TTrieNode::isEdge(char newchar) const {
		return edges.count(newchar);
	}
	size_t TTrieNode::height() const {
		return height_;
	}
	char TTrieNode::parentsymbol() const {
		return parentsymbol_;
	}
	weak_ptr<TTrieNode> TTrieNode::parent() const  {
		return parentnode_;
	}


	TTrie::TTrie():root_(new TTrieNode()), allowsametemplates(false) {
	}
	shared_ptr<TTrieNode> TTrie::getroot() {
		return root_;
	}
	shared_ptr<TTrieNode> TTrie::addstring(const string& newstring, TStringID id) {
		shared_ptr<TTrieNode> currentnode = getroot();
		for (size_t curpos = 0; curpos < newstring.length(); ++curpos) {
			if (currentnode->isEdge(newstring[curpos])) {
				currentnode = currentnode->next(newstring[curpos]);
			}
			else {
				currentnode->setEdge(newstring[curpos],shared_ptr<TTrieNode>(new TTrieNode(currentnode, newstring[curpos],currentnode->height() + 1)));
				currentnode = currentnode->next(newstring[curpos]);  
			}
		}
		currentnode->maketerminal(id,allowsametemplates);
		return currentnode;
	}
	shared_ptr<TTrieNode> TTrie::addReverseString(const string& newstring, TStringID id) {
		shared_ptr<TTrieNode> currentnode = getroot();
		for (size_t curpos = newstring.length(); curpos > 0; --curpos) {
			if (currentnode->isEdge(newstring[curpos - 1])) 
				currentnode = currentnode->next(newstring[curpos - 1]);
			else {
				currentnode->setEdge(newstring[curpos - 1],shared_ptr<TTrieNode>(new TTrieNode(currentnode, newstring[curpos - 1],currentnode->height() + 1)));
				currentnode = currentnode->next(newstring[curpos - 1]);  
			}
		}
		currentnode->maketerminal(id, allowsametemplates);
		return currentnode;
	}