#include "framework.h"
#include "rhythmUI.h"
#include "wallManager.h"
rhythmUI::rhythmUI()
{
	
	IMAGE->addImage("청색바", "images/UI/TEMP_beat_marker.bmp", 12, 64, true);
	IMAGE->addImage("녹색바", "images/UI/TEMP_beat_marker_green.bmp", 12, 64, true);
	IMAGE->addImage("적색바", "images/UI/TEMP_beat_marker_red.bmp", 12, 64, true);
}

rhythmUI::~rhythmUI()
{
}

HRESULT rhythmUI::init()
{
	
	_heartImage = IMAGE->addFrameImage("심장", "images/UI/TEMP_beat_heart.bmp", 82 * 2, 52 * 2, 2, 1, true);
	_heartAni = ANIMATION->addNoneKeyAnimation("심장", 10, false, true);
	_heartY = WINSIZEY * 8 / 10;
	return S_OK;
}

void rhythmUI::release()
{
}

void rhythmUI::update()
{
	moveBeat();
	
}

void rhythmUI::render(HDC hdc)
{
	UIrender(hdc);
	
}

void rhythmUI::UIrender(HDC hdc)
{
	POINT temp;
	temp.x = (PLAYER->getPlayerAddress().x - CAMERA->getRect().left) * GAMEDCRATIO;
	temp.y = (PLAYER->getPlayerAddress().y - CAMERA->getRect().top) * GAMEDCRATIO;
	ZORDER->UIAniRender(_heartImage, 8, 3000, WINSIZEX/2,WINSIZEY -200, _heartAni);
	for (_vibeat = _vbeat.begin(); _vibeat != _vbeat.end(); _vibeat++)
	{
	ZORDER->UIRender(_vibeat->_bluebeatImg, 8, 2500, _vibeat->x,_vibeat->y);
	}
	
}


void rhythmUI::spawnBeat(int x, int y)
{
	tagerhythm newbeatL;
	newbeatL.x = WINSIZEX/2 - x;
	newbeatL.y = WINSIZEY - 200;
	newbeatL._bluebeatImg = IMAGE->findImage("청색바");
	newbeatL._greenbeatImg = IMAGE->findImage("녹색바");
	newbeatL._redbeatImg = IMAGE->findImage("적색바");
	newbeatL.rc = RectMake(x, y, newbeatL._bluebeatImg->getFrameWidth(), newbeatL._bluebeatImg->getFrameHeight());
	newbeatL.speed = 3;
	_vbeat.push_back(newbeatL);

	tagerhythm newbeatR;
	newbeatR.x = WINSIZEX / 2 + x;
	newbeatR.y = WINSIZEY - 200;
	newbeatR._bluebeatImg = IMAGE->findImage("청색바");
	newbeatR._greenbeatImg = IMAGE->findImage("녹색바");
	newbeatR._redbeatImg = IMAGE->findImage("적색바");
	newbeatR.rc = RectMake(x, y, newbeatR._bluebeatImg->getFrameWidth(), newbeatR._bluebeatImg->getFrameHeight());
	newbeatR.speed = -3;
	_vbeat.push_back(newbeatR);
}

void rhythmUI::moveBeat()
{
	for (_vibeat = _vbeat.begin(); _vibeat != _vbeat.end(); )
	{
		_vibeat->x += _vibeat->speed;

		_vibeat->rc = RectMakeCenter(_vibeat->x, _vibeat->y,
			_vibeat->_bluebeatImg->getWidth(),
			_vibeat->_bluebeatImg->getHeight());
		if (step() == true || step() == false )
		{
			_vbeat.erase(_vibeat);
		}
		else
		{
			_vibeat++;
		}
	}
}

bool rhythmUI::step()
{
	RECT rctemp;
	if (IntersectRect(&rctemp, &_vibeat->rc, &PLAYER->getPlayerAddress().player_rc) && PLAYER->getPlayerAddress().isInput == true)
	{
		return true;
	}
	else if (IntersectRect(&rctemp, &_vibeat->rc, &PLAYER->getPlayerAddress().player_rc) && PLAYER->getPlayerAddress().isInput == false)
	{
		return false;
	}
}
