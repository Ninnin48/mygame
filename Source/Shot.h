#pragma once
#include "DxLib.h"
#include "Object.h"

class Shot : public Object
{

public:
	VECTOR VecDif;
	int Reflect_count = 0;
	unsigned int ShotColor;

	Shot(int px, int py, int mx, int my, int speed, unsigned int Color);
	void isCol(VECTOR vn);
	void update();
	void draw();
	void hit();
	void moveX();
	void moveY();
};

