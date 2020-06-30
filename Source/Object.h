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
	VECTOR Vect;//���̂̒��S���W
	VECTOR VecHitXY;//���̂̒��S������܂ōs���̂ɕK�v�Ȑ��l
	VECTOR VecHitWH;//���̂̕�
	VECTOR VecMove;//���̂̐i�s�x�N�g��
	VECTOR VecMoveRev;//�i�s�x�N�g���̋t�x�N�g��
	VECTOR VecNor;//�@���x�N�g��
	VECTOR VecMouse;//�}�E�X�̈ʒu�x�N�g��
	int hp;

	Object(int px, int py);
	void setPosition(int px, int py);
	void setHitArea(int hx, int hy, int hw, int hh);
	bool isRemove();
	virtual void isCol();
	virtual void update();
	virtual void draw();

};

