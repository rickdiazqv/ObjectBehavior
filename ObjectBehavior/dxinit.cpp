#include "header.h"

#define ColorBit		16		//�\������F�̐�

//======================================================
//�E�B���h�E�֘A����
//======================================================
int LoopProcess() {
	ScreenFlip();
	if (ProcessMessage() != 0) { return 0; }
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) { return 0; }
	ClearDrawScreen();

	return 1;
}
int AllInit() {
	SetAlwaysRunFlag(TRUE);
	ChangeWindowMode(TRUE); //�E�B���h�E�\��
	SetMainWindowText(title); //�E�B���h�E�^�C�g��
	SetGraphMode(WINDOW_X, WINDOW_Y, ColorBit); //�E�B���h�E�T�C�Y
	SetFontSize(16); //���p�t�H���g�T�C�Y
	if (DxLib_Init() < 0) { return -1; }
	SetDrawScreen(DX_SCREEN_BACK); //�`��Ώ�

	return 0;
}