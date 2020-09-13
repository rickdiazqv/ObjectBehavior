#include "header.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	if (AllInit() != 0) { return -1; }

	//BaseObject obj;
	TaskManager& taskManager = Singleton<TaskManager>::get_instance();
	RectangleObject rect1(111,111,50, 50, Layer::Object, true);
	RectangleObject rect2(333, 333, 100, 100, Layer::Default, true);
	RectangleObject rect3(555, 555, 150, 150, Layer::Floor, true);
	RectangleObject rect4(111, 222, 50, 50, Layer::Object, true);
	RectangleObject rect5(111, 333, 50, 50, Layer::Object, true);
	RectangleObject rect6(111, 444, 50, 50, Layer::Object, true);
	rect1.vy = 1;
	taskManager.receive();
	while (LoopProcess()) {
		taskManager.update();
		taskManager.draw();
	}
	SingletonFinalizer::finalize();
	DxLib_End();

	return 0;
}