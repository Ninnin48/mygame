#include "Stage.h"


Stage::Stage()
{
	// プレイヤー生成
	player = new Player(7*Grid + Grid/2, 10*Grid + Grid/2);
	//ステージ生成
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 20; j++) {
			if (field[i][j] == 1) {
				Object object = Object(j * Grid + Grid/2, i * Grid + Grid / 2);
				addList(object);
			}
		}

	}
	enTime = 0;
	enShotTime = 0;
	score = 0;
	LoadFile();
}


Stage::~Stage()
{
}

void Stage::update() {

	if (player->isRemove()) { 
		PlaySoundMem(SoundFIleHandle[PLAYER_DEATH], DX_PLAYTYPE_BACK);
		remove_flag = true; 
	}//プレイヤーのHPが0になったらステージ終了
	
	// プレイヤー移動 ////////////////////////////
	player->update();//プレイヤー入力更新
	VNor = VGet(0,0,0);
	ColDirectX();
	if (VNor.x != 0) {
		VNor = VNorm(VNor);
		player->isCol(VNor);
	}
	player->moveX();//プレイヤーX移動

	VNor = VGet(0, 0, 0);
	ColDirectY();
	if (VNor.y != 0) {
		VNor = VNorm(VNor);
		player->isCol(VNor);
	}
	player->moveY();//プレイヤーY移動
	/////////////////////////////////////////////

	//エネミー生成処理///////////////////////////
	enTime++;
	if (enTime > getRand() % 50 + 50) {
		enTime = 0;
		while (1) {
			Enemy enemy = Enemy(getRand() % 640, getRand() % 480);
			if (field[(int)enemy.Vect.y / Grid][(int)enemy.Vect.x / Grid] == 0) {
				addList(enemy);
				break;
			}
			else {
				enemy.hit();
				addList(enemy);
				auto erase = std::remove_if(enemy_list.begin(), enemy_list.end(), [](Enemy& e) {return e.isRemove(); });
				enemy_list.erase(erase, enemy_list.end());
			}
		}
	}
	/////////////////////////////////////////////

	//プレイヤーのショットの処理////////////////
	if (MouseInput::Instance()->getPressingCount(MouseInput::LEFT_CLICK)) {//マウス左クリックで弾を打つ
		VecMouse = VGet(MouseInput::Instance()->getX(), MouseInput::Instance()->getY(), 0.0f);
		if (!shot_flag) {
			Shot shot = Shot(player->Vect.x, player->Vect.y, VecMouse.x, VecMouse.y, 5, GetColor(255, 255, 0));
			addList(shot);
			shot_flag = true;
			PlaySoundMem(SoundFIleHandle[PLAYER_SHOT], DX_PLAYTYPE_BACK);
		}
	}
	else {
		shot_flag = false;
	}
	////////////////////////////////////////////

	//エネミーのショットの処理/////////////////
	enShotTime++;
	if (enShotTime > 300) {
		for (auto& e : enemy_list) {
			Shot shotE = Shot(e.Vect.x, e.Vect.y, player->Vect.x, player->Vect.y, 2, GetColor(255, 0, 0));
			addListE(shotE);
		}
		PlaySoundMem(SoundFIleHandle[ENEMY_SHOT], DX_PLAYTYPE_BACK);
		enShotTime = 0;
	}
	//////////////////////////////////////////

	//ショットの衝突処理//////////////////////
	for (auto& s : shot_list) {//プレイヤーの弾が衝突
		VNor = VGet(0, 0, 0);
		ShotColX(s);
		if (VNor.x != 0) {
			VNor = VNorm(VNor);
			s.isCol(VNor);
		}
		s.moveX();
		VNor = VGet(0, 0, 0);
		ShotColY(s);
		if (VNor.y != 0) {
			VNor = VNorm(VNor);
			s.isCol(VNor);
		}
		s.moveY();
		s.update();

		ShotColEnemy(s);//エネミーに衝突
	}

	for (auto& s : enshot_list) {//エネミーの弾が壁に衝突
		VNor = VGet(0, 0, 0);
		ShotColX(s);
		if (VNor.x != 0) {
			VNor = VNorm(VNor);
			s.isCol(VNor);
		}
		s.moveX();
		VNor = VGet(0, 0, 0);
		ShotColY(s);
		if (VNor.y != 0) {
			VNor = VNorm(VNor);
			s.isCol(VNor);
		}
		s.moveY();
		s.update();

		ShotColPlayer(s);//プレイヤーに衝突
	}
	//////////////////////////////////////////////////

	//オブジェクトの削除判定/////////////////////////
	auto endE = std::remove_if(enemy_list.begin(), enemy_list.end(), [](Enemy& e) {return e.isRemove(); });
	enemy_list.erase(endE, enemy_list.end());
	auto end = std::remove_if(shot_list.begin(), shot_list.end(), [](Shot& s) {return s.isRemove(); });
	shot_list.erase(end, shot_list.end());
	auto endES = std::remove_if(enshot_list.begin(), enshot_list.end(), [](Shot& s) {return s.isRemove(); });
	shot_list.erase(endES, enshot_list.end());
	///////////////////////////////////////////////
}

void Stage::draw() {
	//ステージの描画
	std::for_each(obj_list.begin(), obj_list.end(), [](Object& o) {o.draw(); });

	// 描画
	player->draw();//プレイヤーの描画
	std::for_each(enemy_list.begin(), enemy_list.end(), [](Enemy& e) {e.draw(); });
	std::for_each(shot_list.begin(), shot_list.end(), [](Shot& s) {s.draw(); });//プレイヤーのショットの描画
	std::for_each(enshot_list.begin(), enshot_list.end(), [](Shot& es) {es.draw(); });
	DrawFormatString(0, 0, GetColor(255, 255, 255), "HP : %d", player->hp);
	DrawFormatString(80, 0, GetColor(255, 255, 255), "Score : %d", score);
	//デバッグ用
	//DrawFormatString(0, 260, GetColor(255, 255, 255), "Player MapXY: %d, %d", pvMapX, pvMapY);
	//DrawFormatString(0, 260, GetColor(255, 255, 255), "Player MapXY: %f, %f", pvNor.x, pvNor.y);
}

void Stage::ColDirectX() {
	if (field[(int)player->Vect.y / Grid][(int)player->Vect.x / Grid + 1] == 1 &&
		player->Vect.x - player->VecHitXY.x + player->VecHitWH.x + player->VecMove.x > ((int)player->Vect.x / Grid + 1) * Grid &&
		player->VecMove.x > 0) {//右側のx移動判定 
		VNor = VAdd(VNor, VGet(-1.0f, 0.0f, 0.0f));
		return;
	}
	if (field[(int)player->Vect.y / Grid][(int)player->Vect.x / Grid - 1] == 1 &&
		player->Vect.x - player->VecHitXY.x + player->VecMove.x < (int)player->Vect.x / Grid * Grid&&
		player->VecMove.x < 0) {//左側のx移動判定
		VNor = VAdd(VNor, VGet(1.0f, 0.0f, 0.0f));
		return;
	}
}

void Stage::ColDirectY() {
	if (field[(int)player->Vect.y / Grid + 1][(int)player->Vect.x / Grid] == 1 &&
		player->Vect.y - player->VecHitXY.y + player->VecHitWH.y + player->VecMove.y > ((int)player->Vect.y / Grid + 1)* Grid&&
		player->VecMove.y > 0) {//下側のx移動判定 
		VNor = VAdd(VNor, VGet(0.0f, -1.0f, 0.0f));
		return;
	}
	if (field[(int)player->Vect.y / Grid - 1][(int)player->Vect.x / Grid] == 1 &&
		player->Vect.y - player->VecHitXY.y + player->VecMove.y < (int)player->Vect.y / Grid * Grid &&
		player->VecMove.y < 0) {//上側のx移動判定
		VNor = VAdd(VNor, VGet(0.0f, 1.0f, 0.0f));
		return;
	}
}

void Stage::ShotColX(Object& obj) {
	if (field[(int)obj.Vect.y / Grid][(int)obj.Vect.x / Grid + 1] == 1 &&
		obj.Vect.x - obj.VecHitXY.x + obj.VecHitWH.x + obj.VecMove.x > ((int)obj.Vect.x / Grid + 1)* Grid&&
		obj.VecMove.x > 0) {//右側のx移動判定 
		VNor = VAdd(VNor, VGet(-1.0f, 0.0f, 0.0f));
		return;
	}
	if (field[(int)obj.Vect.y / Grid][(int)obj.Vect.x / Grid - 1] == 1 &&
		obj.Vect.x - obj.VecHitXY.x + obj.VecMove.x < (int)obj.Vect.x / Grid * Grid &&
		obj.VecMove.x < 0) {//左側のx移動判定
		VNor = VAdd(VNor, VGet(1.0f, 0.0f, 0.0f));
		return;
	}
}

void Stage::ShotColY(Object& obj) {
	if (field[(int)obj.Vect.y / Grid + 1][(int)obj.Vect.x / Grid] == 1 &&
		obj.Vect.y - obj.VecHitXY.y + obj.VecHitWH.y + obj.VecMove.y > ((int)obj.Vect.y / Grid + 1)* Grid&&
		obj.VecMove.y > 0) {//下側のy移動判定 
		VNor = VAdd(VNor, VGet(0.0f, -1.0f, 0.0f));
		return;
	}
	if (field[(int)obj.Vect.y / Grid - 1][(int)obj.Vect.x / Grid] == 1 &&
		obj.Vect.y - obj.VecHitXY.y + obj.VecMove.y < (int)obj.Vect.y / Grid * Grid &&
		obj.VecMove.y < 0) {//左側のx移動判定
		VNor = VAdd(VNor, VGet(0.0f, 1.0f, 0.0f));
		return;
	}
}

void Stage::ShotColEnemy(Shot& s) {
	for (auto& e : enemy_list) {
		if (abs(s.Vect.x - e.Vect.x) < (s.VecHitWH.x + e.VecHitWH.x) / 2 &&
			abs(s.Vect.y - e.Vect.y) < (s.VecHitWH.y + e.VecHitWH.y) / 2) {
			if (s.Reflect_count == 1) {
				score += 100;
				PlaySoundMem(SoundFIleHandle[SCORE100], DX_PLAYTYPE_BACK);
			}
			else if (s.Reflect_count == 2) {
				score += 1000;
				PlaySoundMem(SoundFIleHandle[SCORE1000], DX_PLAYTYPE_BACK);
			}
			else {
				score += 10;
				PlaySoundMem(SoundFIleHandle[SCORE10], DX_PLAYTYPE_BACK);
			}
			e.hit();
			s.hit();
			PlaySoundMem(SoundFIleHandle[ENEMY_DAMAGE], DX_PLAYTYPE_BACK);
		}
	}
}

void Stage::ShotColPlayer(Shot& s) {
	if (abs(s.Vect.x - player->Vect.x) < (s.VecHitWH.x + player->VecHitWH.x) / 2 &&
		abs(s.Vect.y - player->Vect.y) < (s.VecHitWH.y + player->VecHitWH.y) / 2) {
		s.hit();
		player->hit();
		PlaySoundMem(SoundFIleHandle[PLAYER_DAMAGE], DX_PLAYTYPE_BACK);
	}
}

void Stage::LoadFile() {
	SoundFIleHandle[PLAYER_SHOT] = LoadSoundMem("Sound\\Player_Shot.mp3");
	SoundFIleHandle[PLAYER_DAMAGE] = LoadSoundMem("Sound\\Player_Damage.mp3");
	SoundFIleHandle[PLAYER_DEATH] = LoadSoundMem("Sound\\Player_Death.mp3");
	SoundFIleHandle[ENEMY_SHOT] = LoadSoundMem("Sound\\Enemy_Shot.mp3");
	SoundFIleHandle[ENEMY_DAMAGE] = LoadSoundMem("Sound\\Enemy_Damage.mp3");
	SoundFIleHandle[SCORE10] = LoadSoundMem("Sound\\Score10.mp3");
	SoundFIleHandle[SCORE100] = LoadSoundMem("Sound\\Score100.mp3");
	SoundFIleHandle[SCORE1000] = LoadSoundMem("Sound\\Score1000.mp3");
}

bool Stage::isRemove() {
	return remove_flag;
}

int Stage::isScore() {
	return score;
}

uint64_t Stage::getRand() {
	static std::mt19937_64 mt64(0);
	return mt64();
}

void Stage::addList(Object& obj) {
	obj_list.push_back(obj);
}

void Stage::addList(Shot& s) {
	shot_list.push_back(s);
}

void Stage::addListE(Shot& s) {
	enshot_list.push_back(s);
}

void Stage::addList(Enemy& e) {
	enemy_list.push_back(e);
}