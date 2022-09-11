#include "Mario.h"

int Mario::FRAME_RUN[6] = { 4,4,5,5,6,6 };
int Mario::FRAME_JUMP[1] = {7};
int Mario::FRAME_BIG[20] = {0,11,0,11,0,11,0,11,0,11,0,11,0,11,0,11,0,11,0,11};
int Mario::FRAME_STAND[1] = { 0 };
Mario::Mario(LPCTSTR imgPath, int frameWidth, int frameHeight, int winWidth, int winHeight)
	:T_Sprite(imgPath, frameWidth, frameHeight)
{
	win_width = winWidth;
	win_height = winHeight;

	jumpSpeed = -16;
	gravity = 1;
	jumping = false;
	falling = false;
	playerstatus = PLAYER_SMALL;
}

Mario::~Mario()
{
}

void Mario::updatePostion(int xDir, int yDir, int jumpDir, T_Map* pBarrier)
{
	int nextStepX, nextStepY;
	int SpeedX = 0, SpeedY = 0;

	int movingSpeed = 0;
	if (jumpDir == DIR_DOWN || jumpDir == DIR_UP)// ����������
	{
		if (jumpDir == DIR_UP)
		{
			movingSpeed = -jumpSpeed;
		}
		if (jumpDir == DIR_DOWN)
		{
			movingSpeed = jumpSpeed;
		}
	}
	else
	{
		movingSpeed = GetSpeed();
	}

	if (yDir == DIR_UP)
	{
		SpeedX = 0;
		SpeedY = -movingSpeed;
		//������һ���ƶ��Ƿ񳬹��߽�
		nextStepY = GetY() + SpeedY;
		if (nextStepY <= 0)
		{
			SpeedY = 0 - GetY();
		}
	}

	if (yDir == DIR_DOWN)
	{
		SpeedX = 0;
		SpeedY = movingSpeed;
		//������һ���ƶ��Ƿ񳬹��߽�
		nextStepY = GetY() + GetRatioSize().cy + SpeedY;
		if (nextStepY >= win_height)
		{
			SpeedY = win_height - GetRatioSize().cy - GetY();
		}
	}

	if (xDir == DIR_LEFT)
	{
		SpeedX = -movingSpeed;
		SpeedY = 0;
		//������һ���ƶ��Ƿ񳬹��߽�
		nextStepX = GetX() + SpeedX;
		if (nextStepX <= 0)
		{
			SpeedX = 0 - GetX();
		}
		if (falling == false)
		{
			fallingDown();
		}
	}
	if (xDir == DIR_RIGHT)
	{
		SpeedX = movingSpeed;
		SpeedY = 0;
		//������һ���ƶ��Ƿ񳬹��߽�
		nextStepX = GetX() + GetRatioSize().cx + SpeedX;
		if (nextStepX >= win_width)
		{
			SpeedX = win_width - GetRatioSize().cx - GetX();
		}
		if (falling == false)
		{
			fallingDown();
		}
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
		if (yDir == DIR_UP)
		{
			jumpSpeed = 0; //���������ٶ�
			
		}
		if (yDir == DIR_DOWN)
		{
			SetSequence(FRAME_RUN, 3);
			jumpSpeed = 0; //���������ٶ�
			jumping = false; //��������״̬
		}
	}
}

void Mario::fallingDown()
{
	if (jumping == false)
	{
		jumpSpeed = 0;
		jumping = true;
		falling = true;
	}
}

void Mario::jumpUpDown(T_Map* pBarrier)
{
	// Ϊ�ٶȼ�������Ӱ��
	jumpSpeed = jumpSpeed + gravity;
	if (jumpSpeed < 0)   // ������
	{
		// ����ֻ�������·�������xDir��Ϊһ�������ڵķ�����-1
		updatePostion(-1, DIR_UP, DIR_UP, pBarrier);
	}
	else if (jumpSpeed > 0)  // ������������
	{
		// ����ֻ�������·�������xDir��Ϊһ�������ڵķ�����-1
		updatePostion(-1, DIR_DOWN, DIR_DOWN, pBarrier);
	}

}
void Mario::StatusChange(PLAYERSTATUS status)
{
	if(getStaStus() == PLAYER_SMALL&&(status== PLAYER_BIG|| status==PLAYER_ABILITY))
	{
		

		SetRatio(1.5f);
		SetPosition(GetX(), GetY() - Height*0.5f);
		colideWidth = GetRatioSize().cx;
		colideHeight = GetRatioSize().cy;
	}
	if (getStaStus() == PLAYER_BIG && status == PLAYER_SMALL )
	{
		SetRatio(1.0f);
		SetPosition(GetX(), GetY() + Height*0.5f);
		colideWidth = GetRatioSize().cx;
		colideHeight = GetRatioSize().cy;
	}
	setStaStus(status);
}
void Mario::death()
{
	SetPosition(12, 20);
}
void Mario::damage() 
{
	if (playerstatus == PLAYER_SMALL)
	{
		death();
	}

	else if (playerstatus == PLAYER_BIG)
	{
		StatusChange(PLAYER_SMALL);
	}
}
