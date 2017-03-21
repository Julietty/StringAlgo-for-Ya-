#pragma once
#include <boost/test/unit_test.hpp>
#include <exception>
#include "Base.h"
#include <algorithm>
#include "NaiveMatcher.h"
#include "time.h"

bool CompareResults(TMatchResults sample, TMatchResults standart);
template<typename Matcher1Type,typename Matcher2Type, typename TestType1, typename TestType2>
bool CompareMatchersResults(Matcher1Type &Matcher1, Matcher2Type &Matcher2, TestType1 test1, TestType2 test2) {
	TMatchResults Res2, Res1;
	try{
		Res1 = test1(Matcher1);
	} catch(std::logic_error er1) {
		return true;
	}
	try
	{
		Res2 = test2(Matcher2);
	} catch(std::logic_error er2) 
	{
		return true;
	}
	return CompareResults(Res1,Res2);
}



