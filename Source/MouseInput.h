#pragma once
#include "DxLib.h"
#include "Singleton.h"

class MouseInput : public Singleton<MouseInput> {

	MouseInput();
	friend Singleton< MouseInput >;

public:
	static constexpr int LEFT_CLICK = 0;
	static constexpr int RIGHT_CLICK = 1;

	bool Update();	//更新
	int getPressingCount(int keyCode);//keyCodeのキーが押されているフレーム数を取得
	int getReleasingCount(int keyCode);//keyCodeのキーが離されているフレーム数を取得
	int getX() { return _x; }
	int getY() { return _y; }

private:
	static constexpr int KEY_NUM = 8;	//キー総数
	int _x, _y;
	int _buttonPressingCount[KEY_NUM];//押されカウンタ
	int _buttonReleasingCount[KEY_NUM];//離されカウンタ

	bool isAvailableCode(int keyCode);//keyCodeが有効なキー番号か問う
};