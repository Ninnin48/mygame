#pragma once
#include "KeyInput.h"
#include "MouseInput.h"
#include "DxLib.h"

class Object
{
protected:
	static const int W_Width = 640;
	static const int W_Height = 480;
	float speed = 3.0f;
	float inner;
	bool hit_flag;
	bool remove_flag;
	void remove() { remove_flag = true; }
public:
	VECTOR Vect;//物体の中心座標
	VECTOR VecHitXY;//物体の中心→左上まで行くのに必要な数値
	VECTOR VecHitWH;//物体の幅
	VECTOR VecMove;//物体の進行ベクトル
	VECTOR VecMoveRev;//進行ベクトルの逆ベクトル
	VECTOR VecNor;//法線ベクトル
	VECTOR VecMouse;//マウスの位置ベクトル
	int hp;

	Object(int px, int py);
	void setPosition(int px, int py);
	void setHitArea(int hx, int hy, int hw, int hh);
	bool isRemove();
	virtual void isCol();
	virtual void update();
	virtual void draw();

};

