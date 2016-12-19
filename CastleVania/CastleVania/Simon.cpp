﻿#include "Simon.h"
#define MAX_HIGH 400

CSimon::CSimon()
{
	this->m_Id = 1;
	m_hpSimon = 16;
	this->isInput = false;
	this->m_Dir = Direction::RIGHT;
	this->simon_Status = IDLE;
	this->InitMove();
	this->InitAnimation();
	this->cane = new CCane();
	//this->cane->m_Pos = 
	this->hv = new CHinhChuNhat();
	this->m_currentWeapon = WEAPON_name::Dagger;
	//init stair status
	this->canUpStairLeft = this->canUpStairRight = this->canDownStairLeft = this->canDownStairRight = false;
	this->isArrowKeyDown = this->isArrowKeyUp = false;
	this->isCancelStairMove = true;
	this->isMoveLeft = false;
}
#pragma region Init
void CSimon::InitAnimation()
{
	this->m_startFrame = 0;
	this->m_endFrame = 0;
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.15f;
	this->m_increase = 1;
	this->m_totalFrame = 24;
	this->m_column = 8;
}
void CSimon::InitMove()
{

	this->m_vx = 10;
	this->m_vy = 380;
	this->m_vxDefault = 180;
	this->m_vyDefault = 380;

	this->m_a = -900;
	this->m_aDefault = this->m_a;
	this->m_ax = 0;
	this->m_Pos = this->m_PosDefault = Vector2(1888, 220);
	this->m_Width = 60;
	this->m_Height = 68;
	this->m_isJumping = false;
}

#pragma endregion

CSimon::~CSimon()
{
	delete this;
}

void CSimon::Update(float deltaTime)
{
	//SetFrame();

	ChangeFrame(deltaTime);
	//this->m_Pos.x += m_vx * deltaTime;
	MoveUpdate(deltaTime);
	//OnCollision(deltaTime, CLoadObject::GetInstance()->listBox);
	//UpdateGround(deltaTime, CLoadObject::GetInstance()->m_listGameObject);
	//OnCollision(deltaTime, CLoadObject::GetInstance()->m_listGameObject);
	//OnCollision(deltaTime, hv);
	this->cane->Update(deltaTime);
}


void CSimon::Gravity(float deltaTime)
{

}

bool CSimon::MoveTo(Vector2 point, float deltaTime)
{
	if (!this->isLeft && !this->isRight)
	{

		if (this->m_Pos.x > point.x) //kiem tra xem co phai qua ben trai
		{
			this->isLeft = true;
		}
		else
		{
			if (this->m_Pos.x < point.x)
			{
				this->isRight = true;
			}
			else
			{
				this->isLeft = (this->m_Dir == LEFT) ? true : false;
				this->isRight = (this->m_Dir == RIGHT) ? true : false;
			}

		}
	}

	if (this->isLeft) // neu isleft thi van toc x am
	{
		this->m_vx = (this->m_vx>0) ? -this->m_vx : this->m_vx;
		this->m_Dir = Direction::LEFT;
	}
	else
	{
		this->m_vx = (this->m_vx<0) ? -this->m_vx : this->m_vx;
		this->m_Dir = Direction::RIGHT;
	}

	//kiem tra xem co toi toa do X cua point chua
	if ((this->isLeft && this->m_Pos.x <= point.x) || (this->isRight && this->m_Pos.x >= point.x))
	{
		this->check_arrive_x = true;
		this->m_Pos.x = point.x;
	}
	if (!this->check_arrive_x)
	{
		this->m_Pos.x += this->m_vx * deltaTime; // thay doi pos.x cua Boss
	}



	if (!this->isDown && !this->isUp)
	{
		if (this->m_Pos.y > point.y) // kiem tra xem co phai di xuong duoi
		{
			this->isDown = true;
		}
		else
		{
			this->isUp = true;
		}
	}
	if (this->isDown) // neu isdown thi van toc y am
	{
		this->m_vy = (this->m_vy > 0) ? -this->m_vy : this->m_vy;
	}
	else // neu isUp thi van toc y duong
	{
		this->m_vy = (this->m_vy < 0) ? -this->m_vy : this->m_vy;
	}

	//neu da toi point.y
	if ((this->isDown && this->m_Pos.y <= point.y) || (this->isUp && this->m_Pos.y >= point.y))
	{
		this->check_arrive_y = true;
		this->m_Pos.y = point.y;
	}
	if (!this->check_arrive_y)
	{
		this->m_Pos.y += this->m_vy * deltaTime;// Neu chua toi thi Thay doi pos.y
	}
	//Neu da toi point thi tra ve true
	if (this->check_arrive_x && this->check_arrive_y)
	{
		this->check_arrive_x = this->check_arrive_y = false;
		this->isLeft = this->isRight = this->isUp = this->isDown = false;
		return true;
	}
	else
	{
		return false;
	}
}

void CSimon::Jump(float deltaTime)
{
	/*this->m_currentFrame = 0;
	isAttacking = false;
	this->m_Height = 68;
	this->m_Pos.y = 60;
	m_startFrame = 0;
	m_endFrame = 0;*/

}

void CSimon::UpdateStatus(float deltaTime, SIMON_status simon_status)
{
	if (this->cane->isChangeSimonStatus == true)
	{
		if (!isSit)
		{
			this->m_currentFrame = 0;
			isAttacking = false;
			this->m_Height = 68;
			//this->m_Pos.y = 94;
			m_startFrame = 0;
			m_endFrame = 0;
		}
		else
		{
			this->m_currentFrame = 4;
			m_startFrame = 4;
			m_endFrame = 4;
			this->m_Height = 50;
			//this->m_Pos.y = 85;
			isAttacking = false;
		}
		this->cane->isChangeSimonStatus = false;
	}
	switch (simon_status)
	{
	case NONE:
		break;
	case IDLE:
		isAttacking = false;
		this->m_Height = 68;
		this->m_vy = 0;
		m_startFrame = 0;
		m_endFrame = 0;
		isMove = true;
 		canJump = true;
		isJumping = false;
		isSit = false;
		canSit = true;
		
		break;
	case MOVE:

		if (this->simon_Status != SIMON_status::ONSTAIR)
		{
			
			if (isMove)
			{
				if (!isJumping)
				{
					this->m_startFrame = 0;
					this->m_endFrame = 3;
					
				}
				
				if (this->m_Dir == Direction::LEFT)
				{
					m_Pos.x -= this->m_vxDefault * deltaTime;
				}
				if (this->m_Dir == Direction::RIGHT)
				{

					m_Pos.x += this->m_vxDefault * deltaTime;
				}
				
			}
		}
		break;

		break;
	case ONSTAIR:
		this->canSit = false;
		this->m_vx = this->m_vy= 4;
		
		this->m_elapseTimeChangeFrame = 0.15f * 1.2f;
		//Xet Frame 
		if (this->isCancelStairMove == false)
		{
			if (this->isDownStair == true)
			{
				this->m_startFrame = 10;
				this->m_endFrame = 11;
				break;
			}
			if (this->isUpStair == true)
			{
				this->m_startFrame = 12;
				this->m_endFrame = 13;
				break;
			}
		}
		else
		{
			if (this->isDownStair == true)
			{
				this->m_startFrame = 10;
				this->m_endFrame = 10;
				break;
			}
			if (this->isUpStair == true)
			{
				this->m_startFrame = 12;
				this->m_endFrame = 12;
				break;
			}
		}


		break;
	case JUMP:
		isJumping = true;
		canJump = false;
		this->m_vy += this->m_a * deltaTime;
		this->m_Pos.y += this->m_vy * deltaTime;
		/*if (isMoveLeft)
		{
			this->m_Pos.x -= this->m_vxDefault * deltaTime;
		}
		else
		{
			this->m_Pos.x += this->m_vxDefault * deltaTime;
		}*/
		if (this->m_vy <= 0)
		{
			isFree = true;
			simon_Status = SIMON_status::FALL;
			this->canJump = false;

		}
		this->m_startFrame = 4;
		this->m_endFrame = 4;

		break;
	case SIT:
		if (canSit)
		{
			isSit = true;
			isMove = false;
			if (!isAttacking)
			{
				this->m_startFrame = 4;
				this->m_endFrame = 4;
				this->m_Height = 50;
				//this->m_Pos.y = 85;
			}

		}

		break;
	case FALL:
		if (isFree)
		{
			this->m_vy += this->m_a * deltaTime * 2;
			this->m_Pos.y += this->m_vy * deltaTime;
		}
		/*if (isMoveLeft)
		{
			this->m_Pos.x -= this->m_vxDefault * deltaTime;
		}
		else
		{
			this->m_Pos.x += this->m_vxDefault * deltaTime;
		}*/
		this->m_startFrame = 0;
		this->m_endFrame = 0;
		break;
	case ACTACK:
		if (isAttacking)
		{

			if (isSit)
			{
				this->m_startFrame = 15;
				this->m_endFrame = 17;
				this->cane->m_Pos.y = m_Pos.y + 9;
				this->m_Height = 66;
				//this->m_Pos.y = 50;
				this->cane->m_checkActive = true;
			}
			else
			{
				
					this->m_startFrame = 5;
					this->m_endFrame = 7;
				
				
				this->cane->m_checkActive = true;
			}

			this->cane->Use(this->m_Pos, isLeft);
			if (isJumping)
			{
				if (this->cane->m_currentFrame == 2)
				{
					isFree = true;
					simon_Status = FALL;
				}
			}
		}
		break;
	case COLLISION_ENEMY:
		this->m_startFrame = 8;
		this->m_endFrame = 8;
		if (this->timeCollisionEnemy<0.6)
		{
			this->m_Pos.x -= deltaTime * 100;
			this->m_Pos.y += deltaTime * 100;
		}
		else
		{
			this->m_Pos.y -= deltaTime * 100;
		}

		break;

	default:
		break;
	}
	/*if (isChangeStatus)
	{


	}*/
}

void CSimon::MoveUpdate(float deltaTime)
{
	Gravity(deltaTime);
	OnKeyDown(deltaTime);
	OnKeyUp(deltaTime);
	UpdateStatus(deltaTime, simon_Status);

	//lay vi tri cua cay roi theo vi tri cua simon


	//update camera
	CCamera::GetInstance()->Update(this->m_Pos.x, this->m_Pos.y);
}

//thay doi Frame
void CSimon::SetFrame()
{
	this->m_startFrame = 0;
	this->m_endFrame = 0;
}


#pragma region GetBox

Vector2 CSimon::GetPos()
{
	return this->m_Pos;
}

void CSimon::OnCollision(float deltaTime, std::hash_map<int, Box> listBox)
{
	CDirection normalX;
	CDirection normalY;
	float moveX = 0.0f;
	float moveY = 0.0f;
	float timeCollision;
	std::hash_map<int, Box>::iterator it;
	for (it = listBox.begin(); it != listBox.end(); it++)
	{

		timeCollision = COnCollision::GetInstance()->SweepAABB(this->GetBox(), it->second, normalX, normalY, deltaTime);
		if (normalY == CDirection::ON_DOWN)
		{

			isFree = false;
			canJump = true;
		}
	}
}

void CSimon::UpdateGround(float deltaTime, std::vector<CBaseGameObject*> listObject)
{
	float normalX = 0;
	float normalY = 0;
	float moveX = 0.0f;
	float moveY = 0.0f;
	float timeCollision;

	for (std::vector<CBaseGameObject*>::iterator it = listObject.begin();
		it != listObject.end();
		++it)
	{
		CBaseGameObject* obj = *it;
		obj->Update(deltaTime);
		/*timeCollision = CCollision::GetInstance()->Collision(this, *it , normalX, normalY, deltaTime);

		if ((timeCollision > 0.0f && timeCollision < 1.0f) || timeCollision == 2)
		{

		if (normalX = 1)
		{

		this->m_vy = 0;
		this->m_vx = 0;
		}
		}*/
	}

}

void CSimon::OnCollision(float deltaTime, CBaseGameObject * hv)
{
	CDirection normalX;
	CDirection normalY;
	float timeCollision;
	timeCollision = COnCollision::GetInstance()->SweepAABB(this, hv, normalX, normalX, deltaTime);
	if (normalX == CDirection::ON_LEFT || normalX == CDirection::ON_RIGHT)
	{
		this->m_vx = 0;
	}
}

void CSimon::OnCollision(float deltaTime, std::vector<CBaseGameObject*> listObject)
{
	for (std::vector<CBaseGameObject*>::iterator it = listObject.begin();
		it != listObject.end();
		++it)
	{
		CBaseGameObject* obj = *it;
		if (obj->m_Id == 601)
		{
			CDirection normalX;
			CDirection normalY;
			float timeCollision;
			timeCollision = COnCollision::GetInstance()->SweepAABB(this, obj, normalX, normalX, deltaTime);
			if (normalX == CDirection::ON_LEFT || normalX == CDirection::ON_RIGHT)
			{
				//MessageBox(NULL, "dung ground", "BG", MB_OK);
			}
		}
	}
}


Box CSimon::GetBox()
{
	return Box(this->m_Pos.x, this->m_Pos.y, this->m_Width - 10, this->m_Height - 8, this->m_vx, this->m_vy);
}
RECT* CSimon::GetBound()
{
	return nullptr;
}
RECT* CSimon::GetRectRS()
{
	return this->UpdateRectResource(m_Height, m_Width);
}
#pragma endregion

#pragma region Input

void CSimon::OnKeyDown(float deltaTime)
{
	this->m_keyDown = CInput::GetInstance()->GetKeyDown();
	switch (this->m_keyDown)
	{
	case DIK_SPACE:
		if (canJump)
		{
			this->simon_Status = SIMON_status::JUMP;
			this->m_vy = m_vyDefault;
		}
		// start jump if is not "on-air"
		break;
	case DIK_LEFT:
		isMoveLeft = true;
		isLeft = true;
		this->cane->isLeft = true;
		this->m_Dir = Direction::LEFT;
		this->cane->m_Dir = Direction::LEFT;
		if (!isJumping)
		{
			this->simon_Status = SIMON_status::MOVE;
		}
		break;
	case DIK_RIGHT:
		isMoveLeft = false;
		isLeft = false;
		this->cane->isLeft = false;
		this->m_Dir = Direction::RIGHT;
		this->cane->m_Dir = Direction::RIGHT;
		this->simon_Status = SIMON_status::MOVE;
		break;
	case DIK_UP:
		if (this->isCancelStairMove == true)
		{
			this->isArrowKeyUp = true;
		}

		break;
	case DIK_DOWN:
		if (this->isCancelStairMove == true)
		{
			this->isArrowKeyDown = true;
		}
		this->simon_Status = SIMON_status::SIT;
		break;
	case DIK_Z:
		/*if (isSit)
		{
		this->m_startFrame = 14;
		this->m_endFrame = 16;
		this->m_Height = 50;
		this->m_Pos.y = 51;
		this->cane->m_Pos.y = 40;
		}
		else*/

		isAttacking = true;
		this->simon_Status = SIMON_status::ACTACK;


		break;
	case DIK_Q:
		this->cane->updateState(state2);
		break;
	case DIK_C: //test change status
		isCheckChangeState = true;
		break;
	case DIK_E:
		this->isWeaponAttacking = true;
		break;
	default:
		break;
	}
}
void CSimon::OnKeyUp(float deltaTime)
{
	this->m_keyUp = CInput::GetInstance()->GetKeyUp();
	switch (this->m_keyUp)
	{
	case DIK_SPACE:


		break;

	case DIK_LEFT:
		simon_Status = SIMON_status::IDLE;
		
		this->m_ax = 0;
		break;
	case DIK_RIGHT:
		simon_Status = SIMON_status::IDLE;

		this->m_ax = 0;
		break;
	case DIK_UP:
		this->isArrowKeyUp = false;
		break;
	case DIK_DOWN:
		this->isArrowKeyDown = false;
		if (isSit)
		{
			simon_Status = SIMON_status::IDLE;
		}
		/*if (isSit)
		{
			m_Pos.y = 90;
		}*/
		break;
	case DIK_Z:




		break;
	default:
		break;
	}
}
void CSimon::ProcessInput(float deltaTime)
{
	int key = CInput::GetInstance()->GetKeyDown();
	int key_up = CInput::GetInstance()->GetKeyUp();
	//de phim
	if (CInput::GetInstance()->IsKeyDown(DIK_RIGHT))
	{
		if (this->simon_Status == SIMON_status::MOVE || this->simon_Status == SIMON_status::IDLE)
		{
			this->simon_Status = SIMON_status::MOVE;
		}
	}
	if (CInput::GetInstance()->IsKeyDown(DIK_LEFT))
	{
		if (this->simon_Status == SIMON_status::MOVE || this->simon_Status == SIMON_status::IDLE)
		{
			this->simon_Status = SIMON_status::MOVE;
		}
	}
	if (key == DIK_SPACE)
	{
		if (this->canJump)
		{
			if (CInput::GetInstance()->IsKeyDown(DIK_RIGHT))
			{
				this->m_vx = this->m_vxDefault;
			}

			if (CInput::GetInstance()->IsKeyDown(DIK_LEFT))
			{
				this->m_vx = -this->m_vxDefault;
			}

			this->simon_Status = SIMON_status::JUMP;
			this->m_vy = this->m_vyDefault;
		}
	}
}
#pragma endregion



