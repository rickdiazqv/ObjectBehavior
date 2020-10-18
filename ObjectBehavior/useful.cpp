#include "useful.h"
#include <json.hpp>

int pow(int a, int x) {
	int res = 1;

	for (int i = 0; i < x; i++) {
		res *= a;
	}

	return res;
}

string DxFileRead(const char* const fpath) {
	int hndl = FileRead_open(fpath);
	int size = FileRead_size(fpath);
	char* buf = new char[size + 1];
	FileRead_read(buf, size, hndl);
	FileRead_close(hndl);
	buf[size] = '\0';
	string str = string(buf);
	delete[] buf;

	/*int p1 = 0, p2 = 0;
	while ((p2 = str.find('\n', p1)) != string::npos) {
		str.erase(p2);
		p1 = p2;
	}*/

	return str;
}