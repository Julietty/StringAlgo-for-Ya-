#pragma once
#include <vector>
#include <string>
#include <exception>
#include <memory>


typedef int TStringID;
typedef std::pair<size_t,TStringID> TOccurance;
typedef std::vector<TOccurance> TMatchResults;

class ICharStream {
public:
	virtual char GetChar() = 0;
	virtual bool IsEmpty() const = 0;
};

class IMetaTemplateMatcher {
public:
	virtual TStringID AddTemplate(const std::string &templatestr) = 0;
	virtual TMatchResults MatchStream(ICharStream &stream) = 0;
};


class TStringStream: public ICharStream {
private:
	std::string str;
	size_t pos;
public:
	TStringStream(std::string s):str(s), pos(){
	}

	char GetChar() {
		if (IsEmpty()) 
			throw std::logic_error("Reading from empty stream");
		return str[pos++]; 
	}

	bool IsEmpty() const {
		return (pos == str.length());
	}

	void reset() {
		pos = 0;
	}
};



