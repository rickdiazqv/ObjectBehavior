#pragma once
#include "tools.h"

constexpr const char* title = "ObjctBehavior";

constexpr int winx = 1600;
constexpr int winy = 900;

constexpr int n_mouse = 3;
constexpr int n_key = 256;

constexpr const char* path_key = "key.ini";

#ifdef __GLOBAL_INSTANCE__
#define GLOBAL
#else
#define GLOBAL extern
#endif