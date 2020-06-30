#include "Shot.h"

Shot::Shot(int px, int py, int mx, int my, int speed, unsigned int Color) :Object(px, py) {
	VecMouse = VGet(mx, my, 0.0f);
	setHitArea(5, 5, 5, 5);
	VecDif = VSub(VecMouse, Vect);
	VecDif = VNorm(VecDif);//playerからマウスへの方向ベクトル
	VecMove = VGet(VecDif.x * speed, VecDif.y * speed, 0.0f);
	ShotColor = Color;//弾の色
}

void Shot::update() {
	//Vect = VAdd(Vect, VecMove);
	if (Vect.x > W_Width) remove();
	if (Vect.x < 0) remove();
	if (Vect.y > W_Height) remove();
	if (Vect.y < 0) remove();
	if (Reflect_count > 2)remove();
}

void Shot::draw() {
	DrawBox(Vect.x - VecHitXY.x, Vect.y - VecHitXY.y, Vect.x + VecHitXY.x, Vect.y + VecHitXY.y, ShotColor, TRUE);

}

void Shot::hit() {
	remove();
}

void Shot::isCol(VECTOR vn) {
	VecNor = vn;//法線ベクトル
	hit_flag = true;
	VecMoveRev = VGet(-VecMove.x, -VecMove.y, 0.0f);//進行ベクトルの逆ベクトル
	inner = VDot(VecMoveRev, VecNor);
	VecMove = VAdd(VecMove, VScale(VecNor, inner*2));
	Reflect_count++;
}
void Shot::moveX() {
	Vect.x = Vect.x + VecMove.x;
}
void Shot::moveY() {
	Vect.y = Vect.y + VecMove.y;
}