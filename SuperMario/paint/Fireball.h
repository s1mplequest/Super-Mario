#pragma once
#include"TinyEngine\T_Sprite.h"
typedef vector<T_Sprite*> vBombSet;
class Fireball : public T_Sprite
{
public:
	static int FRAME_EXPLODE[3];
public:
	Fireball(LPCTSTR imgPath, int frameWidth = 0, int frameHeight = 0, int winWidth = WIN_WIDTH, int winHeight = WIN_HEIGHT);
	virtual ~Fireball();
private:
protected:
	int win_width, win_height;
};