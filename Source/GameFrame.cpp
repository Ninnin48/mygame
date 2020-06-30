#include "GameFrame.h"

GAMESTATE GameFrame::setGameState(GAMESTATE state) {
	if (gstate != state) {
		gstate = state;
		if (gstate == GAME_MAIN) initStage();//initStage�֐��̌Ăяo��
	}
	return gstate;
}

void GameFrame::MainLoop(int scmode) {

	SetMainWindowText("Game");		//�^�C�g����ύX
	ChangeWindowMode(scmode);		//�E�C���h�E���[�h�ɕύX
	SetGraphMode(W_Width, W_Height, Colorbit);		//��ʃ��[�h�̐ݒ�
	if (DxLib_Init() == -1)			//�c�w���C�u��������������
	{
		return;						//�G���[���N�����璼���ɏI��
	}
	
	SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠉�ʂɃZ�b�g
	SetMouseDispFlag(TRUE);			// �}�E�X��\����Ԃɂ���

	setGameState(GAME_TITLE);		//�^�C�g����ʂɐݒ�
	White = GetColor(255, 255, 255);//�����F�𔒂ɐݒ�

	loadFiles();
	//stage = new Stage;
	FontHandle = CreateFontToHandle(NULL, 40, 3);

	// ���[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();	// ��ʂ�����������
		
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

		//debug();		//�f�o�b�O�p�֐� �s�v�Ȃ�R�����g�A�E�g
		ScreenFlip();	// ����ʂ̓��e��\��ʂɔ��f������
	}

	DeleteFontToHandle(FontHandle);

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

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
	if (start_flag && wipe_flag) {//���C�v�\��
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
		MouseInput::Instance()->getY());//�}�E�X�̉�ʍ��W���擾
	DrawFormatString(0, 20, White, "%d %d",
		MouseInput::Instance()->getPressingCount(MouseInput::LEFT_CLICK),//���N���b�N�����Ă���ԃJ�E���g
		MouseInput::Instance()->getPressingCount(MouseInput::RIGHT_CLICK));//�E�N���b�N�����Ă���ԃJ�E���g
	DrawFormatString(0, 40, White, "Press Enter�F%d",
		KeyInput::Instance()->GetPressingCount(KEY_INPUT_RETURN));//Enter�L�[�������Ă���Ƃ��ɃJ�E���g
	DrawFormatString(0, 60, White, "Release Enter�F%d",
		KeyInput::Instance()->GetReleasingCount(KEY_INPUT_RETURN));//Enter�L�[�𗣂��Ă���Ƃ��ɃJ�E���g
	DrawFormatString(0, 80, White, "Sound On�F%d",
		CheckSoundMem(SHandle));
}
