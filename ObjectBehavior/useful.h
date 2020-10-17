#pragma once
#include "package.h"

int pow(int a, int x);
string DxFileRead(const char* const fpath);

inline string j2s(json& j) { return j.get<string>(); }
inline int j2i(json& j) { return atoi(j2s(j).c_str()); }