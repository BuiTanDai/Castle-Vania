#ifndef __CCAMERA_H__
#define __CCAMERA_H__

#include "Global.h"
#include "Singleton.h"

class CCamera : public CSingleton<CCamera>
{
public:
	CCamera();
	~CCamera();
public:
	void Update(float x, float y); //Update vi tri cua camera
	RECT*& GetBound();
	Vector3 GetPointTransform(float x, float y); // Tra ve vi tri da transform
	Vector3 m_pos;
	Matrix m_matrixTransform;
	bool isStopScrollCamera = false;
public:
	Vector3 GetCameraPos();
	void SetPos(Vector3);
	
};
#endif

