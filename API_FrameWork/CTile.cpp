#include "framework.h"
#include "CTile.h"

CTile::CTile():
	CObject()
{
	ZORDER->ZorderFrameRender(nullptr, 1, 0, pos.x - size.x / 2, pos.y-size.y / 2, 0, 0);
}

CTile::CTile(POINT _pos, POINT _size, image* _img, animation* _ani)
	:CObject(_pos, _size, _img, _ani)
{
}

CTile::~CTile()
{
}

HRESULT CTile::init()
{
    return S_OK;
}

void CTile::release()
{
}

void CTile::update()
{
}

void CTile::render()
{
}
