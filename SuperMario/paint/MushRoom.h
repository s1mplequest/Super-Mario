#pragma once
#include"TinyEngine\T_Sprite.h"

class MushRoom : public T_Sprite
{

public:
		static int FRAME_STAND[1];
		MushRoom(LPCTSTR imgPath, int frameWidth = 0, int frameHeight = 0, int winWidth = WIN_WIDTH, int winHeight = WIN_HEIGHT);
		virtual ~MushRoom();
		void setFalling(bool fall) { falling = fall; }
		bool getFalling() { return falling; }
		void updatePosition(int xDir, T_Map* pBarrier);
		void Gravityefect(T_Map* pBarrier);

private:
	int mushroom_id;
	
protected:
	int win_width, win_height;
	bool falling;
	int gravity;

};