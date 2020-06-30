#include "Player.h"

Player::Player(int px, int py) :Object(px, py) {
	setHitArea(5, 5, 10, 10);//hit_x, hit_y, hit_width, hit_heightの初期値
	shot_flag = false;
	dead_time = 0;
	hp = 3;

	White = GetColor(255, 255, 255);//文字色を白に設定
}

void Player::update() {

	hit_flag = false;

	VecMove = VGet(0.0f, 0.0f, 0.0f);
	VecNor = VGet(0.0f, 0.0f, 0.0f);
	if (KeyInput::Instance()->GetPressingCount(KEY_INPUT_A)) { //左に移動
		VecMove = VAdd(VecMove, VGet(-speed, 0.0f, 0.0f));
	}
	if (KeyInput::Instance()->GetPressingCount(KEY_INPUT_D)) {//右に移動 
		VecMove = VAdd(VecMove, VGet(speed, 0.0f, 0.0f));
	}
	if (KeyInput::Instance()->GetPressingCount(KEY_INPUT_W)) { //上に移動
		VecMove = VAdd(VecMove, VGet(0.0f, -speed, 0.0f));
	}
	if (KeyInput::Instance()->GetPressingCount(KEY_INPUT_S)) { //下に移動
		VecMove = VAdd(VecMove, VGet(0.0f, speed, 0.0f));
	}

	if (dead_time > 0) {
		dead_time--;
		return;
	}
	else {
		dead_time = 0;
	}
}

void Player::draw() {
	//プレイヤーの描画
	if (dead_time > 0 && dead_time % 4 < 2) { return; }
	DrawBox(Vect.x - VecHitXY.x, Vect.y - VecHitXY.y, Vect.x + VecHitXY.x, Vect.y + VecHitXY.y, GetColor(255, 255, 255), TRUE);

	//デバッグ用
	//DrawFormatString(0, 80, White, "x : %f, y : %f", Vect.x, Vect.y);
	//DrawFormatString(0, 100, White, "Vec(%f, %f)", VecMove.x, VecMove.y);
	//DrawFormatString(0, 120, White, "shot_flag : %d", shot_flag);
	//DrawFormatString(0, 140, White, "hit_flag : %d", hit_flag);
	//DrawFormatString(0, 160, White, "VecNor(%f, %f)", VecNor.x, VecNor.y);
}

void Player::hit() {
	if (dead_time > 0) return;
	hp--;
	if (hp > 0) {
		dead_time = 100;
	}
	else {
		remove();
	}
}

void Player::isCol(VECTOR vn) {
	VecNor = vn;//法線ベクトル
	hit_flag = true;
	Collision();
}

void Player::Collision() {

	//Vect = VSub(Vect, VecMove);//位置をもとに戻す
	VecMoveRev = VGet(-VecMove.x, -VecMove.y, 0.0f);//進行ベクトルの逆ベクトル
	inner = VDot(VecMoveRev, VecNor);
	VecMove = VAdd(VecMove, VScale(VecNor, inner));
	//VecMove = VAdd(VecMove, VScale(VecNor, speed));
	//Vect = VAdd(Vect, VecMove);
}
void Player::moveX() {
	//Vect = VAdd(Vect, VecMove);
	Vect.x = Vect.x + VecMove.x;
	//if (Vect.x - VecHitXY.x < 0) {							//画面左端の当たり判定
	//	VecMove = VGet(-speed, 0.0f, 0.0f);
	//	Vect = VSub(Vect, VecMove);
	//}
	//if (Vect.x - VecHitXY.x + VecHitWH.x > W_Width) {		//画面右端の当たり判定
	//	VecMove = VGet(speed, 0.0f, 0.0f);
	//	Vect = VSub(Vect, VecMove);
	//}
	//if (Vect.y - VecHitXY.y < 0) {							//画面上端の当たり判定
	//	VecMove = VGet(0.0f, -speed, 0.0f);
	//	Vect = VSub(Vect, VecMove);
	//}
	//if (Vect.y - VecHitXY.y + VecHitWH.y > W_Height) {	//画面下端の当たり判定
	//	VecMove = VGet(0.0f, speed, 0.0f);
	//	Vect = VSub(Vect, VecMove);
	//}
}
void Player::moveY() {
	Vect.y = Vect.y + VecMove.y;
}