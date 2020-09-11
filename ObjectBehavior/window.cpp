#include "header.h"

#define ColorBit		16		//表現する色の数

//======================================================
//ウィンドウ関連処理
//======================================================
int LoopProcess() {
	ScreenFlip();
	if (ProcessMessage() != 0) { return 0; }
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) { return 0; }
	ClearDrawScreen();

	return 1;
}
int AllInit() {
	ChangeWindowMode(TRUE); //ウィンドウ表示
	SetMainWindowText(title); //ウィンドウタイトル
	SetGraphMode(winx, winy, ColorBit); //ウィンドウサイズ
	SetFontSize(20); //利用フォントサイズ
	if (DxLib_Init() < 0) { return -1; }
	SetDrawScreen(DX_SCREEN_BACK); //描画対象

	return 0;
}