#pragma once
#include"TinyEngine\T_Sprite.h"

class Goomba : public T_Sprite
{
public:
		static int  FRAME_RUN[6];
public:
	Goomba(LPCTSTR imgPath, int frameWidth = 0, int frameHeight = 0, int winWidth = WIN_WIDTH, int winHeight = WIN_HEIGHT);
	virtual ~Goomba();
	void setFalling(bool fall) { falling = fall; }
	bool getFalling() { return falling; }
	void updatePosition(int xDir, T_Map* pBarrier);
	void Gravityefect(T_Map* pBarrier);
private:
protected:
	int win_width, win_height;
	bool falling;
	int gravity;

};