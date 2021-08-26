#include "framework.h"
#include "makeWall.h"

makeSoftWall::makeSoftWall()
{
	normal_wall=IMAGE->addFrameImage("일반벽", "images/tile/wall_dirt_crypt2.bmp", 48, 48+25, 1, 1, true);

}

makeSoftWall::~makeSoftWall()
{
}

HRESULT makeSoftWall::init()
{
	return S_OK;
}

void makeSoftWall::release()
{
}

void makeSoftWall::update()
{
}

void makeSoftWall::render()
{
	for(_viWall = _vWall.begin() ; _viWall != _vWall.end(); _viWall++)
	{
		if (_isDebug) {
			ZORDER->ZorderRectangle(_viWall->rc,4);
		}
		ZORDER->ZorderFrameRender(normal_wall, 3, _viWall->rc.bottom, _viWall->x, _viWall->y);
	}
}

void makeSoftWall::addWall(float x, float y)
{
	tagWall newWall;
	newWall.img = IMAGE->findImage("일반벽");
	newWall.x = x ;
	newWall.y = y ;
	newWall.rc = RectMake(x , y, newWall.img->getFrameWidth(), newWall.img->getFrameHeight());
	newWall.hp = 2;
	_vWall.push_back(newWall);
}

void makeSoftWall::updateRect(vector<tagWall>::iterator iter)
{
	iter->rc = RectMake(iter->x, iter->y, iter->img->getFrameWidth(), iter->img->getFrameHeight());
}
