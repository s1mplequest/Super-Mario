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
		//������һ���ƶ��Ƿ񳬹��߽�
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
		//������һ���ƶ��Ƿ񳬹��߽�
		nextStepX = GetX() + GetRatioSize().cx + SpeedX;

		if (nextStepX >= win_width)
		{
			SpeedX = win_width - GetRatioSize().cx - GetX();
			SetDir(DIR_LEFT);
		}

	}
	int x = GetX();// ����ƶ�ǰ��xλ��
	int y = GetY();// ����ƶ�ǰ��yλ��

	if (!CollideWith(pBarrier))
	{
		Move(SpeedX, SpeedY);
	}
	if (CollideWith(pBarrier))
	{
		//SetPosition(x, y);		// ��ԭ�ƶ�ǰ��λ��
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
	//������һ���ƶ��Ƿ񳬹��߽�
	nextStepY = GetY() + GetRatioSize().cy + SpeedY;
	if (nextStepY >= win_height)
	{
		SpeedY = win_height - GetRatioSize().cy - GetY();
	}
	int x = GetX();// ����ƶ�ǰ��xλ��
	int y = GetY();// ����ƶ�ǰ��yλ��

	if (!CollideWith(pBarrier))
	{
		Move(SpeedX, SpeedY);	// �����ƶ�
	}
	if (CollideWith(pBarrier))
	{
		SetPosition(x, y);		// ��ԭ�ƶ�ǰ��λ��

	}
}
