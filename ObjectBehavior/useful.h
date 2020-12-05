#pragma once
#include "package.h"

int pow(int a, int x);
string DxFileRead(const char* const fpath);

inline string j2s(json& j) { return move(j.get<string>()); }
//inline const char*&& j2c(json& j) { return j2s(j).c_str(); }
inline int j2i(json& j) { return j.get<int>();
}