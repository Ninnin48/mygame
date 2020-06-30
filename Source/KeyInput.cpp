#include "KeyInput.h"


KeyInput::KeyInput()
{
	memset(mKeyPressingCount, 0, sizeof(mKeyPressingCount));
	memset(mKeyReleasingCount, 0, sizeof(mKeyReleasingCount));
}

//�X�V
bool KeyInput::Update() {
	char nowKeyStatus[KEY_NUM];
	GetHitKeyStateAll(nowKeyStatus);		//���̃L�[�̓��͏�Ԃ��擾
	for (int i = 0; i < KEY_NUM; i++) {
		if (nowKeyStatus[i] != 0) {			//i�Ԃ̃L�[��������Ă�����
			if (mKeyReleasingCount[i] > 0) {//������J�E���^��0���傫�����
				mKeyReleasingCount[i] = 0;	//0�ɖ߂�
			}
			mKeyPressingCount[i]++;			//������J�E���^�𑝂₷
		}
		else {								//i�Ԃ̃L�[��������Ă�����
			if (mKeyPressingCount[i] > 0) { //������J�E���^��0���傫�����
				mKeyPressingCount[i] = 0;	//0�ɖ߂�
			}
			mKeyReleasingCount[i]++;		//������J�E���^�𑝂₷
		}
	}
	return true;
}

//keyCode�̃L�[��������Ă���t���[������Ԃ�
int KeyInput::GetPressingCount(int keyCode) {
	if (!KeyInput::IsAvailableCode(keyCode)) {
		return -1;
	}
	return mKeyPressingCount[keyCode];
}

//keyCode�̃L�[��������Ă���t���[������Ԃ�
int KeyInput::GetReleasingCount(int keyCode) {
	if (!KeyInput::IsAvailableCode(keyCode)) {
		return -1;
	}
	return mKeyReleasingCount[keyCode];
}

//keyCode���L���Ȓl���`�F�b�N����
bool KeyInput::IsAvailableCode(int keyCode) {
	if (!(0 <= keyCode && keyCode < KEY_NUM)) {
		return false;
	}
	return true;
}