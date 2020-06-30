#pragma once
#include "DxLib.h"
#include "Singleton.h"

class KeyInput : public Singleton<KeyInput>
{
	KeyInput();
	friend Singleton< KeyInput >;

public:
	bool Update();	//�X�V
	int GetPressingCount(int keyCode);//keyCode�̃L�[��������Ă���t���[�������擾
	int GetReleasingCount(int keyCode);//keyCode�̃L�[��������Ă���t���[�������擾

private:
	static const int KEY_NUM = 256;	//�L�[����
	int mKeyPressingCount[KEY_NUM];//������J�E���^
	int mKeyReleasingCount[KEY_NUM];//������J�E���^

	bool IsAvailableCode(int keyCode);//keyCode���L���ȃL�[�ԍ����₤
};

