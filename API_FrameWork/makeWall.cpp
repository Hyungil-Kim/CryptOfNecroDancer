#include "framework.h"
#include "makeWall.h"

makeSoftWall::makeSoftWall()
{
	normal_wall=IMAGE->addFrameImage("�Ϲݺ�", "images/tile/wall_dirt_crypt2.bmp", 48, 48+30, 1, 1, true);

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
	newWall.img = IMAGE->findImage("�Ϲݺ�");
	newWall.x = x ;
	newWall.y = y ;
	newWall.hard = 1;
	newWall._wallType = WALL_TYPE::SOFT_WALL;
	newWall.rc = RectMake(x , y, newWall.img->getFrameWidth(), newWall.img->getFrameHeight());
	
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
	hard_wall = IMAGE->addFrameImage("�ܴ��Ѻ�", "images/tile/wall_catacomb_crypt1.bmp", 48, 48 + 30, 1, 1, true);
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
	newWall.img = IMAGE->findImage("�ܴ��Ѻ�");
	newWall.x = x;
	newWall.y = y;
	newWall.hard = 2;
	newWall._wallType = WALL_TYPE::HARD_WALL;
	newWall.rc = RectMake(x, y, newWall.img->getFrameWidth(), newWall.img->getFrameHeight());

	_vWall.push_back(newWall);
}

void makeHardWall::updateRect(vector<tagWall>::iterator iter)
{
}

makeUnBrokeWall::makeUnBrokeWall()
{
	unBrokeWall = IMAGE->addFrameImage("������", "images/tile/TEMP_wall_unbreakable.bmp", 48, 48 + 40, 1, 1, true);

}

makeUnBrokeWall::~makeUnBrokeWall()
{
}

HRESULT makeUnBrokeWall::init()
{
	return S_OK;
}

void makeUnBrokeWall::release()
{
}

void makeUnBrokeWall::update()
{
}

void makeUnBrokeWall::render()
{
	for (_viWall = _vWall.begin(); _viWall != _vWall.end(); _viWall++)
	{
		if (_isDebug) {
			ZORDER->ZorderRectangle(_viWall->rc, 4);
		}
		ZORDER->ZorderFrameRender(unBrokeWall, 3, _viWall->rc.bottom, _viWall->x, _viWall->y);
	}
}

void makeUnBrokeWall::eraseWall(int x, int y)
{
	for (_viWall = _vWall.begin(); _viWall != _vWall.end(); _viWall++)
	{
		if (x == _viWall->x && y == _viWall->y)
		{
			_vWall.erase(_viWall);
		}
	}
}

void makeUnBrokeWall::addWall(float x, float y)
{
	tagWall newWall;
	newWall.img = IMAGE->findImage("������");
	newWall.x = x;
	newWall.y = y;
	newWall.hard = 3;
	newWall._wallType = WALL_TYPE::BLACK_WALL;
	newWall.rc = RectMake(x, y, newWall.img->getFrameWidth(), newWall.img->getFrameHeight());

	_vWall.push_back(newWall);
}

void makeUnBrokeWall::updateRect(vector<tagWall>::iterator iter)
{
}
