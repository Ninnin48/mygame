#pragma once
#include "DxLib.h"
#include "Singleton.h"

class KeyInput : public Singleton<KeyInput>
{
	KeyInput();
	friend Singleton< KeyInput >;

public:
	bool Update();	//更新
	int GetPressingCount(int keyCode);//keyCodeのキーが押されているフレーム数を取得
	int GetReleasingCount(int keyCode);//keyCodeのキーが離されているフレーム数を取得

private:
	static const int KEY_NUM = 256;	//キー総数
	int mKeyPressingCount[KEY_NUM];//押されカウンタ
	int mKeyReleasingCount[KEY_NUM];//離されカウンタ

	bool IsAvailableCode(int keyCode);//keyCodeが有効なキー番号か問う
};

