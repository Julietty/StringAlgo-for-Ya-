#pragma once
#include "Base.h"
#include "trie.h"
using std::shared_ptr;

class TNaiveTemplateMatcher:public IMetaTemplateMatcher {
private:
	TTrie templates;
	std::vector<string> substrings;
	size_t maxtemplatelength;
public:
	TNaiveTemplateMatcher();
	TStringID AddTemplate(const std::string &templatestr) override;
	TMatchResults MatchStream(ICharStream &stream) override;
};

