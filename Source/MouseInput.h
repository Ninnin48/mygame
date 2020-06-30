#pragma once
#include "DxLib.h"
#include "Singleton.h"

class MouseInput : public Singleton<MouseInput> {

	MouseInput();
	friend Singleton< MouseInput >;

public:
	static constexpr int LEFT_CLICK = 0;
	static constexpr int RIGHT_CLICK = 1;

	bool Update();	//�X�V
	int getPressingCount(int keyCode);//keyCode�̃L�[��������Ă���t���[�������擾
	int getReleasingCount(int keyCode);//keyCode�̃L�[��������Ă���t���[�������擾
	int getX() { return _x; }
	int getY() { return _y; }

private:
	static constexpr int KEY_NUM = 8;	//�L�[����
	int _x, _y;
	int _buttonPressingCount[KEY_NUM];//������J�E���^
	int _buttonReleasingCount[KEY_NUM];//������J�E���^

	bool isAvailableCode(int keyCode);//keyCode���L���ȃL�[�ԍ����₤
};