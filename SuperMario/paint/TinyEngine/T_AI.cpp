//*******************************************************************
// TinyEngine����  
// ����: ������(WanLizhong)
// ����: www.wanlizhong.com 
// ����: 2013-08-02
// ����: 2020-12-20
// ��Ȩ���� 2007-2021 ������
// (C) 2007-2021 WanLizhong All Rights Reserved
//*******************************************************************

#include "T_AI.h"

//���ά��GAME_DIR��Ԫ�ر��һ��
//�ڶ�ά��ʾ��Ӧ����Ķ�ܷ���
int T_AI::EvadeDir[8][5]={
	//DIR_LEFT��ܷ���
	{DIR_RIGHT, DIR_DOWN, DIR_UP, DIR_RIGHT_UP, DIR_RIGHT_DOWN},
	//DIR_RIGHT��ܷ���
	{DIR_LEFT, DIR_DOWN, DIR_UP, DIR_LEFT_UP, DIR_LEFT_DOWN},	
	//DIR_UP��ܷ���
	{DIR_DOWN, DIR_LEFT, DIR_RIGHT, DIR_LEFT_DOWN, DIR_RIGHT_DOWN},	
	//DIR_DOWN��ܷ���
	{DIR_UP, DIR_LEFT, DIR_RIGHT, DIR_LEFT_UP, DIR_RIGHT_UP},	
	//DIR_LEFT_UP��ܷ���
	{DIR_RIGHT_DOWN, DIR_RIGHT_UP, DIR_RIGHT, DIR_UP, DIR_DOWN},
	//DIR_LEFT_DOWN��ܷ���
	{DIR_RIGHT_UP, DIR_RIGHT_DOWN, DIR_RIGHT, DIR_UP, DIR_DOWN},
	//DIR_RIGHT_UP��ܷ���
	{DIR_LEFT_DOWN, DIR_LEFT_UP, DIR_LEFT, DIR_UP, DIR_DOWN},
	//DIR_RIGHT_DOWN��ܷ���
	{DIR_LEFT_UP, DIR_LEFT_DOWN, DIR_LEFT, DIR_UP, DIR_DOWN}		
};

T_AI::T_AI(int d_style)
{
	dir_style = d_style;
}

T_AI::~T_AI(void)
{
}

// �������spָ���Ľ�ɫǰ�������Ӧ����ײ�������
// ����sp�������Ľ�ɫ����
// ����spSizeTimes����ɫ��ߵı����������������ķ�Χ
// ����testRec������Ͳ������õ����յļ������
void T_AI::GetHitRect(IN T_Sprite* sp, IN int spSizeTimes, OUT RECT& testRec)
{
	int sp_width = sp->GetRatioSize().cx;
	int sp_height = sp->GetRatioSize().cy;

	switch(sp->GetDir())
	{
	case DIR_LEFT:
		testRec.left = sp->GetX()-spSizeTimes*sp_width;
		testRec.top = sp->GetY();
		testRec.right = sp->GetX();
		testRec.bottom = sp->GetY()+sp_height;;
		break;

	case DIR_RIGHT:
		testRec.left = sp->GetX()+sp_width;
		testRec.top = sp->GetY();
		testRec.right = sp->GetX()+(spSizeTimes+1)*sp_width;
		testRec.bottom = sp->GetY()+sp_height;;
		break;

	case DIR_UP:
		testRec.left = sp->GetX();
		testRec.top = sp->GetY()-spSizeTimes*sp_height;
		testRec.right = sp->GetX()+sp_width;
		testRec.bottom = sp->GetY();
		break;

	case DIR_DOWN:
		testRec.left = sp->GetX();
		testRec.top = sp->GetY()+sp_height;;
		testRec.right = sp->GetX()+sp_width;
		testRec.bottom = sp->GetY()+(spSizeTimes+1)*sp_height;
		break;

	case DIR_LEFT_UP:
		testRec.left = sp->GetX()-spSizeTimes*sp_width;
		testRec.top = sp->GetY()-spSizeTimes*sp_height;
		testRec.right = sp->GetX();
		testRec.bottom = sp->GetY();
		break;

	case DIR_LEFT_DOWN:
		testRec.left = sp->GetX()-spSizeTimes*sp_width;
		testRec.top = sp->GetY()+sp_height;;
		testRec.right = sp->GetX();
		testRec.bottom = sp->GetY()+(spSizeTimes+1)*sp_height;
		break;

	case DIR_RIGHT_UP:
		testRec.left = sp->GetX()+sp_width;
		testRec.top = sp->GetY()-spSizeTimes*sp_height;
		testRec.right = sp->GetX()+(spSizeTimes+1)*sp_width;
		testRec.bottom = sp->GetY();
		break;

	case DIR_RIGHT_DOWN:
		testRec.left = sp->GetX()+sp_width;
		testRec.top = sp->GetY()+sp_height;;
		testRec.right = sp->GetX()+(spSizeTimes+1)*sp_width;
		testRec.bottom = sp->GetY()+(spSizeTimes+1)*sp_height;
		break;
	}
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �õ�һ��T_Sprite������Χ8������ľ�������
// ����sp�������Ľ�ɫ����
// ����spSizeTimes����ɫ��ߵı����������������ķ�Χ
// ����testRec������Ͳ�����ָ��һ��8��Ԫ�ص�RECT���飬�õ����ս�ɫ������Χ8������ľ��μ������
void T_AI::GetHitRects(IN T_Sprite * sp, IN float spSizeTimes, OUT RECT*& testRec)
{
	if (testRec == NULL)
	{
		testRec = new RECT[8];
	}
	int sp_width = sp->GetRatioSize().cx;
	int sp_height = sp->GetRatioSize().cy;

	for (int i = 0; i < 8; i++)
	{
		if (i == DIR_LEFT)
		{
			testRec[i].left = (LONG)(sp->GetX() - spSizeTimes*sp_width);
			testRec[i].top = (LONG)sp->GetY();
			testRec[i].right = (LONG)sp->GetX();
			testRec[i].bottom = (LONG)(sp->GetY() + sp_height);
		}
		if (i == DIR_RIGHT)
		{
			testRec[i].left = (LONG)(sp->GetX() + sp_width);
			testRec[i].top = (LONG)sp->GetY();
			testRec[i].right = (LONG)(sp->GetX() + (spSizeTimes + 1)*sp_width);
			testRec[i].bottom = (LONG)(sp->GetY() + sp_height);
		}
		if (i == DIR_UP)
		{
			testRec[i].left = (LONG)sp->GetX();
			testRec[i].top = (LONG)(sp->GetY() - spSizeTimes*sp_height);
			testRec[i].right = (LONG)(sp->GetX() + sp_width);
			testRec[i].bottom = (LONG)sp->GetY();
		}

		if (i == DIR_DOWN)
		{
			testRec[i].left = (LONG)sp->GetX();
			testRec[i].top = (LONG)(sp->GetY() + sp_height);
			testRec[i].right = (LONG)(sp->GetX() + sp_width);
			testRec[i].bottom = (LONG)(sp->GetY() + (spSizeTimes + 1)*sp_height);
		}
		if (i == DIR_LEFT_UP)
		{
			testRec[i].left = (LONG)(sp->GetX() - spSizeTimes*sp_width);
			testRec[i].top = (LONG)(sp->GetY() - spSizeTimes*sp_height);
			testRec[i].right = (LONG)sp->GetX();
			testRec[i].bottom = (LONG)sp->GetY();
		}
		if (i == DIR_LEFT_DOWN)
		{
			testRec[i].left = (LONG)(sp->GetX() - spSizeTimes*sp_width);
			testRec[i].top = (LONG)(sp->GetY() + sp_height);
			testRec[i].right = (LONG)sp->GetX();
			testRec[i].bottom = (LONG)(sp->GetY() + (spSizeTimes + 1)*sp_height);
		}
		if (i == DIR_RIGHT_UP)
		{
			testRec[i].left = (LONG)(sp->GetX() + sp_width);
			testRec[i].top = (LONG)(sp->GetY() - spSizeTimes*sp_height);
			testRec[i].right = (LONG)(sp->GetX() + (spSizeTimes + 1)*sp_width);
			testRec[i].bottom = (LONG)sp->GetY();
		}
		if (i == DIR_RIGHT_DOWN)
		{
			testRec[i].left = (LONG)(sp->GetX() + sp_width);
			testRec[i].top = (LONG)(sp->GetY() + sp_height);
			testRec[i].right = (LONG)(sp->GetX() + (spSizeTimes + 1)*sp_width);
			testRec[i].bottom = (LONG)(sp->GetY() + (spSizeTimes + 1)*sp_height);
		}
	}
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// �����ƶ������ٶȺ�ָ���Ļ��Χ���㵱ǰ��ɫ���ƶ�λ��
MoveCoord T_AI::GetMoveCoord(T_Sprite* npc_sp, RECT boundary)
{
	MoveCoord mRate;
	int nextStepX, nextStepY;
	int SpeedX=0, SpeedY=0;
	mRate.BoundDir = -1;	//û���ڱ߽���

	int sp_width = npc_sp->GetRatioSize().cx;
	int sp_height = npc_sp->GetRatioSize().cy;

	int speed = npc_sp->GetSpeed();
	int dir = npc_sp->GetDir();
 
	switch(dir)
	{
	case DIR_LEFT:
		SpeedX = -npc_sp->GetSpeed();
		SpeedY = 0;
		//������һ���ƶ��Ƿ񳬹��߽�
		nextStepX = npc_sp->GetX()-speed;
		if(nextStepX <= boundary.left) 
		{
			SpeedX =  -(npc_sp->GetX()-boundary.left);
			mRate.BoundDir = DIR_LEFT;
		}
		break;

	case DIR_RIGHT:
		SpeedX =speed;
		SpeedY = 0;
		//������һ���ƶ��Ƿ񳬹��߽�
		nextStepX = npc_sp->GetX()+ sp_width + speed;
		if(nextStepX >= boundary.right)
		{
			SpeedX = boundary.right - (npc_sp->GetX()+sp_width);
			mRate.BoundDir = DIR_RIGHT;
		}
		break;

	case DIR_UP:
		SpeedX = 0;
		SpeedY = -speed;
		//������һ���ƶ��Ƿ񳬹��߽�
		nextStepY = npc_sp->GetY()-speed;
		if(nextStepY <= boundary.top) 
		{
			SpeedY =-(npc_sp->GetY()-boundary.top);
			mRate.BoundDir = DIR_UP;
		}
		break;

	case DIR_DOWN:
		SpeedX = 0;
		SpeedY = speed;
		//������һ���ƶ��Ƿ񳬹��߽�
		nextStepY = npc_sp->GetY() + sp_height + speed;
		if(nextStepY >= boundary.bottom) 
		{
			SpeedY = boundary.bottom - (npc_sp->GetY()+sp_height);
			mRate.BoundDir = DIR_DOWN;
		}
		break;
	
	case DIR_LEFT_UP:
		SpeedX = -speed;
		SpeedY = -speed;

		//������һ���ƶ��Ƿ񳬹��߽�
		nextStepX = npc_sp->GetX()-speed;
		if(nextStepX <= boundary.left) 
		{
			SpeedX =  -(npc_sp->GetX()-boundary.left);
			SpeedY = -(npc_sp->GetX()-boundary.left);
			mRate.BoundDir = DIR_LEFT;
			break;
		}
		nextStepY = npc_sp->GetY()-speed;
		if(nextStepY <= boundary.top) 
		{
			SpeedY =-(npc_sp->GetY()-boundary.top);
			SpeedX = -(npc_sp->GetY()-boundary.top);
			mRate.BoundDir = DIR_UP;
		}
		break;

	case DIR_LEFT_DOWN:
		SpeedX = -speed;
		SpeedY = speed;

		//������һ���ƶ��Ƿ񳬹��߽�
		nextStepX = npc_sp->GetX()-speed;
		if(nextStepX <=boundary.left) 
		{
			SpeedX =  -(npc_sp->GetX()-boundary.left);
			SpeedY =  (npc_sp->GetX()-boundary.left);
			mRate.BoundDir = DIR_LEFT;
			break;
		}
		nextStepY = npc_sp->GetY() + sp_height + speed;
		if(nextStepY >=boundary.bottom) 
		{
			SpeedY = boundary.bottom - (npc_sp->GetY()+sp_height);
			SpeedX = -(boundary.bottom - (npc_sp->GetY()+sp_height));
			mRate.BoundDir = DIR_DOWN;
		}
		break;

	case DIR_RIGHT_UP:
		SpeedX = speed;
		SpeedY = -speed;

		//������һ���ƶ��Ƿ񳬹��߽�
		nextStepX = npc_sp->GetX()+ sp_width + speed;
		if(nextStepX >= boundary.right) 
		{
			SpeedX = boundary.right - (npc_sp->GetX()+sp_width);
			SpeedY = -(boundary.right - (npc_sp->GetX()+sp_width));
			mRate.BoundDir = DIR_RIGHT;
			break;
		}
		nextStepY = npc_sp->GetY()-speed;
		if(nextStepY <= boundary.top) 
		{
			SpeedY =-( npc_sp->GetY()-boundary.top);
			SpeedX = npc_sp->GetY()-boundary.top;
			mRate.BoundDir = DIR_UP;
		}
		break;

	case DIR_RIGHT_DOWN:
		SpeedX = speed;
		SpeedY = speed;

		//������һ���ƶ��Ƿ񳬹��߽�
		nextStepX = npc_sp->GetX()+ sp_width + speed;
		if(nextStepX >= boundary.right) 
		{
			SpeedX = boundary.right - (npc_sp->GetX()+sp_width);
			SpeedY = boundary.right - (npc_sp->GetX()+sp_width);
			mRate.BoundDir = DIR_RIGHT;
			break;
		}
		nextStepY = npc_sp->GetY() + sp_height + speed;
		if(nextStepY >=boundary.bottom) 
		{
			SpeedY = boundary.bottom - (npc_sp->GetY()+sp_height);
			SpeedX = boundary.bottom - (npc_sp->GetY()+sp_height);
			mRate.BoundDir = DIR_DOWN;
		}
	}

	mRate.moveX = SpeedX;
	mRate.moveY = SpeedY;
	mRate.oldX = npc_sp->GetX();
	mRate.oldY = npc_sp->GetY();
	return mRate;
}

// �����ƶ������ٶȺ�ָ���Ļ��Χ�Խ�ɫ�����δ���
void T_AI::Wander(T_Sprite* npc_sp, RECT boundary)
{
	// ��ȡ��ǰ��Ϸ��ɫ���ƶ�������ٶȼ�������һ�����ƶ���Ϣ
	MoveCoord mRate = GetMoveCoord(npc_sp, boundary);
	// �����ɫû�е�����Χ�ı߽�
	if(mRate.BoundDir == -1 )
	{
		// ��ɫ�����ƶ�
		npc_sp->Move(mRate.moveX, mRate.moveY);
	}
	// �����ɫ������Χ�ı߽�
	if(mRate.BoundDir != -1) 
	{
		int r_dir = 0;
		// ���ݽ�ɫ���ƶ�����ģʽ��ȡһ�������ܷ���
		if(dir_style == 8) 
		{
			r_dir = rand()%5;
		}
		else
		{
			r_dir = rand()%3;
		}
		// ����ɫ��λ�ڱ߽�
		npc_sp->SetPosition(mRate.oldX, mRate.oldY);
		// Ϊ��ɫ�����µ��ƶ�����
		npc_sp->SetDir(EvadeDir[mRate.BoundDir][r_dir]);
	}
}

// �����ƶ������ٶȺ�ָ���ĵ�ͼ����Խ�ɫ�����δ���
void T_AI::Wander(T_Sprite* npc_sp, T_Map* map)
{
	// ������Ϸ��ͼ�ľ��η�Χ
	RECT mapBound;
	mapBound.left = map->GetX();
	mapBound.top = map->GetY();
	mapBound.right = map->GetX()+map->GetWidth();
	mapBound.bottom = map->GetY()+map->GetHeight();

	// ��ȡ��ǰ��Ϸ��ɫ���ƶ�������ٶȼ�������һ�����ƶ���Ϣ
	MoveCoord mRate = GetMoveCoord(npc_sp, mapBound);
	
	// ���ݽ�ɫ���ƶ��ķ���ģʽ��ȡһ�������ܷ���
	int r_dir = 0;
	if(dir_style == 8) 
	{
		r_dir = rand()%5;
	}
	else
	{
		r_dir = rand()%3;
	}
	
	// �����ɫû�е�����Ϸ��ͼ�ı߽�
	if(mRate.BoundDir == -1 )
	{
		npc_sp->Move(mRate.moveX, mRate.moveY);
	}
	// �����ɫ�Ѿ�������Ϸ��ͼ�ı߽�
	if(mRate.BoundDir != -1) 
	{
		npc_sp->SetPosition(mRate.oldX, mRate.oldY);
		npc_sp->SetDir(EvadeDir[mRate.BoundDir][r_dir]);
	}
	if(npc_sp->CollideWith(map)) 
	{
		// ����ɫ��λ�ڱ߽�
		npc_sp->SetPosition(mRate.oldX, mRate.oldY);
		// Ϊ��ɫ�����µ��ƶ����򣨳�����3�������ܣ�
		npc_sp->SetDir(EvadeDir[npc_sp->GetDir()][rand()%3]);
	}
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ��ɫ��ܴ�����һ������Ϊ��ܵĶ��󣬵ڶ�������ΪҪ�رܵļ����󣬵���������Ϊ�߽緶Χ
void T_AI::Escape(T_Sprite * npc_sp, T_Sprite * player, RECT boundary)
{
	
	RECT playerRect = { player->GetX(), player->GetY(),
		player->GetX() + player->GetRatioSize().cx,
		player->GetY() + player->GetRatioSize().cy };

	RECT* testRect = NULL;
	GetHitRects(npc_sp, 1.0, testRect);

	bool testPlayerHitting = false;

	for (int i = 0; i < 8; i++)
	{
		RECT lprcDst;
		if ((IntersectRect(&lprcDst, &playerRect, &testRect[i])) == TRUE)
		{
			testPlayerHitting = true;
			int r_dir = 0;
			switch (i)
			{
			case DIR_LEFT:
				r_dir = DIR_RIGHT;
				break;
			case DIR_RIGHT:
				r_dir = DIR_LEFT;
				break;
			case DIR_UP:
				r_dir = DIR_DOWN;
				break;
			case DIR_DOWN:
				r_dir = DIR_UP;
				break;
			case DIR_LEFT_UP:
				r_dir = DIR_RIGHT_DOWN;
				break;
			case DIR_LEFT_DOWN:
				r_dir = DIR_RIGHT_UP;
				break;
			case DIR_RIGHT_UP:
				r_dir = DIR_LEFT_DOWN;
				break;
			case DIR_RIGHT_DOWN:
				r_dir = DIR_LEFT_UP;
				break;
			}
			npc_sp->SetDir(r_dir);
			break;
		}
	}
	MoveCoord mRate = GetMoveCoord(npc_sp, boundary);

	// �����⵽����ҷ�������ײ���ڱ߽�λ��
	if (testPlayerHitting == true && mRate.BoundDir != -1)
	{
		// ����ɫ��λ�ڱ߽�
		npc_sp->SetPosition(mRate.oldX, mRate.oldY);

		//�����ϱ߽�����±߽�
		if (mRate.BoundDir == DIR_UP || mRate.BoundDir == DIR_DOWN)
		{
			if (player->GetX() > npc_sp->GetX())
			{
				npc_sp->SetDir(DIR_LEFT);
			}
			else
			{
				npc_sp->SetDir(DIR_RIGHT);
			}
		}
	}
}

// ��ɫ��ܴ�����һ������Ϊ��ܵĶ��󣬵ڶ�������ΪҪ�رܵļ�����
void T_AI::Evade(T_Sprite* npc_sp, T_Sprite* player)
{
	RECT lprcDst;
	RECT playerRect={player->GetX(), player->GetY(), 
					 player->GetX()+player->GetRatioSize().cx, 
					 player->GetY()+player->GetRatioSize().cy };

	RECT testRect;
	GetHitRect(npc_sp, 1, testRect);

	if ((IntersectRect(&lprcDst, &playerRect, &testRect))==TRUE)
	{

		int r_dir = 0;
		if(dir_style == 8) 
		{
			r_dir = rand()%5;
		}
		else
		{
			r_dir = rand()%3;
		}
		npc_sp->SetDir(EvadeDir[npc_sp->GetDir()][r_dir]);
	}
}

// ��ɫ���ص�������һ������Ϊ�����󣬵ڶ�������Ϊ���������ڵĽ�ɫ����
void T_AI::CheckOverlay(T_Sprite* npc_sp, vector<T_Sprite*> vSpriteSet)
{
	vector<T_Sprite*>::iterator p;

	RECT testRec;
	GetHitRect(npc_sp, 1, testRec);// ��ȡ��ǰSprite��Χ�ľ���

	int r_dir = 0;
	if(dir_style == 8) 
	{
		r_dir = rand()%5;
	}
	else
	{
		r_dir = rand()%3;
	}

	RECT lprcDst;
	for (p = vSpriteSet.begin(); p != vSpriteSet.end(); p++) 
	{
		if(*p == npc_sp) continue;
		
		RECT pRect={(*p)->GetX(), (*p)->GetY(), 
					(*p)->GetX()+(*p)->GetRatioSize().cx, 
					(*p)->GetY()+(*p)->GetRatioSize().cy };

		if ((IntersectRect(&lprcDst, &pRect, &testRec))==TRUE)
		{
			npc_sp->SetDir(EvadeDir[npc_sp->GetDir()][r_dir]);
		}
	}
}