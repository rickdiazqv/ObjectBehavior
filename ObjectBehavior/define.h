#pragma once
#include "tools.h"

constexpr const char* title = "ObjctBehavior";

constexpr int winx = 1600;
constexpr int winy = 900;

constexpr int n_mouse = 3;
constexpr int n_key = 256;

constexpr const char* path_key = "key.ini";

constexpr SceneId sc_init = SceneId::Title;

// Button
constexpr int n_btn_diff = 3;
constexpr const char* btn = "button";
constexpr const char* btn_red[n_btn_diff] = {
	"red_neutral",
	"red_click",
	"red_hover"
};
constexpr const char* btn_yel[n_btn_diff] = {
	"yellow_neutral",
	"yellow_click",
	"yellow_hover"
};
constexpr const char* btn_grn[n_btn_diff] = {
	"green_neutral",
	"green_click",
	"green_hover"
};
constexpr const char* btn_emr[n_btn_diff] = {
	"emerald_neutral",
	"emerald_click",
	"emerald_hover"
};
constexpr const char* btn_ppl[n_btn_diff] = {
	"purple_neutral",
	"purple_click",
	"purple_hover"
};
constexpr const char* btn_wht[n_btn_diff] = {
	"white_neutral",
	"white_click",
	"white_hover"
};
constexpr const char* btn_blk[n_btn_diff] = {
	"black_neutral",
	"black_click",
	"black_hover"
};

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