#include "SingleMatcher.h"
#include <set>
#include <algorithm> 
#include <iostream>

TSingleTemplateMatcher::TSingleTemplateMatcher():actioncount(0), initialized(false), substr_(),p_func_values(), currentvalue(0)  {
	actioncount+=2;
	p_func_values.resize(2,0);
}

TStringID TSingleTemplateMatcher::AddTemplate(const string &template_) {
	if (initialized) 
		throw std::logic_error("More than one templates adding");
	substr_ = std::deque<char> (template_.begin(),template_.end());
	actioncount+=substr_.size() + 3;
	substr_.push_back(static_cast<char>(10));
	substr_.push_front(static_cast<char>(10));
	initialized = true;
	return 0;
}



size_t TSingleTemplateMatcher::p_func(size_t pi_prev, char ch) {
	if (p_func_values[pi_prev] + 1 == 0) 
		p_func_values[pi_prev] = p_func(p_func_values[pi_prev - 1], substr_[pi_prev]);
	actioncount++;
	while (pi_prev > 0 && substr_[pi_prev + 1] != ch) {
		pi_prev = p_func_values[pi_prev];
		actioncount++;
	}
	if (substr_[pi_prev + 1]==ch) {
		if (pi_prev + 1>= p_func_values.size())
			actioncount++;
			p_func_values.push_back(-1);
		return pi_prev + 1; 
	}
	else
		return pi_prev;
}

void TSingleTemplateMatcher::handlesymbol(TMatchResults& Result, char ch, size_t shift, TStringID templateid = 0) {
	actioncount++;
	currentvalue = p_func(currentvalue, ch);
	if (currentvalue == substr_.size() - 2) 
	Result.push_back(std::make_pair(shift, templateid));
}
TMatchResults TSingleTemplateMatcher::MatchStream(ICharStream &stream) {
	size_t shift = 0;
	actioncount++;
	TMatchResults Matches;
	p_func_values.resize(2,0);
	while (!stream.IsEmpty()) {
		char newchar=stream.GetChar();
		if (static_cast<int>(newchar) < 32 || static_cast<int>(newchar) > 255) 
			throw std::logic_error("Character out of range");
		handlesymbol(Matches, newchar, shift, 0);
		shift++;
	}
	currentvalue = 0;
	std::cerr << actioncount << std::endl;
	return Matches;
}


void TSingleTemplateMatcher::AppendCharToTemplate(char c) {
	if (!initialized)
		throw std::logic_error("Appending to empty template");
	substr_.pop_back();
	substr_.push_back(c);
	substr_.push_back(static_cast<char>(10));
}

void TSingleTemplateMatcher::PrependCharToTemplate(char c) {
	if (!initialized)
		throw std::logic_error("Prepending to empty template");
	substr_.pop_front();
	substr_.push_front(c);
	substr_.push_front(static_cast<char>(10));
}
TWildcardSingleTemplateMatcher::TWildcardSingleTemplateMatcher():initialized(false),substring(),
	Matchers(), Parts_range() {
}



TStringID TWildcardSingleTemplateMatcher::AddTemplate(const string &template_) {
	if (initialized)
		throw std::logic_error("More than one templates adding");
	initialized = true;
	substring = template_;
	size_t partbegin,partend;
	partbegin = 0;
	while (partbegin < substring.size() && substring[partbegin]=='?')
			partbegin++;
	partend = std::min(substring.find_first_of('?'),substring.size());
	while(partbegin < substring.size()) {
		Matchers.push_back(TSingleTemplateMatcher());
		Matchers.back().AddTemplate(string(&substring[partbegin],&substring[partend]));
		Parts_range.push_back(std::make_pair(partbegin,partend));
		partbegin = partend + 1;
		while (partbegin < substring.size() && substring[partbegin]=='?')
			partbegin++;
		partend = std::min(substring.find_first_of('?',partbegin),substring.size());
	}
	return 0;
}

TMatchResults TWildcardSingleTemplateMatcher::MatchStream(ICharStream &stream) {
	TMatchResults PartsMatchResult; 
	TMatchResults Result; 
	size_t streamlength = 0;
	std::deque<std::vector<bool>> buffer(substring.size(),std::vector<bool> (Parts_range.size(),false));
	size_t shift = 0;
	while (!stream.IsEmpty()) {
		streamlength++;
		char newchar=stream.GetChar();
		if (static_cast<int>(newchar) < 32 || static_cast<int>(newchar) > 255) 
			throw std::logic_error("Character out of range");
		for (size_t partnumber = 0; partnumber < Parts_range.size(); ++partnumber)   
			Matchers[partnumber].handlesymbol(PartsMatchResult, newchar, shift, partnumber);
		shift++;
	}
	shift = 0;
	size_t PartsMatchResultShift = 0;
	while (PartsMatchResultShift < PartsMatchResult.size() || shift + substring.size() <= streamlength) {
		while (!PartsMatchResult.empty() && PartsMatchResultShift < PartsMatchResult.size() &&
			PartsMatchResult[PartsMatchResultShift].first - shift < substring.size()) {
				buffer[PartsMatchResult[PartsMatchResultShift].first - shift][PartsMatchResult[PartsMatchResultShift].second] = true;
			PartsMatchResultShift++;
		}
		bool Match = true;
		size_t partnumber = 0;
		while (Match && partnumber < Parts_range.size()) {
			if (!buffer[Parts_range[partnumber].second - 1][partnumber]) 	
				Match = false;
			partnumber++;
		}
		if (Match) 
			Result.push_back(std::make_pair(shift + substring.size() - 1,0));
		shift++;
		buffer.pop_front();
		buffer.push_back(std::vector<bool>(Parts_range.size(),false));
	}
	return Result;
}