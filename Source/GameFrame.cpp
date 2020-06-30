#include "GameFrame.h"

GAMESTATE GameFrame::setGameState(GAMESTATE state) {
	if (gstate != state) {
		gstate = state;
		if (gstate == GAME_MAIN) initStage();//initStage関数の呼び出し
	}
	return gstate;
}

void GameFrame::MainLoop(int scmode) {

	SetMainWindowText("Game");		//タイトルを変更
	ChangeWindowMode(scmode);		//ウインドウモードに変更
	SetGraphMode(W_Width, W_Height, Colorbit);		//画面モードの設定
	if (DxLib_Init() == -1)			//ＤＸライブラリ初期化処理
	{
		return;						//エラーが起きたら直ちに終了
	}
	
	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏画面にセット
	SetMouseDispFlag(TRUE);			// マウスを表示状態にする

	setGameState(GAME_TITLE);		//タイトル画面に設定
	White = GetColor(255, 255, 255);//文字色を白に設定

	loadFiles();
	//stage = new Stage;
	FontHandle = CreateFontToHandle(NULL, 40, 3);

	// ループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();	// 画面を初期化する
		
		MouseInput::Instance()->Update();
		KeyInput::Instance()->Update();

		switch (gstate)
		{
		case GAME_TITLE:
			drawGameTitle();
			break;
		case GAME_MAIN:
			drawGameMain();
			break;
		case GAME_OVER:
			drawGameOver();
			break;
		case GAME_CLEAR:
			drawGameClear();
			break;
		}

		//debug();		//デバッグ用関数 不要ならコメントアウト
		ScreenFlip();	// 裏画面の内容を表画面に反映させる
	}

	DeleteFontToHandle(FontHandle);

	DxLib_End();				// ＤＸライブラリ使用の終了処理

}

void GameFrame::drawGameTitle() {
	if (MouseInput::Instance()->getPressingCount(MouseInput::LEFT_CLICK) > 1) {
		start_flag = true;
		wipe_flag = true;
		stage = new Stage;
		setGameState(GAME_MAIN);
		PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);

	}
	if (!wipe_flag) {
		DrawStringToHandle(W_Width / 3 - 60, W_Height / 3, "REFLECT SHOOTING", White, FontHandle);
		DrawFormatString(W_Width / 2 - 80, W_Height / 2 + 20, White, "Please Left Click");
	}
	Wipe();
}

void GameFrame::drawGameMain() {
	if (stage->isRemove()) { 
		start_flag = true;
		wipe_flag = true;
		setGameState(GAME_OVER); 
	}

	if (!wipe_flag) { stage->draw(); }
	if (!start_flag) { stage->update(); }

	Wipe();
}

void GameFrame::drawGameOver() {
	if (MouseInput::Instance()->getPressingCount(MouseInput::RIGHT_CLICK) > 1) {
		start_flag = true;
		wipe_flag = true;
		setGameState(GAME_TITLE);
		PlaySoundMem(SHandle, DX_PLAYTYPE_BACK);
	}
	if (!wipe_flag) {
		DrawStringToHandle(W_Width / 2 - 100, W_Height / 3, "GAME OVER", White, FontHandle);
		DrawFormatString(W_Width / 2 - 80, W_Height / 2 + 20, White, "Score : %d", stage->isScore());
		DrawFormatString(W_Width / 2 - 80, W_Height / 2 + 40, White, "Please Right Click");
	}
	Wipe();

}

void GameFrame::drawGameClear() {
	DrawFormatString(W_Width / 2, W_Height / 2, White, "GAME CLEAR");
}

void GameFrame::loadFiles() {
	//SHandle = LoadSoundMem("Source\\Sound\\Click.mp3");
	SHandle = LoadSoundMem("Sound\\Click.mp3");
}

void GameFrame::initStage() {

}

void GameFrame::Wipe() {
	if (start_flag && wipe_flag) {//ワイプ表現
		DrawBox(0, 0, W_Width, W_Height / 10 * (wipe + 1), GetColor(255, 255, 255), TRUE);
		WaitTimer(50);
		wipe++;
	}
	if (wipe == 10) { wipe_flag = false; }

	if (start_flag && !wipe_flag) {
		wipe--;
		DrawBox(0, 0, W_Width, W_Height / 10 * (wipe + 1), GetColor(255, 255, 255), TRUE);
		WaitTimer(50);
	}
	if (wipe == 0) { start_flag = false; }
}

void GameFrame::debug() {
	DrawFormatString(0, 0, White, "%d, %d",
		MouseInput::Instance()->getX(),
		MouseInput::Instance()->getY());//マウスの画面座標を取得
	DrawFormatString(0, 20, White, "%d %d",
		MouseInput::Instance()->getPressingCount(MouseInput::LEFT_CLICK),//左クリックをしている間カウント
		MouseInput::Instance()->getPressingCount(MouseInput::RIGHT_CLICK));//右クリックをしている間カウント
	DrawFormatString(0, 40, White, "Press Enter：%d",
		KeyInput::Instance()->GetPressingCount(KEY_INPUT_RETURN));//Enterキーを押しているときにカウント
	DrawFormatString(0, 60, White, "Release Enter：%d",
		KeyInput::Instance()->GetReleasingCount(KEY_INPUT_RETURN));//Enterキーを離しているときにカウント
	DrawFormatString(0, 80, White, "Sound On：%d",
		CheckSoundMem(SHandle));
}
