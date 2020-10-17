#include "Strings.h"

Strings::Strings(const string& delim, const string& val) {
	int lend = delim.size();
	int p1 = 0, p2 = 0;

	while ((p2 = val.find(delim, p1)) != string::npos) {
		_strings.push_back(val.substr(p1, p2 - p1));
		p1 = p2 + lend;
	}
	_strings.push_back(val.substr(p1));
}

Strings::~Strings() {

}