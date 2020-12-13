#pragma once
#include "tools.h"

constexpr const char* title = "ObjctBehavior";

constexpr int WINDOW_X = 1600;
constexpr int WINDOW_Y = 900;

constexpr int n_mouse = 3;
constexpr int n_key = 256;

constexpr const char* path_conf = "data/json/configloader.json";
constexpr const char* path_key = "key.ini";

constexpr SceneId sc_init = SceneId::Title;

constexpr const char* j_class = "class";
constexpr const char* j_key = "key";
constexpr const char* j_path = "path";
constexpr const char* j_config = "config";
constexpr const char* j_div = "division";
constexpr const char* j_reg = "region";
constexpr const char* j_x = "x";
constexpr const char* j_y = "y";
constexpr const char* j_sprites = "sprites";
constexpr const char* j_ = "";

#ifdef __GLOBAL_INSTANCE__
#define GLOBAL
#else
#define GLOBAL extern
#endif