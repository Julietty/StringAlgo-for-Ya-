
#include "BaseTest.h"
#include "SingleMatcher.h"
#include <iostream>
using std::make_pair;

BOOST_AUTO_TEST_CASE(SingleMatcherFailTest)
{
	TSingleTemplateMatcher TestSingle1;
	TestSingle1.AddTemplate("pqr");
	BOOST_CHECK_THROW(TestSingle1.AddTemplate("123"),std::logic_error);
}

BOOST_AUTO_TEST_CASE(WildcardSingleMatcherFailTest) {
	TWildcardSingleTemplateMatcher TestWildcard;
	TestWildcard.AddTemplate("pqr");
	BOOST_CHECK_THROW(TestWildcard.AddTemplate("123"),std::logic_error);

}

BOOST_AUTO_TEST_CASE(SingleMatcherSimpleTest)
{
	TSingleTemplateMatcher TestSingle1;
	TStringStream Teststream1("aba");
	TStringID templateid = TestSingle1.AddTemplate("ba");
	TMatchResults TrueAns1;
	TrueAns1.push_back(make_pair(2,templateid));
	BOOST_CHECK(CompareResults(TrueAns1, TestSingle1.MatchStream(Teststream1)));
	TStringStream Teststream2("baacaababa");
	TMatchResults TrueAns2;
	TrueAns2.push_back(make_pair(1,templateid));
	TrueAns2.push_back(make_pair(7,templateid));
	TrueAns2.push_back(make_pair(9,templateid));
	BOOST_CHECK(CompareResults(TrueAns2,TestSingle1.MatchStream(Teststream2)));
	TMatchResults TrueAns3;
	TStringStream Teststream3("baaaaaaaaaaabc");
	TrueAns3.push_back(make_pair(1,templateid));
	BOOST_CHECK(CompareResults(TrueAns3,TestSingle1.MatchStream(Teststream3)));
	TMatchResults TrueAns4;
	TrueAns4.push_back(make_pair(8,templateid));
	TestSingle1.AppendCharToTemplate('b');
	Teststream2.reset();
	BOOST_CHECK(CompareResults(TestSingle1.MatchStream(Teststream2),TrueAns4));
	Teststream2.reset();
	TestSingle1.PrependCharToTemplate('a');
	BOOST_CHECK(CompareResults(TestSingle1.MatchStream(Teststream2),TrueAns4));
	TSingleTemplateMatcher TestSingle2;
	TStringStream Teststream4("abacabadabacaba");
	TMatchResults TrueAns5;
	templateid = TestSingle2.AddTemplate("ba");
	TrueAns5.push_back(make_pair(2,templateid));
	TrueAns5.push_back(make_pair(6,templateid));
	TrueAns5.push_back(make_pair(10,templateid));
	TrueAns5.push_back(make_pair(14,templateid));
	BOOST_CHECK(CompareResults(TestSingle2.MatchStream(Teststream4),TrueAns5));
	
}

/*BOOST_AUTO_TEST_CASE(SingleMatcherBoundariesTest) {
	

}*/

BOOST_AUTO_TEST_CASE(WildcardSingleMatcherBaseTest)
{
	TWildcardSingleTemplateMatcher TestSingle1;
	TStringStream Teststream1("aba");
	TStringID templateid = TestSingle1.AddTemplate("ba");
	TMatchResults TrueAns1;
	TrueAns1.push_back(make_pair(2,templateid));
	BOOST_CHECK(CompareResults(TrueAns1, TestSingle1.MatchStream(Teststream1)));
	TStringStream Teststream2("baacaababa");
	TMatchResults TrueAns2;
	TrueAns2.push_back(make_pair(1,templateid));
	TrueAns2.push_back(make_pair(7,templateid));
	TrueAns2.push_back(make_pair(9,templateid));
	BOOST_CHECK(CompareResults(TrueAns2,TestSingle1.MatchStream(Teststream2)));
	TMatchResults TrueAns3;
	TStringStream Teststream3("baaaaaaaaaaabc");
	TrueAns3.push_back(make_pair(1,templateid));
	BOOST_CHECK(CompareResults(TrueAns3,TestSingle1.MatchStream(Teststream3)));
}

BOOST_AUTO_TEST_CASE(WildcardSingleMatcherSimpleTest)
{
	TWildcardSingleTemplateMatcher TestWildcard1;
	TStringStream Teststream1("aba");
	TStringID templateid = TestWildcard1.AddTemplate("a?a");
	TMatchResults TrueAns1;
	TrueAns1.push_back(make_pair(2,templateid));
	BOOST_CHECK(CompareResults(TrueAns1, TestWildcard1.MatchStream(Teststream1)));
	TWildcardSingleTemplateMatcher TestWildcard5;
	TestWildcard5.AddTemplate("??");
	TStringStream smallstream("abs");
	TrueAns1.push_back(make_pair(1,templateid));
	BOOST_CHECK(CompareResults(TrueAns1, TestWildcard5.MatchStream(smallstream)));
	TStringStream Teststream2("baacaababa");
	TMatchResults TrueAns2;
	TrueAns2.push_back(make_pair(4,templateid));
	TrueAns2.push_back(make_pair(7,templateid));
	TrueAns2.push_back(make_pair(9,templateid));
	BOOST_CHECK(CompareResults(TrueAns2,TestWildcard1.MatchStream(Teststream2)));
	TMatchResults TrueAns3;
	TStringStream Teststream3("baaaaaaaaaaabc");
	TrueAns3.push_back(make_pair(3,templateid));
	TrueAns3.push_back(make_pair(4,templateid));
	TrueAns3.push_back(make_pair(5,templateid));
	TrueAns3.push_back(make_pair(6,templateid));
	TrueAns3.push_back(make_pair(7,templateid));
	TrueAns3.push_back(make_pair(8,templateid));
	TrueAns3.push_back(make_pair(9,templateid));
	TrueAns3.push_back(make_pair(10,templateid));
	TrueAns3.push_back(make_pair(11,templateid));

	BOOST_CHECK(CompareResults(TrueAns3,TestWildcard1.MatchStream(Teststream3)));

	TWildcardSingleTemplateMatcher TestWildcard2;
	templateid = TestWildcard2.AddTemplate("totes?t???lateto");
	TStringStream Teststream4("totesttemplatetotesttestlateto");
	TMatchResults TrueAns4;
	TrueAns4.push_back(make_pair(15,templateid));
	TrueAns4.push_back(make_pair(29,templateid));

	BOOST_CHECK(CompareResults(TrueAns4, TestWildcard2.MatchStream(Teststream4)));
}
template <typename MatcherType>
class singlematchertest {
public:
	MatcherType Matcher;
	ICharStream& stream_;
	const string& pattern_;
	singlematchertest(ICharStream &stream, const string &pattern):stream_(stream), pattern_(pattern) {
	}
	TMatchResults operator()(MatcherType &Matcher){
		Matcher.AddTemplate(pattern_);
		return Matcher.MatchStream(stream_);
	}
};
/*BOOST_AUTO_TEST_CASE(SingleMatcherTimeTest)
{

	srand(time(0));
	string substring;
	
		for (size_t i = 0; i < 10; ++i)
			substring.push_back('a'+rand()%3);
	string text;
	text.reserve(1000000);
		for (size_t i = 0; i < 1000000; ++i)
			text.push_back('a'+rand()%3);
	 
	TStringStream teststream1(text); 
	TSingleTemplateMatcher SingleMatcher1;
	time_t ts=clock();
	SingleMatcher1.AddTemplate(substring);
	SingleMatcher1.MatchStream(teststream1);
	time_t tf=clock();
	std::cerr << 1.0 * (tf - ts)/CLOCKS_PER_SEC;
	
	//big tests
	TSingleTemplateMatcher SingleMatcher2;
	string long_a;
	long_a.reserve(1000000);
	for (size_t i = 0; i < 1000000; ++i)
		long_a.push_back('a');
	TStringStream teststream2(long_a);
	SingleMatcher2.AddTemplate("a");
	SingleMatcher2.MatchStream(teststream2);
	TSingleTemplateMatcher SingleMatcher3;
	SingleMatcher3.AddTemplate("aa");
	teststream2.reset();
	SingleMatcher3.MatchStream(teststream2);
	for (size_t i = 0; i < 300; ++i)
		long_a[rand()%1000000] = 'b';
	TStringStream teststream3(long_a);
	SingleMatcher3.MatchStream(teststream3);
	string randomstr;
	randomstr.reserve(1000000);
	for (size_t i = 0; i < 1000000; ++i)
		randomstr.push_back('a' + rand()%30);
	size_t begin = rand()%500000;
	size_t end = begin + rand() % 500000;
	TSingleTemplateMatcher SingleMatcher4;
	SingleMatcher4.AddTemplate(string(&randomstr[begin],&randomstr[end]));
	TStringStream teststream4(randomstr);
	SingleMatcher4.MatchStream(teststream4);
}
BOOST_AUTO_TEST_CASE(SingleMatcherStressTest)
{
	srand(time(0));
	for (size_t testnumber = 0; testnumber < 100; ++testnumber) {
		size_t templatesize = rand() % 10 + 1;
		size_t textsize = rand() % 10000;
		string substring;
		for (size_t i = 0; i < templatesize; ++i)
			substring.push_back('a'+rand()%3);
		string text;
		for (size_t i = 0; i < textsize; ++i)
			text.push_back('a'+rand()%3);
		TStringStream teststream1(text),teststream2(text); 
		singlematchertest<TSingleTemplateMatcher> test1(teststream1, substring);
		singlematchertest<TNaiveTemplateMatcher> test2(teststream2, substring);
		TSingleTemplateMatcher SingleMatcher;
		TNaiveTemplateMatcher NaiveMatcher; 
		BOOST_CHECK(CompareMatchersResults(SingleMatcher, NaiveMatcher, test1, test2));
	}
	
}

TMatchResults WildcardNaiveMatch(const string &substring, ICharStream &stream){
	string buffer;
	TMatchResults Matches;
	size_t substringstart = 0;
	while (!stream.IsEmpty() || buffer.length()) {
		while (buffer.length() < substring.size() && !stream.IsEmpty()) {
			char newch=stream.GetChar();
			if (static_cast<int>(newch) < 32 || static_cast<int>(newch) > 255) 
				throw std::logic_error("Character out of range");
			buffer.push_back(newch);
		}
		if (buffer.length() >= substring.size()){
			bool match = true;
			for (size_t symbnum = 0; symbnum < substring.size();++symbnum) {
				if (buffer[symbnum]!=substring[symbnum]&&substring[symbnum]!='?')
					match = false; 
			}
			if (match) 
				Matches.push_back(std::make_pair(substringstart + substring.size() - 1,0));
		}
		buffer.erase(0,1);
		substringstart++;
		
	}
	return Matches;
}

BOOST_AUTO_TEST_CASE(WildcardSingleMatcherStressTest)
{
	srand(time(0));
	for (size_t testnumber = 0; testnumber < 100; ++testnumber) {
		size_t templatesize = rand() % 10 + 1;
		size_t textsize = rand() % 10000;
		string substring;
		for (size_t i = 0; i < templatesize; ++i) {
			substring.push_back('a'+rand()%3);
			if (rand()%10 < 3)
				substring.push_back('?');
		}
		string text;
		for (size_t i = 0; i < textsize; ++i)
			text.push_back('a'+rand()%3);
		TStringStream teststream1(text),teststream2(text); 
		TWildcardSingleTemplateMatcher WildcardMatcher;
		WildcardMatcher.AddTemplate(substring);
		BOOST_CHECK(CompareResults(WildcardMatcher.MatchStream(teststream1),WildcardNaiveMatch(substring,teststream2)));
	}
}*/
