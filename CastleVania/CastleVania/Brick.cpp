#include "Brick.h"



CBrick::CBrick()
{
	Init();
}

CBrick::CBrick(Vector2 pos)
{
	Init();
	this->m_Pos = pos;
}


CBrick::~CBrick()
{
}

Box CBrick::GetBox()
{
	return Box(this->m_Pos.x, this->m_Pos.y, this->m_Width, this->m_Height);
}

void CBrick::Init()
{
	this->m_Id = 702;
	this->m_Width = 32;
	this->m_Height = 32;
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
}