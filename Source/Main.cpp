#include "Main.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//GameFrame *gf = new GameFrame();
	GameFrame gf;
	//gf->doMainLoop(TRUE);
	//delete gf;

	gf.MainLoop(TRUE);

	return 0;				// �\�t�g�̏I�� 
}
