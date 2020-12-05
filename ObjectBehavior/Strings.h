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
	string join(const string& delim) {
		auto s = ++_strings.begin();
		string res = _strings[0];

		for (; s != _strings.end(); s++) {
			res.append(delim);
			res.append(*s);
		}

		return res;
	}

public:
	template<typename... Rest>
	static string join(const string& delim, Rest... rest) { return __join_method_sum__(delim, rest...); }

private:
	template<typename First>
	static string __join_method_sum__(const string& delim, First first) {
		ostringstream oss; oss << first;
		string res = oss.str();
		return res;
	}
	template<typename First, typename... Rest>
	static string __join_method_sum__(const string& delim, First first, Rest... rest) {
		ostringstream oss; oss << first;
		string res = oss.str();
		res.append(delim); res.append(__join_method_sum__(delim, rest...));
		return res;
	}

};