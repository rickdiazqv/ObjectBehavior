#include "header.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	if (AllInit() != 0) { return -1; }

	//BaseObject obj;
	TaskManager& taskManager = Singleton<TaskManager>::get_instance();
	//RectangleObject rect0;
	RectangleObject rect1(111,111,50, 50, Layer::Object, true);
	printfDx("rect1:%x\n", &rect1);
	RectangleObject rect2(333, 333, 100, 100, Layer::Default, true);
	RectangleObject rect3(555, 555, 150, 150, Layer::Floor);
	while (LoopProcess()) {
		taskManager.update();
		taskManager.draw();
	}
	SingletonFinalizer::finalize();
	DxLib_End();

	return 0;
}