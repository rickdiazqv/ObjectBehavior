#define __GLOBAL_INSTANCE__
#include "header.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	if (AllInit() != 0) { return -1; }

	//BaseObject obj;
	WorkManager& workManager = Singleton<WorkManager>::get_instance();
	RectangleObject rect1(111, 111, 50, 50, Layer::Object, true);
	RectangleObject rect2(333, 333, 100, 100, Layer::Default, true);
	RectangleObject rect3(555, 555, 150, 150, Layer::Floor, true);
	RectangleObject rect4(222, 222, 50, 50, Layer::Object, true);
	RectangleObject rect5(333, 333, 50, 50, Layer::Object, true);
	RectangleObject rect6(444, 444, 50, 50, Layer::Object, true);
	Model3D MGR("data/MGRŽo‹Mver1.3/MGRŽo‹M.pmx");
	rect1.vy = 3;
	rect4.vy = 2;
	rect5.vy = 1;
	rect6.vy = -1;
	workManager.receive();
	while (LoopProcess()) {
		DrawBox(0, 0, winx, winy, 0x7f7f7f, TRUE);
		workManager.update();
		workManager.draw();
	}
	SingletonFinalizer::finalize();
	DxLib_End();

	return 0;
}