#include"Fireball.h"


Fireball::Fireball(LPCTSTR imgPath, int frameWidth, int frameHeight, int winWidth, int winHeight)
	:T_Sprite(imgPath, frameWidth, frameHeight)
{
	win_width = winWidth;
	win_height = winHeight;

}

Fireball::~Fireball()
{
}
