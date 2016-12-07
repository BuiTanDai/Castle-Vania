#include "Weapon.h"



CWeapon::CWeapon()
{
	this->m_WeaponName = WEAPON_name::None;
	this->Init();
}
CWeapon::CWeapon(WEAPON_name weaponName,Vector2 pos)
{
	this->m_WeaponName = weaponName;
	this->m_PosDefault = this->m_Pos = pos;
	this->Init();
}
void CWeapon::InitAnimate(int totalFrame, int column, int startFrame, int endFrame)
{
	this->m_totalFrame = totalFrame;
	this->m_column = column;
	this->m_startFrame = startFrame;
	this->m_endFrame = endFrame;
	this->m_increase = 1;
	this->m_currentTime = 0;
	this->m_currentFrame = 0;
	this->m_elapseTimeChangeFrame = 0.15f;
}
void CWeapon::Init() {
	this->m_time_life = 0.0f;
	this->m_isRemove = false;
	this->m_Id = static_cast<int>(this->m_WeaponName);
	switch (this->m_WeaponName)
	{

	case WEAPON_name::Axe:
		this->m_Width = 30;
		this->m_Height = 28;
		this->InitAnimate(4, 4, 0, 3);
		break;
	case WEAPON_name::Boomerang:
		this->m_Width = 26;
		this->m_Height = 28;
		//Init Animation
		this->InitAnimate(3, 3, 0, 2);
		break;
	case WEAPON_name::Dagger:
		this->m_Width = 32;
		this->m_Height = 18;
		this->InitAnimate(1, 1, 0, 0);
		break;
	case WEAPON_name::FireBomb2:
		this->m_Width = 32;
		this->m_Height = 26;
		this->InitAnimate(1, 1, 0, 0);
		break;
	default:
		break;
	}
	
	
}
void CWeapon::Update(float deltaTime)
{
	this->MoveUpdate(deltaTime);
	this->ChangeFrame(deltaTime);
	this->m_time_life += deltaTime;
	if (this->m_time_life>=2.0)
	{
		this->m_isRemove = true;
	}
	
}
void CWeapon::MoveUpdate(float deltaTime) 
{
	switch (this->m_WeaponName)
	{
	case WEAPON_name::Dagger:
		this->m_vxDefault = this->m_vx = 200;
		this->m_Pos.x += this->m_vx * deltaTime;
	default:
		this->m_vxDefault = this->m_vx = 200;
		this->m_Pos.x += this->m_vx * deltaTime;
		break;
	}
}

Box CWeapon::GetBox()
{
	return Box(this->m_Pos.x, this->m_Pos.y, this->m_Width - 2, this->m_Height - 2);
}

RECT * CWeapon::GetRectRS()
{
	/*RECT * rec = new RECT();
	rec->left = 0;
	rec->right = rec->left + m_Width;
	rec->top = 0;
	rec->bottom = rec->top + m_Height;
	return rec;*/
	return this->UpdateRectResource(m_Height, m_Width);
}


CWeapon::~CWeapon()
{
}