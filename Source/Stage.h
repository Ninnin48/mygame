#pragma once
#include "DxLib.h"
#include "Player.h"
#include "Shot.h"
#include "Enemy.h"
#include "Object.h"
#include <list>
#include <map>
#include <algorithm>
#include <random>

class Stage
{
	enum SOUNDSTATE {
		PLAYER_SHOT, PLAYER_DAMAGE, PLAYER_DEATH, 
		ENEMY_SHOT, ENEMY_DAMAGE, 
		SCORE10, SCORE100, SCORE1000,
		STATEMAX
	};
	std::list<Object> obj_list;
	std::list<Shot> shot_list;
	std::list<Shot> enshot_list;
	std::list<Enemy> enemy_list;

	static const int W_Width = 640;
	static const int W_Height = 480;
	static const int Grid = 32;
	int time=3;
	int fX, fY;
	int pvMapX, pvMapY;
	int enTime;
	int enShotTime;
	int score;
	int field[15][20] = { 
		{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},//0
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//1
		{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1},//2
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//3
		{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//4
		{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//5
		{1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//6
		{1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},//7
		{1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//8
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},//9
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},//10
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},//11
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},//12
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},//13
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} //14
	};
	int SoundFIleHandle[STATEMAX];
	Player* player;
	Object* obj;
	VECTOR pvPrev;
	VECTOR pvCurrent;
	VECTOR pvMove;
	VECTOR VNor = VGet(0, 0, 0);
	VECTOR pvHitXY;
	VECTOR pvHitWH;
	VECTOR pvLU, pvLD, pvRU, pvRD;//左上、左下、右上、右下
	VECTOR VecMouse;//マウスの位置ベクトル
	bool shot_flag;
	bool remove_flag = false;

	void ColDirectX();
	void ColDirectY();
	void ShotColX(Object& obj);
	void ShotColY(Object& obj);
	void ShotColEnemy(Shot& s);
	void ShotColPlayer(Shot& s);
	void LoadFile();

public:

	Stage();
	~Stage();
	void update();
	void draw();
	uint64_t getRand();
	bool isRemove();
	int isScore();
	void addList(Object& obj);
	void addList(Shot& s);
	void addListE(Shot& s);
	void addList(Enemy& e);
};

