#include "HideObjectManage.h"



CHideObjectManage::CHideObjectManage()
{
}


CHideObjectManage::~CHideObjectManage()
{
}

void CHideObjectManage::Update(float deltaTime)
{
	if (this->m_listHideObject.size() != 0)
	{
		for (std::vector<CHideObject*>::iterator it = this->m_listHideObject.begin();
			it != this->m_listHideObject.end(); ++it)
		{
			CHideObject* obj = *it;
			obj->Update(deltaTime);
		}
	}

}

CHideObject * CHideObjectManage::CreateHideObject(HideObject_TYPE type, Vector2 pos)
{
	CHideObject* obj = NULL;
	switch (type)
	{
	case GroundHorizontal:
		break;
	case GroundVertical:
		obj = new CChangeScreen(HideObject_TYPE::GroundVertical, pos);
		break;
		break;
	case StopScrollScene:
		obj = new CStopScrollCamera(HideObject_TYPE::StopScrollScene, pos);
		break;
	case ChangeScene:
		obj = new CChangeScreen(HideObject_TYPE::ChangeScene, pos);
		break;

	case Free:
		break;
		//cau thang
	case DownStairLeft:
		obj = new CDownStairLeft(pos);
		break;
	case UpStairLeft:
		obj = new CUpStairLeft(pos);
		break;
	case DownStairRight:
		obj = new CDownStairRight(pos);
		break;
	case UpStairRight:
		obj = new CUpStairRight(pos);
		break;

	case ChangeTop:
		break;
	case ChangeDown:
		obj = new CChangeDown(HideObject_TYPE::ChangeDown, pos);
		break;
	case CheckSimonDie:
		obj = new CCheckSimonDie(HideObject_TYPE::CheckSimonDie, pos);
		break;
	default:
		break;
	}
	this->m_listHideObject.push_back(obj);
	return obj;
}
