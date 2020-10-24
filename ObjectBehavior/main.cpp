#define __GLOBAL_INSTANCE__
#include "header.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	if (AllInit() != 0) { return -1; }

	GameProcessor* const gameProcessor = GameProcessor::geInstance();

	while (LoopProcess()) {
		DrawBox(0, 0, winx, winy, 0x7f7f7f, TRUE);
		gameProcessor->process();
	}

	GameProcessor::finalize();
	DxLib_End();

	return 0;
}