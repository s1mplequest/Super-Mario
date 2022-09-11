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
	if (jumpDir == DIR_DOWN || jumpDir == DIR_UP)// 上跳、下跳
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
		//计算下一步移动是否超过边界
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
		//计算下一步移动是否超过边界
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
		//计算下一步移动是否超过边界
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
		//计算下一步移动是否超过边界
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

	int x = GetX();// 获得移动前的x位置
	int y = GetY();// 获得移动前的y位置

	if (!CollideWith(pBarrier))
	{
		Move(SpeedX, SpeedY);	// 继续移动
	}
	if (CollideWith(pBarrier))
	{
		SetPosition(x, y);		// 还原移动前的位置
		if (yDir == DIR_UP)
		{
			jumpSpeed = 0; //设置跳的速度
			
		}
		if (yDir == DIR_DOWN)
		{
			SetSequence(FRAME_RUN, 3);
			jumpSpeed = 0; //设置跳的速度
			jumping = false; //设置跳的状态
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
	// 为速度加上重力影响
	jumpSpeed = jumpSpeed + gravity;
	if (jumpSpeed < 0)   // 往上跳
	{
		// 由于只处理上下方向，所以xDir设为一个不存在的方向，如-1
		updatePostion(-1, DIR_UP, DIR_UP, pBarrier);
	}
	else if (jumpSpeed > 0)  // 往下自由落体
	{
		// 由于只处理上下方向，所以xDir设为一个不存在的方向，如-1
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
