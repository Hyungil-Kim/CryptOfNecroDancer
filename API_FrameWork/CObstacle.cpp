#include "framework.h"
#include "CObstacle.h"

CObstacle::CObstacle():
	CObject(), objType(OBJECT::EMPTY)
{
}

CObstacle::CObstacle(POINT _pos, RECT _rc, OBJECT _type):
	CObject(_pos, _rc), objType(_type)
{
}

CObstacle::CObstacle(CObstacle* copy)
{
}

CObstacle::~CObstacle()
{
}

HRESULT CObstacle::init()
{
	return S_OK;
}

void CObstacle::release()
{
}

void CObstacle::update()
{
}

void CObstacle::render()
{
}
