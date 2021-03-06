#include "Brick.h"



CBrick::CBrick()
{
	Init();
}

CBrick::CBrick(Vector2 pos, int m_Width, int m_Height)
{
	Init();
	this->m_Width = m_Width;
	this->m_Height = m_Height;
	this->m_Pos = pos;
}


CBrick::~CBrick()
{
}

Box CBrick::GetBox()
{
	if (!simon->isSit)
	{
		return Box(this->m_Pos.x, this->m_Pos.y, this->m_Width - 40, this->m_Height);
	}
	else
	{
		return Box(this->m_Pos.x, this->m_Pos.y, this->m_Width, this->m_Height + 10);
	}
}

void CBrick::Init()
{
	this->m_Id = 702;
	
	m_isLive = true;
}

RECT * CBrick::GetRectRS()
{
	RECT * rec = new RECT();
	rec->left = 0;
	rec->right = rec->left + m_Width;
	rec->top = 0;
	rec->bottom = rec->top + m_Height;
	return rec;
}

void CBrick::Update(float deltaTime)
{
	this->OnSimonCollision(deltaTime);
	OnItemCollision(deltaTime, CItemManage::GetInstance()->m_ListItem);
	OnEnemyCollision(deltaTime, CEnemyManage::GetInstance()->m_ListEnemy);
	//OnGroundMovingCollision(deltaTime, CGroundMovingManage::GetInstance()->m_ListGroundMovingPlatform);
}

void CBrick::OnSimonCollision(float deltaTime)
{
	if (this->simon->simon_Status != SIMON_status::ONSTAIR)
	{
		CDirection normalX;
		CDirection normalY;
		float timeCollision;
		timeCollision = COnCollision::GetInstance()->SweepAABB(this->simon->GetBox(), this->GetBox(), normalX, normalY, deltaTime);
		if (normalY == CDirection::ON_DOWN && this->simon->isOnStair == false && this->simon->isMoveToStair == false && this->simon->isCollisionEnemy == false)
		{
			simon->m_Pos.y = this->m_Pos.y + this->m_Height / 2 + simon->m_Height / 2 - 8;
			this->simon->simon_Status = SIMON_status::IDLE;
			this->simon->isKey_X = false;
			/*this->simon->isMoveJump = false;*/
		}
		if ( (normalX == CDirection::ON_LEFT || normalX == CDirection::ON_RIGHT) && this->simon->isMoveJump == true)
		{
			this->simon->m_vx = 0;
		}
		if (this->simon->isCollisionEnemy == false)
		{
			if (this->simon->isMoveToStair == false && this->simon->isOnStair == false && this->simon->isDownStair == false && this->simon->prepareOnStair == false && this->simon->isJump == false)
			{
				if (this->simon->m_Pos.y > this->m_Pos.y)
				{
					if (COnCollision::GetInstance()->AABBCheck(this->simon->GetBox(), this->GetBox()))
					{

						if (this->simon->isSit == true && (this->simon->m_currentFrame == 4 || this->simon->m_currentFrame == 15 || this->simon->m_currentFrame == 16 || this->simon->m_currentFrame == 17))
						{
							simon->m_Pos.y = this->m_Pos.y + this->m_Height / 2 + simon->m_Height / 2 - 24;
						}
						else
						{
							simon->m_Pos.y = this->m_Pos.y + this->m_Height / 2 + simon->m_Height / 2 - 8;
						}
					}
				}
				
			}
		}

	}
}

void CBrick::OnItemCollision(float deltaTime, std::vector<CItem*> listItem)
{
	if (listItem.size() != 0)
	{
		CDirection normalX;
		CDirection normalY;
		float timeCollision;
		for (std::vector<CItem*>::iterator it = listItem.begin(); it != listItem.end(); ++it)
		{
			CItem* item = *it;
			if (COnCollision::GetInstance()->AABBCheck(item->GetBox(), this->GetBox()) 
				|| ( abs(item->m_Pos.y - this->m_Pos.y) <= 32 && abs(item->m_Pos.x - this->m_Pos.x) <=32) )
			{
				item->m_Pos.y = this->m_Pos.y + this->m_Height/2 + 10;
				item->m_vyDefault = item->m_vy = 0;
			}
		}
	
	}
	
}

void CBrick::OnEnemyCollision(float deltaTime, std::vector<CEnemy*> listEnemy)
{
	CDirection normalX;
	CDirection normalY;
	float timeCollision;
	for (std::vector<CEnemy*>::iterator it = listEnemy.begin(); it != listEnemy.end(); it++)
	{
		CEnemy* enemy = *it;
		timeCollision = COnCollision::GetInstance()->SweepAABB(enemy->GetBox(), this->GetBox(), normalX, normalY, deltaTime);
		if (normalY == ON_DOWN)
		{
			if (enemy->m_Id == 202)
			{
				int a = 5;
			}
		}
	}
}


