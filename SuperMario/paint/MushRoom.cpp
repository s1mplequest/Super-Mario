#include"MushRoom.h"
int MushRoom::FRAME_STAND[1] = { 0 };
MushRoom::MushRoom(LPCTSTR imgPath, int frameWidth, int frameHeight, int winWidth, int winHeight)
	:T_Sprite(imgPath, frameWidth, frameHeight)
{
	falling = false;
	gravity = 2;
	win_width = winWidth;
	win_height = winHeight;
}

MushRoom::~MushRoom()
{
}
void MushRoom::updatePosition(int xDir, T_Map* pBarrier)
{
	int nextStepX, nextStepY;
	int SpeedX = 0, SpeedY = 0;

	int movingSpeed = 0;


	if (xDir == DIR_LEFT)
	{
		SpeedX = -GetSpeed();
		SpeedY = 0;
		//计算下一步移动是否超过边界
		nextStepX = GetX() + SpeedX;
		if (nextStepX <= 0)
		{
			SpeedX = 0 - GetX();
			SetDir(DIR_RIGHT);
		}

	}
	if (xDir == DIR_RIGHT)
	{
		SpeedX = GetSpeed();
		SpeedY = 0;
		//计算下一步移动是否超过边界
		nextStepX = GetX() + GetRatioSize().cx + SpeedX;

		if (nextStepX >= win_width)
		{
			SpeedX = win_width - GetRatioSize().cx - GetX();
			SetDir(DIR_LEFT);
		}

	}
	int x = GetX();// 获得移动前的x位置
	int y = GetY();// 获得移动前的y位置

	if (!CollideWith(pBarrier))
	{
		Move(SpeedX, SpeedY);
	}
	if (CollideWith(pBarrier))
	{
		//SetPosition(x, y);		// 还原移动前的位置
		if (xDir == DIR_RIGHT)
		{
			SetDir(DIR_LEFT);
		}
		else
		{
			SetDir(DIR_RIGHT);
		}
		
	}
}
void MushRoom::Gravityefect(T_Map* pBarrier)
{
	int nextStepX, nextStepY;
	int SpeedX = 0, SpeedY = 0;
	SpeedX = 0;
	SpeedY = gravity;
	//计算下一步移动是否超过边界
	nextStepY = GetY() + GetRatioSize().cy + SpeedY;
	if (nextStepY >= win_height)
	{
		SpeedY = win_height - GetRatioSize().cy - GetY();
	}
	int x = GetX();// 获得移动前的x位置
	int y = GetY();// 获得移动前的y位置

	if (!CollideWith(pBarrier))
	{
		Move(SpeedX, SpeedY);	// 继续移动
	}
	if (CollideWith(pBarrier))
	{
		SetPosition(x, y);		// 还原移动前的位置

	}
}
