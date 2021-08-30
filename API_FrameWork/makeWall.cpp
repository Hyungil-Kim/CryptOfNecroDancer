#include "framework.h"
#include "makeWall.h"

makeSoftWall::makeSoftWall()
{
	normal_wall=IMAGE->addFrameImage("일반벽", "images/tile/wall_dirt_crypt2.bmp", 48, 48+30, 1, 1, true);

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
		ZORDER->ZorderFrameRender(normal_wall, 3, _viWall->rc.bottom, _viWall->x, _viWall->y);
	}
}

void makeSoftWall::addWall(float x, float y)
{
	tagWall newWall;
	newWall.img = IMAGE->findImage("일반벽");
	newWall.x = x ;
	newWall.y = y ;
	newWall._wallType = WALL_TYPE::SOFT_WALL;
	newWall.rc = RectMake(x , y, newWall.img->getFrameWidth(), newWall.img->getFrameHeight());
	
	newWall.hard = 2;
	_vWall.push_back(newWall);
}

void makeSoftWall::eraseWall(int x, int y)
{
	for (_viWall = _vWall.begin(); _viWall != _vWall.end(); _viWall++)
	{
		if (x == _viWall->x/48 && y == _viWall->y/48)
		{
			_vWall.erase(_viWall);
			break;
		}
	}
}

void makeSoftWall::updateRect(vector<tagWall>::iterator iter)
{
	iter->rc = RectMake(iter->x, iter->y, iter->img->getFrameWidth(), iter->img->getFrameHeight());
}

makeHardWall::makeHardWall()
{
	hard_wall = IMAGE->addFrameImage("단단한벽", "images/tile/wall_catacomb_crypt1.bmp", 48, 48 + 30, 1, 1, true);
}

makeHardWall::~makeHardWall()
{
}

HRESULT makeHardWall::init()
{
	return S_OK;
}

void makeHardWall::release()
{
}

void makeHardWall::update()
{
}

void makeHardWall::render()
{
	for (_viWall = _vWall.begin(); _viWall != _vWall.end(); _viWall++)
	{
		if (_isDebug) {
			ZORDER->ZorderRectangle(_viWall->rc, 4);
		}
		ZORDER->ZorderFrameRender(hard_wall, 3, _viWall->rc.bottom, _viWall->x, _viWall->y);
	}
}

void makeHardWall::eraseWall(int x, int y)
{
	for (_viWall = _vWall.begin(); _viWall != _vWall.end(); _viWall++)
	{
		if (x == _viWall->x && y == _viWall->y)
		{
			_vWall.erase(_viWall);
		}
	}
}

void makeHardWall::addWall(float x, float y)
{
	tagWall newWall;
	newWall.img = IMAGE->findImage("단단한벽");
	newWall.x = x;
	newWall.y = y;
	newWall._wallType = WALL_TYPE::HARD_WALL;
	newWall.rc = RectMake(x, y, newWall.img->getFrameWidth(), newWall.img->getFrameHeight());
	newWall.hard = 3;
	_vWall.push_back(newWall);
}

void makeHardWall::updateRect(vector<tagWall>::iterator iter)
{
}
