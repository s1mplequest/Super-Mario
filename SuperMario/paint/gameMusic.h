#pragma once
#include"TinyEngine\T_Music.h"
#include"TinyEngine\T_Engine.h"
#include"TinyEngine\T_Audio.h"
//#include"TinyEngine\T_Menu.h"

class gameMusic :public AudioWave

{
public:
	AudioDX ds;
	AudioDXBuffer backmusic_buffer;
	AudioDXBuffer robot_buffer;
	AudioDXBuffer robot_jump_buffer;
	AudioDXBuffer mousedown_buffer;
	AudioDXBuffer mousemove_buffer;
	AudioDXBuffer blast_buffer;
	AudioDXBuffer jump_buffer;
	AudioDXBuffer gameWin_buffer;
	AudioDXBuffer gamwLose_buffer;
	AudioDXBuffer gamwEnd_buffer;
	AudioDXBuffer gamwEat_buffer;
	AudioDXBuffer gamwNext_buffer;
	bool keys[256];
	bool isboom;
	bool islose = false;
	bool iseat = false;
	bool isNext = false;
protected:


	//static	 AudioDXBuffer mousedown_buffer;
	//static  AudioDXBuffer mousemove_buffer;


public:
	gameMusic();
	~gameMusic();
	void gameMusic::playmusic(int gameState, WPARAM keyaction1, bool isfold);
	void gameMusic::initResourse(HWND m_hWnd);
	void setBoom(bool boom) { isboom = boom; };
	void setlose(bool boom) { islose = boom; };
	void seteat(bool boom) { iseat = boom; }
	void setNext(bool boom) { isNext = boom; }
	bool CheckKey(WPARAM wParam) { return keys[wParam]; }
};
