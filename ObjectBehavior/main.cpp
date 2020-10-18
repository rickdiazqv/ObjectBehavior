#define __GLOBAL_INSTANCE__
#include "header.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	if (AllInit() != 0) { return -1; }

	GameProcessor* const gameProcessor = GameProcessor::geInstance();
	RectangleObject rect1(111, 800, 50, 50, Layer::Object, true);
	RectangleObject rect2(333, 333, 100, 100, Layer::Default, true);
	RectangleObject rect3(555, 555, 150, 150, Layer::Floor, true);
	RectangleObject rect4(222, 222, 50, 50, Layer::Object, true);
	RectangleObject rect5(333, 333, 50, 50, Layer::Object, true);
	RectangleObject rect6(444, 444, 50, 50, Layer::Object, true);
	RectangleObject rect7(500, 630, 400, 300, Layer::Object, true);
	RectangleObject rect8(1000, 630, 50, 50, Layer::Object, true);
	CircleObject cir0(0, 0, 64, Layer::Object, true);
	Button btn1(1000, 100);
	//Model3D MGR("data/MGR�o�Mver1.3/MGR�o�M.pmx");
	//Model3D miku("data/Lat���~�N/Lat���~�NVer2.3_Normal.pmd");
	//rect1.vy = .5f;
	//rect4.vy = 2;
	//rect5.vy = 1;
	//rect6.vy = -1;
	//cir0.vx = .5f;
	//cir0.vy = .5f;

	//CSVEditor test("data/jb_6.csv");

	while (LoopProcess()) {
		DrawBox(0, 0, winx, winy, 0x7f7f7f, TRUE);
		gameProcessor->process();
	}

	GameProcessor::finalize();
	DxLib_End();

	return 0;
}