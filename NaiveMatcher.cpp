#include "NaiveMatcher.h"

TNaiveTemplateMatcher::TNaiveTemplateMatcher():templates(),substrings(), maxtemplatelength(0) {
}

TStringID TNaiveTemplateMatcher::AddTemplate(const std::string &templatestr) {
	templates.addstring(templatestr,substrings.size());
	substrings.push_back(templatestr);
	maxtemplatelength = std::max(maxtemplatelength, templatestr.size());
	return substrings.size() - 1;
}

TMatchResults TNaiveTemplateMatcher::MatchStream(ICharStream &stream){
	if (!substrings.size())
		return TMatchResults();
	string buffer;
	TMatchResults Matches;
	size_t substringstart = 0;
	while (!stream.IsEmpty() || buffer.length()) {
		for (size_t template_id = 0; template_id < substrings.size(); ++template_id) {
			while (buffer.length() < substrings[template_id].size() && !stream.IsEmpty()) {
				char newch=stream.GetChar();
				if (static_cast<int>(newch) < 32 || static_cast<int>(newch) > 255) 
				throw std::logic_error("Character out of range");
				buffer.push_back(newch);
			}
			if (buffer.length() < substrings[template_id].size())
				continue;
			bool match = true;
			for (size_t symbnum = 0; symbnum < substrings[template_id].size();++symbnum)
				if (buffer[symbnum]!=substrings[template_id][symbnum])
					match = false; 

			if (match) {
				Matches.push_back(std::make_pair(substringstart + substrings[template_id].size() - 1,template_id));
			}
		}
		buffer.erase(0,1);
		substringstart++;
		
	}
	return Matches;
}


