#pragma once
#include "Base.h"
#include <deque>

using std::string;


class TSingleTemplateMatcher:public IMetaTemplateMatcher {
private:
	unsigned long long actioncount;
	bool initialized;
	std::deque<char> substr_;
	std::deque<size_t> p_func_values;
	ptrdiff_t currentvalue; 
	size_t p_func(size_t pi_prev, char ch);
	void handlesymbol(TMatchResults &Result, char ch, size_t shift, TStringID templateid);
public:
	TSingleTemplateMatcher();
	void AppendCharToTemplate(char c);
	void PrependCharToTemplate(char c);
	TStringID AddTemplate(const string &template_) override;
	TMatchResults MatchStream(ICharStream &stream) override;
	friend class TWildcardSingleTemplateMatcher;
};


class TWildcardSingleTemplateMatcher:public IMetaTemplateMatcher {
private:
	
	bool initialized;
	string substring;
	std::vector<TSingleTemplateMatcher> Matchers;
	std::vector<std::pair<size_t,size_t>> Parts_range;
public:
	TWildcardSingleTemplateMatcher();
	TStringID AddTemplate(const string &template_) override;
	TMatchResults MatchStream(ICharStream &stream) override;
};

