#include "Enemy.h"
Enemy::Enemy(int ex, int ey) : Object(ex, ey){
	setHitArea(10, 10, 10, 10);
	shot_flag = false;
	hit_flag = false;
	remove_flag = false;

}

void Enemy::isCol() {
	hit_flag = true;
	remove();
}
void Enemy::update() {

}
void Enemy::draw() {
	DrawBox(Vect.x - VecHitXY.x, Vect.y - VecHitXY.y, Vect.x + VecHitXY.x, Vect.y + VecHitXY.y, GetColor(0, 255, 0), TRUE);
}

void Enemy::hit() {
	remove();
}