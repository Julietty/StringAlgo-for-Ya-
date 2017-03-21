#define BOOST_TEST_MAIN
#include "BaseTest.h"


using std::make_pair;





BOOST_AUTO_TEST_CASE(NaiveMatcherFailTest) {
	TNaiveTemplateMatcher TestNaive1;
	TestNaive1.AddTemplate("qq");
	BOOST_CHECK_THROW(TestNaive1.AddTemplate("qq"),std::logic_error);

	
	
	TNaiveTemplateMatcher TestNaive2;
	TStringStream stream2("abacaba");
	TestNaive2.AddTemplate("123");
	TestNaive2.AddTemplate("pqedzxd");
	TestNaive2.AddTemplate("bacab");
	TestNaive2.MatchStream(stream2);
	TestNaive2.AddTemplate("ba");
	BOOST_CHECK_THROW(TestNaive2.AddTemplate("123"),std::logic_error);
	bool failed3 = false;
	TNaiveTemplateMatcher TestNaive3;
	string s("123");
	s.push_back(static_cast<char>(10));
	TStringStream stream3(s);
	TestNaive3.AddTemplate("123");
	BOOST_CHECK_THROW(TestNaive3.MatchStream(stream3),std::logic_error);
	
}
BOOST_AUTO_TEST_CASE(NaiveMatcherSimpleTest) {
	TNaiveTemplateMatcher TestNaive1;
	std::vector<TStringID> templates;
	templates.push_back(TestNaive1.AddTemplate("aba"));
	templates.push_back(TestNaive1.AddTemplate("cac"));
	templates.push_back(TestNaive1.AddTemplate("bac"));
	templates.push_back(TestNaive1.AddTemplate("aca"));
	templates.push_back(TestNaive1.AddTemplate("ba"));
	templates.push_back(TestNaive1.AddTemplate("abacaba"));
	TStringStream teststream1("abacaba");
	TMatchResults TrueAns1;
	TrueAns1.push_back(make_pair(2,templates[0]));
	TrueAns1.push_back(make_pair(6,templates[5]));
	TrueAns1.push_back(make_pair(6,templates[0]));
	TrueAns1.push_back(make_pair(3,templates[2]));
	TrueAns1.push_back(make_pair(4,templates[3]));
	TrueAns1.push_back(make_pair(2,templates[4]));
	TrueAns1.push_back(make_pair(6,templates[4]));
	BOOST_CHECK(CompareResults(TestNaive1.MatchStream(teststream1), TrueAns1));
	teststream1.reset();
	BOOST_CHECK(CompareResults(TestNaive1.MatchStream(teststream1), TrueAns1));
	templates.push_back(TestNaive1.AddTemplate("a"));
	TrueAns1.push_back(make_pair(0,templates[6]));
	TrueAns1.push_back(make_pair(2,templates[6]));
	TrueAns1.push_back(make_pair(4,templates[6]));
	TrueAns1.push_back(make_pair(6,templates[6]));
	teststream1.reset();
	BOOST_CHECK(CompareResults(TestNaive1.MatchStream(teststream1), TrueAns1));
	TStringStream teststream2("112312ba");
	TMatchResults TrueAns2;
	TrueAns2.push_back(make_pair(7,templates[4]));
	TrueAns2.push_back(make_pair(7,templates[6]));
	BOOST_CHECK(CompareResults(TestNaive1.MatchStream(teststream2), TrueAns2));
	templates.clear();
	TNaiveTemplateMatcher TestNaive3;
	templates.push_back(TestNaive3.AddTemplate("a"));
	templates.push_back(TestNaive3.AddTemplate("aa"));
	templates.push_back(TestNaive3.AddTemplate("aaa"));
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
	BOOST_CHECK(CompareResults(TestNaive3.MatchStream(teststream3),TrueAns3));
	TNaiveTemplateMatcher TestNaive4;
	TMatchResults TrueAns4;
	TStringStream teststream4("baacaababa");
	TStringID templateid= TestNaive4.AddTemplate("ba");
	TrueAns4.push_back(make_pair(1,templateid));
	TrueAns4.push_back(make_pair(7,templateid));
	TrueAns4.push_back(make_pair(9,templateid));
	BOOST_CHECK(CompareResults(TrueAns4,TestNaive4.MatchStream(teststream4)));
}
BOOST_AUTO_TEST_CASE(NaiveMatcherBoundariesTest) {
	TNaiveTemplateMatcher TestNaive1;
	TStringStream teststream1("a");
	std::vector<TStringID> templatesid;
	templatesid.push_back(TestNaive1.AddTemplate("a"));
	TMatchResults TrueAns1;
	TrueAns1.push_back(make_pair(0,templatesid[0]));
	BOOST_CHECK(CompareResults(TestNaive1.MatchStream(teststream1),TrueAns1));
	TStringStream EmptyStream("");
	TrueAns1.clear();
	BOOST_CHECK(CompareResults(TestNaive1.MatchStream(EmptyStream),TrueAns1));
	TestNaive1.AddTemplate("veryverylongtext");
	TStringStream Teststream2("shorttext");
	BOOST_CHECK(CompareResults(TestNaive1.MatchStream(Teststream2),TrueAns1));

}
