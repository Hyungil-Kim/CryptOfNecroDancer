#include "framework.h"
#include "rhythmUI.h"
#include "wallManager.h"
rhythmUI::rhythmUI()
{

}

rhythmUI::~rhythmUI()
{
}

HRESULT rhythmUI::init()
{
	IMAGE->addImage("청색바", "images/UI/TEMP_beat_marker.bmp", 12, 64, true);
	IMAGE->addImage("녹색바", "images/UI/TEMP_beat_marker_green.bmp", 12, 64, true);
	IMAGE->addImage("적색바", "images/UI/TEMP_beat_marker_red.bmp", 12, 64, true);
	_heartImage = IMAGE->addFrameImage("심장", "images/UI/TEMP_beat_heart.bmp", 82 * 2, 52 * 2, 2, 1, true);
	_heartAni = ANIMATION->addNoneKeyAnimation("심장",1,0,4, false, true);
	return S_OK;
}

void rhythmUI::release()
{
}

void rhythmUI::update()
{
 	
	moveBeat();
	
}

void rhythmUI::render()
{
	UIrender();
	
}

void rhythmUI::UIrender()
{
	POINT temp;
	temp.x = (PLAYER->getPlayerAddress().x - CAMERA->getRect().left) * GAMEDCRATIO;
	temp.y = (PLAYER->getPlayerAddress().y - CAMERA->getRect().top) * GAMEDCRATIO;
	rc = RectMake(WINSIZEX / 2 - 30, WINSIZEY - 104,_heartImage->getFrameWidth(),_heartImage->getFrameHeight());
	ZORDER->UIAniRender(_heartImage, 8, 3000, WINSIZEX/2-30,WINSIZEY -104, _heartAni);

	for (_vibeat = _vbeat.begin(); _vibeat != _vbeat.end(); _vibeat++)
	{
		ZORDER->UIRender(_vibeat->_bluebeatImg, 8, 2500, _vibeat->x, _vibeat->y);
	}
	if (_isDebug)
	{
		for (_vibeat = _vbeat.begin(); _vibeat != _vbeat.end(); _vibeat++)
		{
			if (_vibeat->iscol == true)
			{
				ZORDER->UIRectangleColor(rc, 9,MINT);
			}
		}
	}
}


void rhythmUI::spawnBeat(int x, int y)
{
	tagerhythm newbeat;
	ZeroMemory(&newbeat, sizeof(tagerhythm));
	newbeat._bluebeatImg = new image;
	newbeat._greenbeatImg = new image;
	newbeat._redbeatImg = new image;
	newbeat._bluebeatImg = IMAGE->findImage("청색바");
	newbeat._greenbeatImg = IMAGE->findImage("녹색바");
	newbeat._redbeatImg = IMAGE->findImage("적색바");
	newbeat.speed = 8;
	newbeat.iscol = false;
	newbeat.count = 0.25;
	newbeat.x = WINSIZEX/2 - x;
	newbeat.y = WINSIZEY - 74;
	newbeat.rc = RectMake(newbeat.x, newbeat.y, newbeat._bluebeatImg->getWidth(), newbeat._bluebeatImg->getHeight());
	_vbeat.push_back(newbeat);

	ZeroMemory(&newbeat, sizeof(tagerhythm));
	newbeat._bluebeatImg = new image;
	newbeat._greenbeatImg = new image;
	newbeat._redbeatImg = new image;
	newbeat._bluebeatImg = IMAGE->findImage("청색바");
	newbeat._greenbeatImg = IMAGE->findImage("녹색바");
	newbeat._redbeatImg = IMAGE->findImage("적색바");
	newbeat.speed = -8;
	newbeat.iscol = false;
	newbeat.count = 0.3;
	newbeat.x = WINSIZEX / 2 + x;
	newbeat.y = WINSIZEY - 74;
	newbeat.rc = RectMake(newbeat.x, newbeat.y, newbeat._bluebeatImg->getWidth(), newbeat._bluebeatImg->getHeight());
	_vbeat.push_back(newbeat);
}

void rhythmUI::moveBeat()
{
	for (_vibeat = _vbeat.begin(); _vibeat != _vbeat.end(); )
	{
		_vibeat->x += cosf(0) * _vibeat->speed;
		_vibeat->y -= sinf(0) * _vibeat->speed;

		_vibeat->rc = RectMakeCenter(_vibeat->x+5, _vibeat->y+30,
			_vibeat->_bluebeatImg->getWidth(),
			_vibeat->_bluebeatImg->getHeight());
		if (_vibeat->x == WINSIZEX / 2 + 32)
		{
			_vibeat = _vbeat.erase(_vibeat);
		}
		else
		{
			++_vibeat;
		}
	}
}



void rhythmUI::step()
{
	for (_vibeat = _vbeat.begin(); _vibeat != _vbeat.end();++_vibeat)
	{
		_vibeat->count +=  TIME->getElapsedTime();
		_vibeat->iscol = (1.3 < _vibeat->count);
	}
}

bool rhythmUI::checkstep()
{
	
	for (_vibeat = _vbeat.begin(); _vibeat != _vbeat.end(); ++_vibeat)
	{
		if (_vibeat->iscol == true)
		{
			return true;
		}

	}
	return false;

}
