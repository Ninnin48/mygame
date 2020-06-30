#pragma once
#include "DxLib.h"
#include "Object.h"

class Enemy : public Object
{
	bool shot_flag;
	VECTOR VecShotDir;

public:

	Enemy(int ex, int ey);
	void isCol();
	void update();
	void draw();
	void hit();
};

