#pragma once
#include "Object.h"
#include "KeyInput.h"
#include "MouseInput.h"
#include "DxLib.h"

class Player : public Object
{
	bool shot_flag;
	int dead_time;

	unsigned int White;
public:

	Player(int px, int py);
	void isCol(VECTOR vn);
	void Collision();
	void update();
	void draw();
	void hit();
	void moveX();
	void moveY();
};