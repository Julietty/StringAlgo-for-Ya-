#pragma comment(linker, "/STACK:66777216")
#include "BaseTest.h"
#include "StaticMatcher.h"
using std::make_pair;
using std::vector;

BOOST_AUTO_TEST_CASE(StaticMatcherSimpleTest) {
	TStaticTemplateMatcher TestStatic1;
	std::vector<TStringID> templates;
	templates.push_back(TestStatic1.AddTemplate("aba"));
	templates.push_back(TestStatic1.AddTemplate("cac"));
	templates.push_back(TestStatic1.AddTemplate("bac"));
	templates.push_back(TestStatic1.AddTemplate("aca"));
	templates.push_back(TestStatic1.AddTemplate("ba"));
	templates.push_back(TestStatic1.AddTemplate("abacaba"));
	TStringStream teststream1("abacaba");
	TMatchResults TrueAns1;
	TrueAns1.push_back(make_pair(2,templates[0]));
	TrueAns1.push_back(make_pair(6,templates[5]));
	TrueAns1.push_back(make_pair(6,templates[0]));
	TrueAns1.push_back(make_pair(3,templates[2]));
	TrueAns1.push_back(make_pair(4,templates[3]));
	TrueAns1.push_back(make_pair(2,templates[4]));
	TrueAns1.push_back(make_pair(6,templates[4]));
	BOOST_CHECK(CompareResults(TestStatic1.MatchStream(teststream1), TrueAns1));
	teststream1.reset();
	
	templates.clear();
	TStaticTemplateMatcher TestStatic2;
	templates.push_back(TestStatic2.AddTemplate("aba"));
	templates.push_back(TestStatic2.AddTemplate("cac"));
	templates.push_back(TestStatic2.AddTemplate("bac"));
	templates.push_back(TestStatic2.AddTemplate("aca"));
	templates.push_back(TestStatic2.AddTemplate("ba"));
	templates.push_back(TestStatic2.AddTemplate("abacaba"));
	templates.push_back(TestStatic2.AddTemplate("a"));
	TrueAns1.push_back(make_pair(0,templates[6]));
	TrueAns1.push_back(make_pair(2,templates[6]));
	TrueAns1.push_back(make_pair(4,templates[6]));
	TrueAns1.push_back(make_pair(6,templates[6]));
	BOOST_CHECK(CompareResults(TestStatic2.MatchStream(teststream1), TrueAns1));

	TStringStream teststream2("112312ba");
	TMatchResults TrueAns2;
	TrueAns2.push_back(make_pair(7,templates[4]));
	TrueAns2.push_back(make_pair(7,templates[6]));
	BOOST_CHECK(CompareResults(TestStatic2.MatchStream(teststream2), TrueAns2));

	TStaticTemplateMatcher TestStatic3;
	TMatchResults TrueAns4;
	TStringStream teststream3("baacaababa");
	TStringID templateid= TestStatic3.AddTemplate("ba");
	TrueAns4.push_back(make_pair(1,templateid));
	TrueAns4.push_back(make_pair(7,templateid));
	TrueAns4.push_back(make_pair(9,templateid));
	BOOST_CHECK(CompareResults(TrueAns4,TestStatic3.MatchStream(teststream3)));
	
}
BOOST_AUTO_TEST_CASE(StaticMatcherBoundariesTest) {
	TStaticTemplateMatcher TestStatic1;
	vector<TStringID> templates;
	templates.push_back(TestStatic1.AddTemplate("a"));
	templates.push_back(TestStatic1.AddTemplate("b"));
	templates.push_back(TestStatic1.AddTemplate("bbc"));
	TStringStream teststream1("aaaca");
	TMatchResults TrueAns1;
	TrueAns1.push_back(make_pair(0, templates[0]));
	TrueAns1.push_back(make_pair(1, templates[0]));
	TrueAns1.push_back(make_pair(2, templates[0]));
	TrueAns1.push_back(make_pair(4, templates[0]));
	BOOST_CHECK(CompareResults(TestStatic1.MatchStream(teststream1),TrueAns1));
}


BOOST_AUTO_TEST_CASE(DynamicMatcherFailTest) {
	TDynamicTemplateMatcher TestDynamic1;
	TestDynamic1.AddTemplate("test");
	BOOST_CHECK_THROW(TestDynamic1.AddTemplate("test"),std::logic_error);

}

BOOST_AUTO_TEST_CASE(DynamicMatcherSimpleTest) {
	TDynamicTemplateMatcher TestDynamic1;
	std::vector<TStringID> templates;
	templates.push_back(TestDynamic1.AddTemplate("aba"));
	templates.push_back(TestDynamic1.AddTemplate("cac"));
	templates.push_back(TestDynamic1.AddTemplate("bac"));
	templates.push_back(TestDynamic1.AddTemplate("aca"));
	templates.push_back(TestDynamic1.AddTemplate("ba"));
	templates.push_back(TestDynamic1.AddTemplate("abacaba"));
	TStringStream teststream1("abacaba");
	TMatchResults TrueAns1;
	TrueAns1.push_back(make_pair(2,templates[0]));
	TrueAns1.push_back(make_pair(6,templates[5]));
	TrueAns1.push_back(make_pair(6,templates[0]));
	TrueAns1.push_back(make_pair(3,templates[2]));
	TrueAns1.push_back(make_pair(4,templates[3]));
	TrueAns1.push_back(make_pair(2,templates[4]));
	TrueAns1.push_back(make_pair(6,templates[4]));
	BOOST_CHECK(CompareResults(TestDynamic1.MatchStream(teststream1), TrueAns1));
	teststream1.reset();
	BOOST_CHECK(CompareResults(TestDynamic1.MatchStream(teststream1), TrueAns1));
	templates.push_back(TestDynamic1.AddTemplate("a"));
	TrueAns1.push_back(make_pair(0,templates[6]));
	TrueAns1.push_back(make_pair(2,templates[6]));
	TrueAns1.push_back(make_pair(4,templates[6]));
	TrueAns1.push_back(make_pair(6,templates[6]));
	teststream1.reset();
	BOOST_CHECK(CompareResults(TestDynamic1.MatchStream(teststream1), TrueAns1));
	TStringStream teststream2("112312ba");
	TMatchResults TrueAns2;
	TrueAns2.push_back(make_pair(7,templates[4]));
	TrueAns2.push_back(make_pair(7,templates[6]));
	BOOST_CHECK(CompareResults(TestDynamic1.MatchStream(teststream2), TrueAns2));
	templates.clear();
	TDynamicTemplateMatcher TestDynamic3;
	templates.push_back(TestDynamic3.AddTemplate("a"));
	templates.push_back(TestDynamic3.AddTemplate("aa"));
	templates.push_back(TestDynamic3.AddTemplate("aaa"));
	TStringStream teststream3("aaaaaaa");
	TMatchResults TrueAns3;
	TrueAns3.push_back(make_pair(0,templates[0]));
	TrueAns3.push_back(make_pair(1,templates[0]));
	TrueAns3.push_back(make_pair(2,templates[0]));
	TrueAns3.push_back(make_pair(3,templates[0]));
	TrueAns3.push_back(make_pair(4,templates[0]));
	TrueAns3.push_back(make_pair(5,templates[0]));
	TrueAns3.push_back(make_pair(6,templates[0]));
	TrueAns3.push_back(make_pair(1,templates[1]));
	TrueAns3.push_back(make_pair(2,templates[1]));
	TrueAns3.push_back(make_pair(3,templates[1]));
	TrueAns3.push_back(make_pair(4,templates[1]));
	TrueAns3.push_back(make_pair(5,templates[1]));
	TrueAns3.push_back(make_pair(6,templates[1]));
	TrueAns3.push_back(make_pair(2,templates[2]));
	TrueAns3.push_back(make_pair(3,templates[2]));
	TrueAns3.push_back(make_pair(4,templates[2]));
	TrueAns3.push_back(make_pair(5,templates[2]));
	TrueAns3.push_back(make_pair(6,templates[2]));
	BOOST_CHECK(CompareResults(TestDynamic3.MatchStream(teststream3),TrueAns3));
	TDynamicTemplateMatcher TestDynamic4;
	TMatchResults TrueAns4;
	TStringStream teststream4("baacaababa");
	TStringID templateid= TestDynamic4.AddTemplate("ba");
	TrueAns4.push_back(make_pair(1,templateid));
	TrueAns4.push_back(make_pair(7,templateid));
	TrueAns4.push_back(make_pair(9,templateid));
	BOOST_CHECK(CompareResults(TrueAns4,TestDynamic4.MatchStream(teststream4)));
}

BOOST_AUTO_TEST_CASE(T2DSingleMatcherSimpleTest) {
	T2DSingleTemplateMatcher TestT2DSingle1;
	vector<string> A;
	vector<string> B;
	A.push_back("ab");
	A.push_back("ab");
	B.push_back("aabb");
	B.push_back("abab");
	B.push_back("abab");
	B.push_back("bbaa");
	TestT2DSingle1.AddTemplateTable(A);
	TMatchResults TrueAns1;
	TrueAns1.push_back(make_pair(2,1));
	TrueAns1.push_back(make_pair(2,3));
	BOOST_CHECK(CompareResults(TestT2DSingle1.MatchTable(B),TrueAns1));
	T2DSingleTemplateMatcher TestT2DSingle2;
	A.clear();
	B.clear();
	A.push_back("bca");
	A.push_back("bab");
	B.push_back("ababcaab");
	B.push_back("bbcbabca");
	B.push_back("abcaabab");
	B.push_back("baabcbab");
	B.push_back("bbcaaabc");
	B.push_back("cbabacca");
	TMatchResults TrueAns2;
	TestT2DSingle2.AddTemplateTable(A);
	TrueAns2.push_back(make_pair(1,5));
	TrueAns2.push_back(make_pair(2,7));
	TrueAns2.push_back(make_pair(5,3));
	BOOST_CHECK(CompareResults(TestT2DSingle2.MatchTable(B),TrueAns2));
}

template <typename MatcherType>
class staticmatchertest {
public:
	MatcherType Matcher;
	ICharStream& stream_;
	vector<string> pattern_;
	staticmatchertest(ICharStream &stream, const vector<string>&pattern):stream_(stream), pattern_(pattern) {
	}
	TMatchResults operator()(MatcherType &Matcher){
		for(auto &tmp:pattern_)Matcher.AddTemplate(tmp);
		return Matcher.MatchStream(stream_);
	}
};

BOOST_AUTO_TEST_CASE(StaticMatcherStressTest){
	for (size_t testnumber = 0; testnumber < 100; ++testnumber) {
		vector<string> templates;
		templates.resize(rand()%15);
		for (size_t template_num = 0; template_num < templates.size();++template_num) {
			size_t templatesize = rand() % 10 + 1;
			string substring;
			for (size_t i = 0; i < templatesize; ++i)
				substring.push_back('a'+rand()%3);
			templates[template_num]=std::move(substring);
		}
		
		size_t textsize = rand() % 100000;
		string text;
		for (size_t i = 0; i < textsize; ++i)
			text.push_back('a'+rand()%3);
		TStringStream teststream1(text),teststream2(text); 
		staticmatchertest<TStaticTemplateMatcher> test1(teststream1, templates);
		staticmatchertest<TNaiveTemplateMatcher> test2(teststream2, templates);
		TStaticTemplateMatcher StaticMatcher;
		TNaiveTemplateMatcher NaiveMatcher; 
		BOOST_CHECK(CompareMatchersResults(StaticMatcher, NaiveMatcher, test1, test2));
	}
}
BOOST_AUTO_TEST_CASE(DynamicMatcherStressTest) {
	for (size_t testnumber = 0; testnumber < 100; ++testnumber) {
		vector<string> templates;
		templates.resize(rand()%15);
		for (size_t template_num = 0; template_num < templates.size();++template_num) {
			size_t templatesize = rand() % 10 + 1;
			string substring;
			for (size_t i = 0; i < templatesize; ++i)
				substring.push_back('a'+rand()%3);
			templates[template_num]=std::move(substring);
		}
		
		size_t textsize = rand() % 100000;
		string text;
		for (size_t i = 0; i < textsize; ++i)
			text.push_back('a'+rand()%3);
		TStringStream teststream1(text),teststream2(text); 
		staticmatchertest<TDynamicTemplateMatcher> test1(teststream1, templates);
		staticmatchertest<TNaiveTemplateMatcher> test2(teststream2, templates);
		TDynamicTemplateMatcher DynamicMatcher;
		TNaiveTemplateMatcher NaiveMatcher; 
		BOOST_CHECK(CompareMatchersResults(DynamicMatcher, NaiveMatcher, test1, test2));
	}
} 

BOOST_AUTO_TEST_CASE(StaticMatcherBigTests) {
	srand(time(0));
	TStaticTemplateMatcher StaticMatcher2;
	string long_a;
	long_a.reserve(1000000);
	for (size_t i = 0; i < 1000000; ++i)
		long_a.push_back('a');
	TStringStream teststream2(long_a);
	StaticMatcher2.AddTemplate("a");
	StaticMatcher2.AddTemplate("aa");
	StaticMatcher2.AddTemplate("aaa");
	StaticMatcher2.MatchStream(teststream2);
	for (size_t i = 0; i < 300; ++i)
		long_a[rand()%1000000] = 'b';
	TStringStream teststream3(long_a);
	StaticMatcher2.MatchStream(teststream3);
	StaticMatcher2;
	string randomstr;
	randomstr.reserve(1000000);
	for (size_t i = 0; i < 1000000; ++i)
		randomstr.push_back('a' + rand()%30);
	TStaticTemplateMatcher StaticMatcher4;
	size_t begin = rand()%400000;
	size_t end = begin+ 1 + rand() % 400000;
	StaticMatcher4.AddTemplate(string(&randomstr[begin],&randomstr[end]));
	begin = rand()%400000;
	end = begin + 1 + rand() % 4000000;
		
	StaticMatcher4.AddTemplate(string(&randomstr[begin],&randomstr[end]));
	begin = rand()%400000;
	end = begin + 1 + rand() % 400000;
		
	StaticMatcher4.AddTemplate(string(&randomstr[begin],&randomstr[end]));
	TStringStream teststream4(randomstr);
	StaticMatcher4.MatchStream(teststream4);
}