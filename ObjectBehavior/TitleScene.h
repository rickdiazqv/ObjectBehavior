#pragma once
#include "define.h"
#include "Scene.h"
#include "RectangleObject.h"
#include "CircleObject.h"
#include "Button.h"
#include "MouseListener.h"
#include "BackGround.h"
#include "VintageWindow.h"


class TitleScene : public Scene {
public:
	TitleScene();
	~TitleScene();

public:
	void update() override;
	void draw() override;

private:
	RectangleObject rect1 = RectangleObject(111, 800, 50, 50, Layer::Object, true);
	RectangleObject rect2 = RectangleObject(333, 222, 100, 100, Layer::Default, true);
	RectangleObject rect3 = RectangleObject(555, 555, 150, 150, Layer::Floor, true);
	RectangleObject rect4 = RectangleObject(222, 222, 50, 50, Layer::Object, true);
	RectangleObject rect5 = RectangleObject(333, 333, 50, 50, Layer::Object, true);
	RectangleObject rect6 = RectangleObject(444, 444, 50, 50, Layer::Object, true);
	RectangleObject rect7 = RectangleObject(500, 630, 400, 300, Layer::Object, true);
	RectangleObject rect8 = RectangleObject(1000, 630, 50, 50, Layer::Object, true);
	CircleObject cir0 = CircleObject(0, 0, 64, Layer::Object, true);
	//VintageWindow window = VintageWindow(400, 400, 600, 300);
	Button btn1 = Button(1000, 100);
	class ButtonListener : public MouseListener<Object*> {
	public:
		void onClick(Object* ev) override { printfDx("click "); }
		void onMouseDown(int index, Object* ev) override {}
		void onMouseUp(int index, Object* ev) override {}
		void onMouseEntry(Object* ev) override { printfDx("entry "); }
		void onMouseExit(Object* ev) override { printfDx("exit "); }
	} ml;
	//BackGround sea;
	//Model3D MGR("data/MGRŽo‹Mver1.3/MGRŽo‹M.pmx");
	//Model3D miku("data/LatŽ®ƒ~ƒN/LatŽ®ƒ~ƒNVer2.3_Normal.pmd");
	//rect1.vy = .5f;
	//rect4.vy = 2;
	//rect5.vy = 1;
	//rect6.vy = -1;
	//cir0.vx = .5f;
	//cir0.vy = .5f;
};

