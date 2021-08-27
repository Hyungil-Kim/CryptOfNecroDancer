#pragma once
#include "CObject.h"
class CObstacle : public CObject
{
private:
	OBJECT objType;


public:
	CObstacle();
	CObstacle(POINT _pos,RECT _rc, OBJECT _type);
	CObstacle(CObstacle* copy);
	~CObstacle();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	OBJECT getObjType() { return objType; }
	void setObjType(OBJECT obj) { objType = obj; }
};

