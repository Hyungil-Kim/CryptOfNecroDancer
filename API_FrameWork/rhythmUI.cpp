#include "framework.h"
#include "rhythmUI.h"
#include "wallManager.h"
#include "monsterManager.h"
#include "bossMap.h"
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
	_check = 1.81;//1.2;
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
		static bool prevCol = false;
		bool isCol = false;
		for (_vibeat = _vbeat.begin(); _vibeat != _vbeat.end(); _vibeat++)
		{
			if (_vibeat->iscol == true)
			{
				ZORDER->UIRectangleColor(rc, 9,MINT);
				isCol = true;

				break;
			}
		}

		if (isCol && !prevCol)
		{
			char str[128] = { };
			sprintf_s(str, "worldTime : %f\n", TIME->getWorldTime());
			OutputDebugString(str);
		}

		prevCol = isCol;

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
	newbeat.speed = (WINSIZEX * 0.5f) / 1.9167;
	newbeat.iscol = false;
	newbeat.count = 0;
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
	newbeat.speed = -(WINSIZEX * 0.5f) / 1.9167;
	newbeat.iscol = false;
	newbeat.count = 0;
	newbeat.x = WINSIZEX / 2 + x;
	newbeat.y = WINSIZEY - 74;
	newbeat.rc = RectMake(newbeat.x, newbeat.y, newbeat._bluebeatImg->getWidth(), newbeat._bluebeatImg->getHeight());
	_vbeat.push_back(newbeat);
}

void rhythmUI::moveBeat()
{
	float deltaTime = TIME->getElapsedTime();
	for (_vibeat = _vbeat.begin(); _vibeat != _vbeat.end(); ++_vibeat)
	{
		float delta = _vibeat->speed * deltaTime;
		_vibeat->x += delta;

		_vibeat->rc = RectMakeCenter(_vibeat->x+5, _vibeat->y+30,
			_vibeat->_bluebeatImg->getWidth(),
			_vibeat->_bluebeatImg->getHeight());

		//if (_vibeat->x == WINSIZEX / 2 + 32)
		//{
		//	_vibeat = _vbeat.erase(_vibeat);
		//}
		//else
		//{
		//	++_vibeat;
		//}
	}
}


 
void rhythmUI::step()
{

	for (_vibeat = _vbeat.begin(); _vibeat != _vbeat.end();)
	{
		_vibeat->count +=  TIME->getElapsedTime();
		_vibeat->iscol = (_check-0.46 < _vibeat->count) && (_check+0.46  > _vibeat->count);

		if ((_check < _vibeat->count))
		{
			_vibeat = _vbeat.erase(_vibeat);
		}
		else
		{
			++_vibeat;
		}
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
