#pragma once
#include "define.h"

class Strings {
private:
	vector<string> _strings;

public:
	Strings(const string& delim, const string& val);
	~Strings();

public:
	inline int size() { return _strings.size(); }
	inline string& getString(int index) { return _strings[index]; }
};

