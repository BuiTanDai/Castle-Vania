#ifndef __CCANE_H__
#define __CCANE_H__

#include "Animation.h"
#include "BaseGameObject.h"
//#include "LoadObject.h"
enum caneState {
	default = 1,
	state2 = 2,
	state3 = 3
};
class CCane : public CBaseGameObject, public CAnimation
{

public:
	CCane();
	CCane(Vector2 pos);
	~CCane();
public:
	void Init();
	caneState m_State;
	void Update(Vector2 simonPos, Direction simonDir, float deltaTime);//ham Update chinh cua game
	Vector2 GetPos();
	void OnCollision(float deltaTime, std::vector<CBaseGameObject*> listObject);
	Box GetBox();
	RECT* GetBound();
	RECT* GetRectRS();
	bool Use();
	float m_timeCollisionEnemy = 0.0f;
	//cac ham ke thua tu Animation
public:
	void SetFrame();		// ham chuyen frame.
	int getCurrentFrame() { return m_currentFrame; }
	void updateState(caneState state);
public:
	bool m_checkActive = false; //xet xem co' danh' roi hay ko
	bool m_checkDone = false; //Xet xem danh xong chua
	bool isChangeSimonStatus = false;
};

#endif // !__CCANE_H__