#include "header.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	if (AllInit() != 0) { return -1; }

	//BaseObject obj;
	TaskManager& taskManager = Singleton<TaskManager>::get_instance();
	RectangleObject rect1(100, 50);
	RectangleObject rect2(150, 50, 100, 50);
	RectangleObject rect3(400, 200, 50, 50);
	while (LoopProcess()) {
		taskManager.update();
		taskManager.draw();
	}
	SingletonFinalizer::finalize();
	DxLib_End();

	return 0;
}