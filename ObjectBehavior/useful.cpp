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
	char* buf = new char[size];
	FileRead_read(buf, size, hndl);
	FileRead_close(hndl);
	string str = string(buf);
	delete[] buf;

	return str;
}