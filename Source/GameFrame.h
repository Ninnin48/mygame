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

	void drawGameTitle();	//�^�C�g����ʂ�`��
	void drawGameMain();	//�Q�[���{�̉�ʂ�`��
	void drawGameOver();	//�Q�[���I�[�o�[��ʂ�`��
	void drawGameClear();	//�Q�[���N���A��ʂ�`��
	void loadFiles();		//�t�@�C���̓ǂݍ���
	void initStage();		//�X�e�[�W�̏�����
	void Wipe();			//���C�v�\��
	void debug();			//�f�o�b�O�p�֐�

	GAMESTATE gstate;		//���݂̉�ʃ��[�h��\���ϐ�
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
	GAMESTATE setGameState(GAMESTATE state);	//gstate�ύX�֐�
public:
	~GameFrame() {}			//�f�X�g���N�^
	void MainLoop(int scmode);	//���C�����[�v�̎��s
	
	//Player* player;
	Stage* stage;
	//Test* test;
};