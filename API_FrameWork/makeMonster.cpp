#include "framework.h"
#include "makeMonster.h"
/*
================================================ =
Find monster class ctrl + F4("name!")
================================================ =
monstername					imagename
1.	green_slime				�׸�������
2.	blue_slime				��罽����
3.	
4	
5.	
6.	
7.	
8.	
9.	
10. 
11. 
12. 
13. 
14.	
15.	
16.
17.
*/
//////////////////////////////////////////////////////////////
//////////////////////green_slime!	�׸�������!//////////////////////////
//////////////////////////////////////////////////////////////
green_slime::green_slime()
{
	IMAGE->addFrameImage("�׸�������", "images/monster/slime_green.bmp", 104, 52, 4, 2, true);
	
}

green_slime::~green_slime()
{
}

HRESULT green_slime::init()
{
	return S_OK;
}

void green_slime::release()
{
}

void green_slime::update(Player* cp)
{
	
}

void green_slime::render()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		switch (_viMonster->monsterState)
		{
		case MONSTERSTATE::MOVE:
		case MONSTERSTATE::ATTACK:
		case MONSTERSTATE::DIGGING:
		case MONSTERSTATE::HIT:
		case MONSTERSTATE::STOP:
			if (_isDebug) {
				ZORDER->ZorderRectangle(_viMonster->rc, 3);
			}
			ZORDER->ZorderAniRender(_viMonster->img, 4, _viMonster->rc.bottom, _viMonster->x, _viMonster->y, _viMonster->ani);
			break;
		case MONSTERSTATE::DEAD:
			break;
		}
	}
}

void green_slime::addMonster(float x, float y)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("�׸�������");
	newMonster.x = x;
	newMonster.y = y;
	newMonster.rc = RectMake(x, y, newMonster.img->getFrameWidth(), newMonster.img->getFrameHeight());
	newMonster.hp = 4;
	newMonster.atk = 2;
	newMonster.ani = ANIMATION->addNoneKeyAnimation("�׸�������",0,3, 5, false,true);
	newMonster.shadowani = ANIMATION->addNoneKeyAnimation("�׸�������",4,7,5,false,true);
	newMonster.canBreakWall = false;
	newMonster.isDetecting = false;
	newMonster.isDead = false;
	newMonster.isHit = false;
	newMonster.isCurrentRight = false;
	newMonster.monsterState = MONSTERSTATE::STOP;
	newMonster.monsterMoveState = MONSTERMOVESTATE::NONE;
	_vMonster.push_back(newMonster);
}


void green_slime::stateCheck()
{
}

void green_slime::moveMonster()
{
}
//////////////////////////////////////////////////////////////
//////////////////////blue!	��罽����!//////////////////////////
//////////////////////////////////////////////////////////////
blue_slime::blue_slime()
{
	IMAGE->addFrameImage("��罽����", "images/monster/slime_blue.bmp", 208, 50, 8, 2, true);
}

blue_slime::~blue_slime()
{
}

HRESULT blue_slime::init()
{
	return S_OK;
}

void blue_slime::release()
{
}

void blue_slime::update(Player* cp)
{
	moveMonster();
}

void blue_slime::render()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		switch (_viMonster->monsterState)
		{
		case MONSTERSTATE::MOVE:
		case MONSTERSTATE::ATTACK:
		case MONSTERSTATE::DIGGING:
		case MONSTERSTATE::HIT:
		case MONSTERSTATE::STOP:
			if (_isDebug) {
				ZORDER->ZorderRectangle(_viMonster->rc, 3);
			}
			ZORDER->ZorderAniRender(_viMonster->img, 4, _viMonster->rc.bottom, _viMonster->x, _viMonster->y, _viMonster->ani);
			break;
		case MONSTERSTATE::DEAD:
			break;
		}
	}
}

void blue_slime::addMonster(float x, float y)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("��罽����");
	newMonster.x = x;
	newMonster.y = y;
	newMonster.rc = RectMake(x, y, newMonster.img->getFrameWidth(), newMonster.img->getFrameHeight());
	newMonster.hp = 4;
	newMonster.atk = 2;
	newMonster.ani = ANIMATION->addNoneKeyAnimation("��罽����", 0, 7, 4, false, true);
	newMonster.shadowani = ANIMATION->addNoneKeyAnimation("��罽����", 8,15, 5, false, true);
	newMonster.canBreakWall = false;
	newMonster.isDetecting = false;
	newMonster.isDead = false;
	newMonster.isHit = false;
	newMonster.isCurrentRight = false;
	newMonster.isMove = false;
	newMonster.isOnceMove = false;
	newMonster.monsterState = MONSTERSTATE::STOP;
	newMonster.monsterMoveState = MONSTERMOVESTATE::NONE;
	_vMonster.push_back(newMonster);
}

void blue_slime::stateCheck()
{
}

void blue_slime::moveMonster()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		if (_viMonster->ani->findNowPlayIndex() == 7 && _viMonster->isOnceMove == false && _viMonster->isMove ==false)
		{
			_viMonster->y -= 33;
			_viMonster->isMove = true;
			_viMonster->isOnceMove = true;
		}
		if (_viMonster->ani->findNowPlayIndex() == 7 && _viMonster->isOnceMove == false && _viMonster->isMove == true)
		{
			_viMonster->y += 33;
			_viMonster->isMove = false;
			_viMonster->isOnceMove = true;
		}
		if (_viMonster->ani->findNowPlayIndex() == 0)
		{
			_viMonster->isOnceMove = false;
		}
	}
}
