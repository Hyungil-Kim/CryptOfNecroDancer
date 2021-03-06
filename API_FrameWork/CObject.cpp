#include "framework.h"
#include "CObject.h"

CObject::CObject():
	pos({ WINSIZEX / 2,WINSIZEY / 2 }),
	size({ 10,10 }),
	img(nullptr),
	ani(nullptr)
{
}


CObject::CObject(POINT _pos, RECT _rc):
	pos(_pos),rc(_rc)
{
}

CObject::CObject(POINT _pos, POINT _size, image* _img, animation* _ani):
	pos(_pos),size(_size),img(_img),ani(_ani)
{
}

CObject::~CObject()
{
	SAFE_DELETE(img);
	SAFE_DELETE(ani);
}

HRESULT CObject::init()
{
	return S_OK;
}

void CObject::release()
{
}

void CObject::update()
{
}

void CObject::render()
{
}
