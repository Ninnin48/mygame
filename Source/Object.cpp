#include "Object.h"

Object::Object(int px, int py) {
	setPosition(px, py);//x,y‚Ì‰Šú’l
	setHitArea(16, 16, 32, 32);//hit_x, hit_y, hit_width, hit_height‚Ì‰Šú’l
	hit_flag = false;
	remove_flag = false;
	VecMove = VGet(0.0f, 0.0f, 0.0f);
}

void Object::setPosition(int px, int py) {
	Vect = VGet(px, py, 0.0f);
}
void Object::setHitArea(int hx, int hy, int hw, int hh) {
	VecHitXY = VGet(hx, hy, 0.0f);
	VecHitWH = VGet(hw, hh, 0.0f);
}

bool Object::isRemove() {
	return remove_flag;
}

void Object::isCol() {

}

void Object::update() {
	hit_flag = false;
}
void Object::draw() {
	DrawBox(Vect.x - VecHitXY.x, Vect.y - VecHitXY.y, Vect.x + VecHitXY.x, Vect.y + VecHitXY.y, GetColor(255, 0, 255), TRUE);
}