#include "Main.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//GameFrame *gf = new GameFrame();
	GameFrame gf;
	//gf->doMainLoop(TRUE);
	//delete gf;

	gf.MainLoop(TRUE);

	return 0;				// ソフトの終了 
}
