#include "MouseInput.h"

MouseInput::MouseInput() : _buttonPressingCount(), _buttonReleasingCount(), _x(), _y() {
}

//更新
bool MouseInput::Update() {
	int nowButtonState = GetMouseInput();
	GetMousePoint(&_x, &_y);
	for (int i = 0; i < KEY_NUM; i++) {
		if ((nowButtonState >> i) & 1) {            //i番のボタンが押されていたら
			if (_buttonReleasingCount[i] > 0) {//離されカウンタが0より大きければ
				_buttonReleasingCount[i] = 0;   //0に戻す
			}
			_buttonPressingCount[i]++;          //押されカウンタを増やす
		}
		else {                             //i番のキーが離されていたら
			if (_buttonPressingCount[i] > 0) { //押されカウンタが0より大きければ
				_buttonPressingCount[i] = 0;    //0に戻す
			}
			_buttonReleasingCount[i]++;         //離されカウンタを増やす
		}
	}
	return true;
}

//keyCodeのキーが押されているフレーム数を返す
int MouseInput::getPressingCount(int keyCode) {
	if (!isAvailableCode(keyCode)) {
		return -1;
	}
	return _buttonPressingCount[keyCode];
}

//keyCodeのキーが離されているフレーム数を返す
int MouseInput::getReleasingCount(int keyCode) {
	if (!isAvailableCode(keyCode)) {
		return -1;
	}
	return _buttonReleasingCount[keyCode];
}

//keyCodeが有効な値かチェックする
bool MouseInput::isAvailableCode(int keyCode) {
	if (!(0 <= keyCode && keyCode < KEY_NUM)) {
		return false;
	}
	return true;
}
