#include "BaseTest.h"

bool CompareResults(TMatchResults sample, TMatchResults standart) {
	if (sample.size() != standart.size()) 
		return false;
	std::sort(sample.begin(), sample.end());
	std::sort(standart.begin(), standart.end());
	for (size_t i = 0; i < standart.size(); ++i) 
		if (sample[i] != standart[i]) {
			return false;
		}
	return true;
}


