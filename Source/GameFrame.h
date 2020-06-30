#pragma once
#include "DxLib.h"
#include "MouseInput.h"
#include "KeyInput.h"
#include "Player.h"
#include "Shot.h"
#include "Stage.h"
//#include "Test.h"

enum GAMESTATE {
	GAME_TITLE = 1, GAME_MAIN, GAME_OVER, GAME_CLEAR
};

class GameFrame
{

	void drawGameTitle();	//タイトル画面を描画
	void drawGameMain();	//ゲーム本体画面を描画
	void drawGameOver();	//ゲームオーバー画面を描画
	void drawGameClear();	//ゲームクリア画面を描画
	void loadFiles();		//ファイルの読み込み
	void initStage();		//ステージの初期化
	void Wipe();			//ワイプ表現
	void debug();			//デバッグ用関数

	GAMESTATE gstate;		//現在の画面モードを表す変数
	unsigned int White;
	static const int W_Width = 640;
	static const int W_Height = 480;
	static const int Colorbit = 32;
	int score;
	int FontHandle;
	int wipe = 0;
	int SHandle;
	bool start_flag = false;
	bool wipe_flag = false;

protected:
	GAMESTATE setGameState(GAMESTATE state);	//gstate変更関数
public:
	~GameFrame() {}			//デストラクタ
	void MainLoop(int scmode);	//メインループの実行
	
	//Player* player;
	Stage* stage;
	//Test* test;
};