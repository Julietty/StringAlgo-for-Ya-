#pragma once
#include "Base.h"
#include <map>
#include "trie.h"


class TStaticTemplateMatcher:public IMetaTemplateMatcher, private TTrie {
private:
	weak_ptr<TTrieNode> moveto(weak_ptr<TTrieNode> node, char symbol);
	weak_ptr<TTrieNode> suf_link_move(weak_ptr<TTrieNode> node);
	weak_ptr<TTrieNode> hard_suf_link_move(weak_ptr<TTrieNode> node); 
	std::vector<size_t> template_lengths; 
	shared_ptr<TTrieNode> sink;
	weak_ptr<TTrieNode> currentnode;
	bool used;
	void Handlesymbol(char ch, TMatchResults& ans, size_t &pos);
	void AllowSameTemplates();
public:
	TStaticTemplateMatcher();
	size_t size() const;
	TStringID AddTemplate(const std::string &templatestr) override;
	TMatchResults MatchStream(ICharStream &stream) override;
	friend class TDynamicTemplateMatcher;
	friend class T2DSingleTemplateMatcher;
};

class TDynamicTemplateMatcher:public IMetaTemplateMatcher {
private:
	std::vector<std::vector<TStaticTemplateMatcher>> Matchers;
	std::vector<std::vector<size_t>> template_groups;
	std::vector<string> templates;
	TTrie CheckOnce;
public:
	TDynamicTemplateMatcher();
	TStringID AddTemplate(const std::string &templatestr) override;
	TMatchResults MatchStream(ICharStream &stream) override;
};


class T2DSingleTemplateMatcher {
private:
	TStaticTemplateMatcher Matcher;
	size_t templatelength,templateheight,textlength, textheight;
	void FindRowMatchSequence(const std::vector<size_t>& Matches, size_t columnnumber,
		TMatchResults &Result,const std::vector<size_t>& equivalences);

public:
	void AddTemplateTable(const std::vector<string> &templatetable);
	TMatchResults MatchTable(const std::vector<string> &texttable);
};