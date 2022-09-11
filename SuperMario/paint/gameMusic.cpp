#include"gameMusic.h"
#include"T_enginetest.h"
gameMusic::gameMusic() {
	isboom = false;
	

}
gameMusic::~gameMusic() {

}
void gameMusic::initResourse(HWND m_hWnd) {
	if (!ds.CreateDS(m_hWnd))
		return;
	backmusic_buffer.LoadWave(ds, L".\\sound\\backmusic.wav");
	robot_buffer.LoadWave(ds, L".\\sound\\walk.wav");
	robot_jump_buffer.LoadWave(ds, L".\\sound\\jump.wav");
	mousedown_buffer.LoadWave(ds, L".\\sound\\mousedown.wav");
	mousemove_buffer.LoadWave(ds, L".\\sound\\mouseover.wav");
	blast_buffer.LoadWave(ds, L".\\sound\\blast.wav");
	gamwLose_buffer.LoadWave(ds, L".\\sound\\lose.wav");
	gamwEnd_buffer.LoadWave(ds, L".\\sound\\gameover.wav");
	gameWin_buffer.LoadWave(ds, L".\\sound\\victory.wav");
	gamwEat_buffer.LoadWave(ds, L".\\sound\\eatmushroom.wav");
	gamwNext_buffer.LoadWave(ds, L".\\sound\\flag.wav");
	backmusic_buffer.Play(true);


};
void gameMusic::playmusic(int gameState, WPARAM keyaction1, bool isfold)


{
	//menuMusic->Terminate();			// ≤Àµ•…˘“Ù
	//backmusic_buffer.Terminate();			// ”Œœ∑±≥æ∞“Ù¿÷
	//gamwLose_buffer.Terminate();		// ”Œœ∑Ω· ¯…˘“Ù
	//gameWin_buffer.Terminate();
	//gamwLose_buffer.LoadWave(ds, L".\\sound\\lose.wav");
	//gamwEnd_buffer.LoadWave(ds, L".\\sound\\gameover.wav");
	//gameWin_buffer.LoadWave(ds, L".\\sound\\victory.wav");
	if (gameState == GAME_RUN && isfold)
	{

		int a = keyaction1;
		if (a == VK_A)
		{

			robot_buffer.Restore();
			robot_buffer.Play(false);

		}
		if (a == VK_D)
		{

			robot_buffer.Restore();
			robot_buffer.Play(false);

		}
		if (a == VK_SPACE )
		{

			robot_jump_buffer.Restore();
			robot_jump_buffer.Play(false);

		}
		if (islose == true)
		{
			gamwLose_buffer.Restore();
			gamwLose_buffer.Play(false);
			//Sleep(2000);
			islose = false;
			//gameState == GAME_RUN;

		}
		if (iseat == true) {
			gamwEat_buffer.Restore();
			gamwEat_buffer.Play(false);
			Sleep(1000);
			iseat = false;
		}


	}
	if (gameState == GAME_WIN)
	{
		gameWin_buffer.Restore();
		gameWin_buffer.Play(false);
	}
	if (gameState == GAME_NEXT) {

		gamwNext_buffer.Restore();
		gamwNext_buffer.Play(false);
		Sleep(2000);

	}

	if (gameState == GAME_END)
	{
		gamwEnd_buffer.Restore();
		gamwEnd_buffer.Play(false);
	}
}