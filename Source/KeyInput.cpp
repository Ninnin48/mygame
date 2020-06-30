#include "KeyInput.h"


KeyInput::KeyInput()
{
	memset(mKeyPressingCount, 0, sizeof(mKeyPressingCount));
	memset(mKeyReleasingCount, 0, sizeof(mKeyReleasingCount));
}

//更新
bool KeyInput::Update() {
	char nowKeyStatus[KEY_NUM];
	GetHitKeyStateAll(nowKeyStatus);		//今のキーの入力状態を取得
	for (int i = 0; i < KEY_NUM; i++) {
		if (nowKeyStatus[i] != 0) {			//i番のキーが押されていたら
			if (mKeyReleasingCount[i] > 0) {//離されカウンタが0より大きければ
				mKeyReleasingCount[i] = 0;	//0に戻す
			}
			mKeyPressingCount[i]++;			//押されカウンタを増やす
		}
		else {								//i番のキーが離されていたら
			if (mKeyPressingCount[i] > 0) { //押されカウンタが0より大きければ
				mKeyPressingCount[i] = 0;	//0に戻す
			}
			mKeyReleasingCount[i]++;		//離されカウンタを増やす
		}
	}
	return true;
}

//keyCodeのキーが押されているフレーム数を返す
int KeyInput::GetPressingCount(int keyCode) {
	if (!KeyInput::IsAvailableCode(keyCode)) {
		return -1;
	}
	return mKeyPressingCount[keyCode];
}

//keyCodeのキーが離されているフレーム数を返す
int KeyInput::GetReleasingCount(int keyCode) {
	if (!KeyInput::IsAvailableCode(keyCode)) {
		return -1;
	}
	return mKeyReleasingCount[keyCode];
}

//keyCodeが有効な値かチェックする
bool KeyInput::IsAvailableCode(int keyCode) {
	if (!(0 <= keyCode && keyCode < KEY_NUM)) {
		return false;
	}
	return true;
}