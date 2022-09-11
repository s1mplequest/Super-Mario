#pragma once
#include"TinyEngine\T_Sprite.h"
class Flag : public T_Sprite
{
public:
public:
	Flag(LPCTSTR imgPath, int frameWidth , int frameHeight , int winWidth = WIN_WIDTH, int winHeight = WIN_HEIGHT);
	virtual ~Flag();
private:
protected:
	int win_width, win_height;
};