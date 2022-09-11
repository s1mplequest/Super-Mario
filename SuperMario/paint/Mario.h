#pragma once
#include "TinyEngine\\T_Config.h"
#include "TinyEngine\\T_Sprite.h"
#include "TinyEngine\\T_Map.h"
enum VK_KEYVALUE
{
	VK_A = 0x41,
	VK_B, VK_C, VK_D, VK_E, VK_F, VK_G, VK_H, VK_I, VK_J, VK_K, VK_L, VK_M,
	VK_N, VK_O, VK_P, VK_Q, VK_R, VK_S, VK_T, VK_U, VK_V, VK_W, VK_X, VK_Y, VK_Z
};
enum PLAYERSTATUS {
	PLAYER_SMALL,
	PLAYER_BIG,
	PLAYER_ABILITY
};
class Mario : public T_Sprite
{
public:
	static int FRAME_RUN[6];
	static int FRAME_JUMP[1];
	static int FRAME_BIG[20];
	static int FRAME_STAND[1];
protected:
	// 与跳跃相关变量
	int jumpSpeed;
	int gravity;
	bool jumping;
	bool falling;
	int win_width, win_height;
	string name;
	PLAYERSTATUS playerstatus;

public:
	Mario(LPCTSTR imgPath, int frameWidth = 0, int frameHeight = 0, int winWidth = WIN_WIDTH, int winHeight = WIN_HEIGHT);
	virtual ~Mario();

	void setJumpSpeed(int jspeed) { jumpSpeed = jspeed; }
	int getJumpSpeed() { return jumpSpeed; }

	void SetName(string s) { name = s; }
	string GetName() { return name; }

	void setJumping(bool jump) { jumping = jump; }
	bool getJumping() { return jumping; }

	void setFalling(bool fall) { falling = fall; }
	bool getFalling() { return falling; }

	void setStaStus(PLAYERSTATUS status) { playerstatus = status; }
	PLAYERSTATUS getStaStus() { return playerstatus; }

	void updatePostion(int xDir, int yDir, int jumpDir, T_Map* pBarrier);
	void jumpUpDown(T_Map* pBarrier);
	void fallingDown();
	void StatusChange(PLAYERSTATUS status);
	void damage();
	void death();
	//void setY(){   }


};