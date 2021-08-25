#include "framework.h"
#include "CMap.h"

CMap::CMap()
{
	IMAGE->addFrameImage("1ÃþÅ¸ÀÏ", "images/tile/floor_zone1", 78, 52, 3, 2, true);
	for (int horizontal = 0; horizontal < TILE_NUM_Y; horizontal++)
	{
		for (int vertical = 0; vertical < TILE_NUM_X; vertical++)
			tile[horizontal * TILE_NUM_X + vertical] = new CTile;
	}
}

CMap::CMap(POINT startPos, POINT size)
{
	POINT tempPos = startPos;
	for (int horizontal = 0; horizontal < TILE_NUM_Y; horizontal++)
	{
		for (int vertical = 0; vertical < TILE_NUM_X; vertical++)
		{
			tile[horizontal * TILE_NUM_X + vertical] = new CTile(startPos, size, IMAGE->findImage("1ÃþÅ¸ÀÏ"));
			startPos.x += size.x;
			
		}
		startPos = { tempPos.x,startPos.y + size.y };
	}
}

CMap::~CMap()
{
}

HRESULT CMap::init()
{
	return S_OK;
}

void CMap::release()
{
}

void CMap::update()
{

}

void CMap::render()
{
	this->getDolBUffer()->render(getMemDC(), 0, 0);
	TCHAR str[128];
	for (int idx = 0; idx < TILE_NUM_X * TILE_NUM_Y; idx++)
	{
		Rectangle(getMemDC(),
			tile[idx]->getPos().x - tile[idx]->getSize().x / 2,
			tile[idx]->getPos().y - tile[idx]->getSize().y / 2,
			tile[idx]->getPos().x + tile[idx]->getSize().x / 2,
			tile[idx]->getPos().y + tile[idx]->getSize().y / 2);
		


		wsprintf(str, "%d", idx);
		TextOut(getMemDC(), tile[idx]->getPos().x, tile[idx]->getPos().y, str, strlen(str));
	}
}
