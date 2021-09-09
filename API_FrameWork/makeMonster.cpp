#include "framework.h"
#include "makeMonster.h"
#include "rhythmUI.h"
#include "wallManager.h"
#include "realwallManager.h"
#include "bossMap.h"
/*
================================================ =
Find monster class ctrl + F4("name!")
================================================ =
monstername					imagename
1.	green_slime				그린슬라임
2.	blue_slime				블루슬라임
3.	orange_slime			오랜지슬라임
4	skeleton
5.

*/
//////////////////////////////////////////////////////////////
//////////////////////green_slime!	그린슬라임!//////////////////////////
//////////////////////////////////////////////////////////////
green_slime::green_slime()
{
	IMAGE->addFrameImage("그린슬라임", "images/monster/slime_green.bmp", 48 * 4, 48 * 2, 4, 2, true);

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
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end();)
	{
		deathcheck();
		if (_viMonster->monsterState == MONSTERSTATE::DEAD)
		{
			if (!(SOUND->isPlaySound("slimedeath")))
			{
				SOUND->play("slimedeath",0.5);
			}
			_viMonster = _vMonster.erase(_viMonster);
		}
		else
		{
			++_viMonster;
		}
	}
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		RectMake(_viMonster->x, _viMonster->y, _viMonster->img->getFrameWidth(), _viMonster->img->getFrameHeight());
	}
}

void green_slime::render()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		if (_viMonster->hp != _viMonster->maxhp)
			showhp();

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
	newMonster.img = IMAGE->findImage("그린슬라임");
	newMonster.x = x;
	newMonster.y = y;
	newMonster.posx = x / 48;
	newMonster.posy = y / 48;
	newMonster.rc = RectMake(x, y, newMonster.img->getFrameWidth(), newMonster.img->getFrameHeight());
	newMonster.maxhp = 2;
	newMonster.hp = 2;
	newMonster.atk = 2;
	newMonster.ani = ANIMATION->addNoneKeyAnimation("그린슬라임", 0, 3, 5, false, true);
	newMonster.shadowani = ANIMATION->addNoneKeyAnimation("그린슬라임", 4, 7, 5, false, true);
	newMonster.m_emptyheart = IMAGE->findImage("몬스터빈하트");
	newMonster.m_heart = IMAGE->findImage("몬스터하트");
	newMonster.m_halfheart = IMAGE->findImage("몬스터절반하트");
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
void green_slime::dead()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); _viMonster++)
	{
		if (_viMonster->hp <= 0)
		{
			_vMonster.erase(_viMonster);
		}
	}
}
void green_slime::updateRect(vector<tagMonster>::iterator iter)
{
	iter->rc = RectMake(iter->x, iter->y, iter->img->getFrameWidth(), iter->img->getFrameHeight());
}
//////////////////////////////////////////////////////////////
//////////////////////blue!	블루슬라임!//////////////////////////
//////////////////////////////////////////////////////////////
blue_slime::blue_slime()
{
	IMAGE->addFrameImage("블루슬라임", "images/monster/slime_blue.bmp", 48 * 8, 48 * 2, 8, 2, true);

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
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end();)
	{
		deathcheck();
		if (_viMonster->monsterState == MONSTERSTATE::DEAD)
		{
			if (!(SOUND->isPlaySound("slimedeath")))
			{
				SOUND->play("slimedeath", 0.5);
			}
			_viMonster = _vMonster.erase(_viMonster);
		}
		else
		{
			++_viMonster;
		}
	}
	moveMonster();
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		checkInvincibility();
	}
}

void blue_slime::render()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		if (_viMonster->hp != _viMonster->maxhp)
			showhp();
		switch (_viMonster->monsterState)
		{
		case MONSTERSTATE::ATTACK:
			if (_viMonster->atkdown == true)
			{
				ZORDER->ZorderAniRender(_viMonster->_atkup, 6, 0, _viMonster->x, _viMonster->y + 24, _viMonster->A_atkdown);
			}
			if (_viMonster->atkup == true)
			{
				ZORDER->ZorderAniRender(_viMonster->_atkup, 6, 0, _viMonster->x, _viMonster->y - 24, _viMonster->A_atkup);
			}
			if (_viMonster->atkright == true)
			{
				ZORDER->ZorderAniRender(_viMonster->_atkleft, 6, 0, _viMonster->x - 24, _viMonster->y, _viMonster->A_atkright);
			}
			if (_viMonster->atkleft == true)
			{
				ZORDER->ZorderAniRender(_viMonster->_atkleft, 6, 0, _viMonster->x + 24, _viMonster->y, _viMonster->A_atkleft);
			}
		case MONSTERSTATE::MOVE:
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
	newMonster.img = IMAGE->findImage("블루슬라임");
	newMonster.x = x;
	newMonster.y = y;
	newMonster.posx = x / 48;
	newMonster.posy = y / 48;
	newMonster.rc = RectMake(x, y, newMonster.img->getFrameWidth(), newMonster.img->getFrameHeight());
	newMonster.maxhp = 4;
	newMonster.hp = 4;
	newMonster.atk = 2;
	newMonster.ani = ANIMATION->addNoneKeyAnimation("블루슬라임", 0, 7, 4, false, true);
	newMonster.shadowani = ANIMATION->addNoneKeyAnimation("블루슬라임", 8, 15, 5, false, true);
	newMonster._atkup = IMAGE->findImage("상하공격");
	newMonster.A_atkdown = ANIMATION->addNoneKeyAnimation("상하공격", 0, 4, 5, false, true);
	newMonster.A_atkup = ANIMATION->addNoneKeyAnimation("상하공격", 9, 5, 5, false, true);
	newMonster.m_emptyheart = IMAGE->findImage("몬스터빈하트");
	newMonster.m_heart = IMAGE->findImage("몬스터하트");
	newMonster.m_halfheart = IMAGE->findImage("몬스터절반하트");
	newMonster.canBreakWall = false;
	newMonster.isDetecting = false;
	newMonster.isDead = false;
	newMonster.isHit = 0;
	newMonster.isCurrentRight = false;
	newMonster.isMove = false;
	newMonster.candown = false;
	newMonster.canup = false;
	newMonster.atkup = false;
	newMonster.atkdown = false;
	newMonster.speed = 4;
	newMonster.isGraceperiod = false;
	newMonster.gracePeriodCount = 0;
	newMonster.limit = TILE_SIZE_Y;
	newMonster.isOnceMove = false;
	newMonster.monsterState = MONSTERSTATE::STOP;
	newMonster.monsterMoveState = MONSTERMOVESTATE::UP;
	_vMonster.push_back(newMonster);
}

void blue_slime::stateCheck()
{
}

void blue_slime::moveMonster()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		_viMonster->posy = _viMonster->y / 48;
		if (_viMonster->ani->findNowPlayIndex() == 7 && _viMonster->isOnceMove == false && _viMonster->isMove == false)
		{
			isCanMove();
			if (_viMonster->canup == true)
			{
				_viMonster->monsterState = MONSTERSTATE::MOVE;
				_viMonster->y -= 4;
				_viMonster->limit -= _viMonster->speed;
				if (_viMonster->limit - _viMonster->speed <= -2)
				{
					_viMonster->limit = TILE_SIZE_Y;
					_viMonster->isMove = true;
					_viMonster->isOnceMove = true;
					_viMonster->monsterMoveState = MONSTERMOVESTATE::DOWN;
					updateRect(_viMonster);
					_viMonster->canup = false;

				}
			}
			else if (_viMonster->atkup == true)
			{
				_viMonster->monsterState = MONSTERSTATE::ATTACK;
				_viMonster->atkdown = false;
				_viMonster->atkright = false;
				_viMonster->atkleft = false;
				if (_viMonster->isGraceperiod == false) attack();
				_viMonster->isGraceperiod = true;

			}
		}
		_viMonster->posy = _viMonster->y / 48;
		if (_viMonster->ani->findNowPlayIndex() == 7 && _viMonster->isOnceMove == false && _viMonster->isMove == true)
		{
			isCanMove();
			if (_viMonster->candown == true)
			{
				_viMonster->monsterState = MONSTERSTATE::MOVE;
				_viMonster->y += _viMonster->speed;
				_viMonster->limit -= _viMonster->speed;
				if (_viMonster->limit - _viMonster->speed <= -2)
				{

					_viMonster->limit = TILE_SIZE_Y;
					_viMonster->isMove = false;
					_viMonster->isOnceMove = true;
					_viMonster->monsterMoveState = MONSTERMOVESTATE::UP;
					updateRect(_viMonster);
					_viMonster->candown = false;
				}
			}
			else if (_viMonster->atkdown == true)
			{
				_viMonster->monsterState = MONSTERSTATE::ATTACK;
				_viMonster->atkup = false;
				_viMonster->atkright = false;
				_viMonster->atkleft = false;
				if (_viMonster->isGraceperiod == false) attack();
				_viMonster->isGraceperiod = true;
			}
		}
		if (_viMonster->ani->findNowPlayIndex() == 0)
		{
			_viMonster->isOnceMove = false;
			_viMonster->isHit = 0;
		}
	}
}

void blue_slime::movestate()
{

}

void blue_slime::updateRect(vector<tagMonster>::iterator iter)
{
	iter->rc = RectMake(iter->x, iter->y, iter->img->getFrameWidth(), iter->img->getFrameHeight());
}



//////////////////////////////////////////////////////////////
//////////////////////orange_slime!	오랜지슬라임!//////////////////////////
//////////////////////////////////////////////////////////////

orange_slime::orange_slime()
{
	IMAGE->addFrameImage("주황슬라임", "images/monster/slime_orange.bmp", 48 * 8, 48 * 2, 8, 2, true);
}

orange_slime::~orange_slime()
{
}

HRESULT orange_slime::init()
{
	return S_OK;
}

void orange_slime::release()
{
}

void orange_slime::update(Player* cp)
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end();)
	{
		deathcheck();
		if (_viMonster->monsterState == MONSTERSTATE::DEAD)
		{
			if (!(SOUND->isPlaySound("slimedeath")))
			{
				SOUND->play("slimedeath", 0.5);
			}
			_viMonster = _vMonster.erase(_viMonster);
		}
		else
		{
			++_viMonster;
		}
	}
	moveMonster();
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		checkInvincibility();
	}
}

void orange_slime::render()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		if (_viMonster->hp != _viMonster->maxhp)
			showhp();
		switch (_viMonster->monsterState)
		{
		case MONSTERSTATE::ATTACK:
			if (_viMonster->atkdown == true)
			{
				ZORDER->ZorderAniRender(_viMonster->_atkup, 6, 0, _viMonster->x, _viMonster->y + 24, _viMonster->A_atkdown);
			}
			if (_viMonster->atkup == true)
			{
				ZORDER->ZorderAniRender(_viMonster->_atkup, 6, 0, _viMonster->x, _viMonster->y - 24, _viMonster->A_atkup);
			}
			if (_viMonster->atkright == true)
			{
				ZORDER->ZorderAniRender(_viMonster->_atkleft, 6, 0, _viMonster->x + 24, _viMonster->y, _viMonster->A_atkright);
			}
			if (_viMonster->atkleft == true)
			{
				ZORDER->ZorderAniRender(_viMonster->_atkleft, 6, 0, _viMonster->x - 24, _viMonster->y, _viMonster->A_atkleft);
			}
		case MONSTERSTATE::MOVE:
		case MONSTERSTATE::DIGGING:
		case MONSTERSTATE::HIT:
		case MONSTERSTATE::STOP:
			if (_isDebug) {
				ZORDER->ZorderRectangle(_viMonster->rc, 3);
			}
			if (_viMonster->AniLeft == true)
			{
				ZORDER->ZorderAniRender(_viMonster->img, 4, _viMonster->rc.bottom, _viMonster->x, _viMonster->y, _viMonster->ani);
			}
			else
			{
				ZORDER->ZorderAniRender(_viMonster->img, 4, _viMonster->rc.bottom, _viMonster->x, _viMonster->y, _viMonster->leftani);
			}
			break;
		case MONSTERSTATE::DEAD:
			break;
		}
	}
}

void orange_slime::addMonster(float x, float y)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("주황슬라임");
	newMonster.x = x;
	newMonster.y = y;
	newMonster.posx = x / 48;
	newMonster.posy = y / 48;
	newMonster.rc = RectMake(x, y, newMonster.img->getFrameWidth(), newMonster.img->getFrameHeight());
	newMonster.maxhp = 4;
	newMonster.hp = 4;
	newMonster.atk = 2;
	newMonster.ani = ANIMATION->addNoneKeyAnimation("주황슬라임", 0, 3, 4, false, true);
	newMonster.leftani = ANIMATION->addNoneKeyAnimation("주황슬라임", 4, 7, 4, false, true);
	newMonster.shadowani = ANIMATION->addNoneKeyAnimation("주황슬라임", 15, 12, 4, false, true);
	newMonster.shadowani = ANIMATION->addNoneKeyAnimation("주황슬라임", 11, 8, 4, false, true);
	newMonster._atkup = IMAGE->findImage("상하공격");
	newMonster._atkleft = IMAGE->findImage("좌우공격");
	newMonster.A_atkdown = ANIMATION->addNoneKeyAnimation("상하공격", 0, 4, 5, false, true);
	newMonster.A_atkup = ANIMATION->addNoneKeyAnimation("상하공격", 9, 5, 5, false, true);
	newMonster.A_atkright = ANIMATION->addNoneKeyAnimation("좌우공격", 0, 4, 5, false, true);
	newMonster.A_atkleft = ANIMATION->addNoneKeyAnimation("좌우공격", 9, 5, 5, false, true);
	newMonster.m_emptyheart = IMAGE->findImage("몬스터빈하트");
	newMonster.m_heart = IMAGE->findImage("몬스터하트");
	newMonster.m_halfheart = IMAGE->findImage("몬스터절반하트");
	newMonster.canBreakWall = false;
	newMonster.isDetecting = false;
	newMonster.isDead = false;
	newMonster.isHit = false;
	newMonster.isCurrentRight = false;
	newMonster.isMove = false;
	newMonster.AniLeft = true;
	newMonster.limit = TILE_SIZE_Y;
	newMonster.speed = 4;
	newMonster.isOnceMove = false;
	newMonster.monsterState = MONSTERSTATE::STOP;
	newMonster.monsterMoveState = MONSTERMOVESTATE::UP;
	_vMonster.push_back(newMonster);
}

void orange_slime::stateCheck()
{
}

void orange_slime::moveMonster()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		_viMonster->posy = _viMonster->y / 48;
		if (_viMonster->ani->findNowPlayIndex() == 3 && _viMonster->isOnceMove == false && _viMonster->isMove == false && _viMonster->AniLeft == true)
		{

			isCanMove();
			if (_viMonster->canup == true)
			{
				_viMonster->y -= _viMonster->speed;
				_viMonster->limit -= _viMonster->speed;
				_viMonster->monsterState = MONSTERSTATE::MOVE;
				if (_viMonster->limit - _viMonster->speed <= -2)
				{
					_viMonster->limit = TILE_SIZE_Y;
					_viMonster->isMove = true;
					_viMonster->isOnceMove = true;
					_viMonster->canup = false;
					updateRect(_viMonster);
					_viMonster->monsterMoveState = MONSTERMOVESTATE::LEFT;
				}
			}
			else if (_viMonster->atkup == true)
			{
				_viMonster->monsterState = MONSTERSTATE::ATTACK;
				_viMonster->atkdown = false;
				_viMonster->atkright = false;
				_viMonster->atkleft = false;
				if (_viMonster->isGraceperiod == false) attack();
				_viMonster->isGraceperiod = true;
			}
		}
		_viMonster->posx = _viMonster->x / 48;
		if (_viMonster->ani->findNowPlayIndex() == 3 && _viMonster->isOnceMove == false && _viMonster->isMove == true && _viMonster->AniLeft == true)
		{
			isCanMove();
			if (_viMonster->canleft == true)
			{
				_viMonster->x -= _viMonster->speed;
				_viMonster->limit -= _viMonster->speed;
				_viMonster->monsterState = MONSTERSTATE::MOVE;
				if (_viMonster->limit - _viMonster->speed <= -2)
				{
					_viMonster->limit = TILE_SIZE_Y;
					_viMonster->isMove = false;
					_viMonster->isOnceMove = true;
					_viMonster->AniLeft = false;
					_viMonster->canleft = false;
					updateRect(_viMonster);
					_viMonster->monsterMoveState = MONSTERMOVESTATE::DOWN;
				}
			}
			else if (_viMonster->atkleft == true)
			{
				_viMonster->monsterState = MONSTERSTATE::ATTACK;
				_viMonster->atkup = false;
				_viMonster->atkdown = false;
				_viMonster->atkright = false;
				if (_viMonster->isGraceperiod == false) attack();
				_viMonster->isGraceperiod = true;
			}
		}
		_viMonster->posy = _viMonster->y / 48;
		if (_viMonster->ani->findNowPlayIndex() == 3 && _viMonster->isOnceMove == false && _viMonster->isMove == false && _viMonster->AniLeft == false)
		{
			isCanMove();
			if (_viMonster->candown == true)
			{
				_viMonster->y += _viMonster->speed;
				_viMonster->limit -= _viMonster->speed;
				_viMonster->monsterState = MONSTERSTATE::MOVE;
				if (_viMonster->limit - _viMonster->speed <= -2)
				{
					_viMonster->limit = TILE_SIZE_Y;
					_viMonster->isMove = true;
					_viMonster->candown = false;
					_viMonster->isOnceMove = true;
					updateRect(_viMonster);
					_viMonster->monsterMoveState = MONSTERMOVESTATE::RIGHT;
				}
			}
			else if (_viMonster->atkdown == true)
			{
				_viMonster->monsterState = MONSTERSTATE::ATTACK;
				_viMonster->atkup = false;
				_viMonster->atkright = false;
				_viMonster->atkleft = false;
				if (_viMonster->isGraceperiod == false) attack();
				_viMonster->isGraceperiod = true;
			}
		}
		_viMonster->posx = _viMonster->x / 48;
		if (_viMonster->ani->findNowPlayIndex() == 3 && _viMonster->isOnceMove == false && _viMonster->isMove == true && _viMonster->AniLeft == false)
		{
			isCanMove();
			if (_viMonster->canright == true)
			{
				_viMonster->x += _viMonster->speed;
				_viMonster->limit -= _viMonster->speed;
				_viMonster->monsterState = MONSTERSTATE::MOVE;
				if (_viMonster->limit - _viMonster->speed <= -2)
				{
					_viMonster->limit = TILE_SIZE_Y;
					_viMonster->isMove = false;
					_viMonster->isOnceMove = true;
					_viMonster->canright = false;
					_viMonster->AniLeft = true;
					updateRect(_viMonster);
					_viMonster->monsterMoveState = MONSTERMOVESTATE::UP;
				}
			}
			else if (_viMonster->atkright == true)
			{
				_viMonster->monsterState = MONSTERSTATE::ATTACK;
				_viMonster->atkup = false;
				_viMonster->atkdown = false;
				_viMonster->atkleft = false;
				if (_viMonster->isGraceperiod == false) attack();
				_viMonster->isGraceperiod = true;
			}
		}
		if (_viMonster->ani->findNowPlayIndex() == 0)
		{
			_viMonster->isOnceMove = false;
		}
	}
}

void orange_slime::updateRect(vector<tagMonster>::iterator iter)
{
	iter->rc = RectMake(iter->x, iter->y, iter->img->getFrameWidth(), iter->img->getFrameHeight());
}
//////////////////////////////////////////////////////////////
//////////////////////white_skeleton!	해골!//////////////////////////
//////////////////////////////////////////////////////////////
white_skeleton::white_skeleton()
{
	IMAGE->addFrameImage("해골", "images/monster/skeleton.bmp", 48 * 16, 48 * 4, 16, 4, true);
}

white_skeleton::~white_skeleton()
{
}

HRESULT white_skeleton::init()
{
	return S_OK;
}

void white_skeleton::release()
{
}

void white_skeleton::update(rhythmUI* _rtm)
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end();)
	{
		deathcheck();
		if (_viMonster->monsterState == MONSTERSTATE::DEAD)
		{
			if (!(SOUND->isPlaySound("skeldeath")))
			{
				SOUND->play("skeldeath");
			}
			_viMonster = _vMonster.erase(_viMonster);
		}
		else
		{
			++_viMonster;
		}
	}
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		checkInvincibility();
	}

	moveMonster(_rtm);

}

void white_skeleton::render()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		if (_viMonster->hp != _viMonster->maxhp)
			showhp();
		switch (_viMonster->monsterState)
		{
		case MONSTERSTATE::ATTACK:
			if (_viMonster->atkdown == true)
			{
				atkSound();
				ZORDER->ZorderAniRender(_viMonster->_atkup, 6, 0, _viMonster->x, _viMonster->y + 24, _viMonster->A_atkdown);
			}
			if (_viMonster->atkup == true)
			{
				atkSound();
				ZORDER->ZorderAniRender(_viMonster->_atkup, 6, 0, _viMonster->x, _viMonster->y - 24, _viMonster->A_atkup);
			}
			if (_viMonster->atkright == true)
			{
				atkSound();
				ZORDER->ZorderAniRender(_viMonster->_atkleft, 6, 0, _viMonster->x + 24, _viMonster->y, _viMonster->A_atkright);
			}
			if (_viMonster->atkleft == true)
			{
				atkSound();
				ZORDER->ZorderAniRender(_viMonster->_atkleft, 6, 0, _viMonster->x - 24, _viMonster->y, _viMonster->A_atkleft);
			}
		case MONSTERSTATE::MOVE:
		case MONSTERSTATE::DIGGING:
		case MONSTERSTATE::HIT:
		case MONSTERSTATE::STOP:
			if (_isDebug) {
				ZORDER->ZorderRectangle(_viMonster->rc, 3);
			}

			if (_viMonster->monsterMoveState == MONSTERMOVESTATE::LEFT || _viMonster->monsterMoveState == MONSTERMOVESTATE::DOWN)
			{
				ZORDER->ZorderAniRender(_viMonster->img, 4, _viMonster->rc.bottom, _viMonster->x, _viMonster->y, _viMonster->leftani);
			}
			if (_viMonster->monsterMoveState == MONSTERMOVESTATE::RIGHT || _viMonster->monsterMoveState == MONSTERMOVESTATE::NONE)
			{
				ZORDER->ZorderAniRender(_viMonster->img, 4, _viMonster->rc.bottom, _viMonster->x, _viMonster->y, _viMonster->rightani);
			}
			if (_viMonster->monsterMoveState == MONSTERMOVESTATE::UP)
			{
				ZORDER->ZorderAniRender(_viMonster->img, 4, _viMonster->rc.bottom, _viMonster->x, _viMonster->y, _viMonster->ani);
			}
			break;
		case MONSTERSTATE::DEAD:
			break;
		}
	}
}

void white_skeleton::atkSound()
{
	if (!(SOUND->isPlaySound("skelAtk")))
	{
		SOUND->play("skelAtk");
	}
}

void white_skeleton::addMonster(float x, float y)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("해골");
	newMonster.x = x;
	newMonster.y = y;
	newMonster.posx = x / 48;
	newMonster.posy = y / 48;
	newMonster.rc = RectMake(x, y, newMonster.img->getFrameWidth(), newMonster.img->getFrameHeight());
	newMonster.maxhp = 2;
	newMonster.hp = 2;
	newMonster.atk = 1;
	newMonster.ani = ANIMATION->addNoneKeyAnimation("해골", 8, 15, 4, false, true);
	newMonster.leftani = ANIMATION->addNoneKeyAnimation("해골", 0, 7, 4, false, true);
	newMonster.rightani = ANIMATION->addNoneKeyAnimation("해골", 40, 47, 4, false, true);
	newMonster.shadowani = ANIMATION->addNoneKeyAnimation("해골", 16, 31, 4, false, true);
	newMonster.shadowani = ANIMATION->addNoneKeyAnimation("해골", 48, 63, 4, false, true);
	newMonster._atkup = IMAGE->findImage("상하공격");
	newMonster._atkleft = IMAGE->findImage("좌우공격");
	newMonster.A_atkdown = ANIMATION->addNoneKeyAnimation("상하공격", 0, 4, 5, false, true);
	newMonster.A_atkup = ANIMATION->addNoneKeyAnimation("상하공격", 9, 5, 5, false, true);
	newMonster.A_atkright = ANIMATION->addNoneKeyAnimation("좌우공격", 0, 4, 5, false, true);
	newMonster.A_atkleft = ANIMATION->addNoneKeyAnimation("좌우공격", 9, 5, 5, false, true);
	newMonster.m_emptyheart = IMAGE->findImage("몬스터빈하트");
	newMonster.m_heart = IMAGE->findImage("몬스터하트");
	newMonster.m_halfheart = IMAGE->findImage("몬스터절반하트");
	newMonster.canBreakWall = false;
	newMonster.isDetecting = false;
	newMonster.isDead = false;
	newMonster.isHit = false;
	newMonster.isCurrentRight = false;
	newMonster.isMove = false;
	newMonster.AniLeft = true;
	newMonster.canleft = false;
	newMonster.canright = false;
	newMonster.canup = false;
	newMonster.candown = false;
	newMonster.limit = TILE_SIZE_Y;
	newMonster.speed = 48 * 2;
	newMonster.movecount = 0;
	newMonster.isOnceMove = false;
	newMonster.monsterState = MONSTERSTATE::STOP;
	newMonster.monsterMoveState = MONSTERMOVESTATE::LEFT;
	_vMonster.push_back(newMonster);
}

void white_skeleton::stateCheck()
{
}

void white_skeleton::moveMonster(rhythmUI* _rtm)
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{

		if (_rtm->checkstep() && _viMonster->rtmcount == false)
		{
			_viMonster->movecount += 1;
			_viMonster->rtmcount = true;
		}
		if (!(_rtm->checkstep()))
		{
			_viMonster->rtmcount = false;
		}
		if (_viMonster->movecount >= 3)
		{
			int x = PLAYER->getPlayerAddress().posx;
			int y = PLAYER->getPlayerAddress().posy;
		
				
			
				if ((abs(_viMonster->posx - x) < 6 && abs(_viMonster->posy - y) < 6) || _rwm->getcurScene() == "보스전")
				{
				setdirection();
				switch (_viMonster->monsterMoveState)
				{
				case MONSTERMOVESTATE::LEFT:
					if (_viMonster->atkleft)
					{
						_viMonster->movecount = 0;
						if (_viMonster->isGraceperiod == false) attack();
						_viMonster->isGraceperiod = true;
					}
					else
					{
						_viMonster->movecount = 0;
						_viMonster->posx -= 1;
						_viMonster->x = _viMonster->posx * 48;
						_viMonster->y = _viMonster->posy * 48;
					}
					break;
				case MONSTERMOVESTATE::RIGHT:
					if (_viMonster->atkright)
					{
						_viMonster->movecount = 0;
						if (_viMonster->isGraceperiod == false) attack();
						_viMonster->isGraceperiod = true;
					}
					else
					{
						_viMonster->movecount = 0;
						_viMonster->posx += 1;
						_viMonster->x = _viMonster->posx * 48;
						_viMonster->y = _viMonster->posy * 48;
					}
					break;
				case MONSTERMOVESTATE::UP:
					if (_viMonster->atkup)
					{
						_viMonster->movecount = 0;
						if (_viMonster->isGraceperiod == false) attack();
						_viMonster->isGraceperiod = true;
					}
					else
					{
						_viMonster->movecount = 0;
						_viMonster->posy -= 1;
						_viMonster->x = _viMonster->posx * 48;
						_viMonster->y = _viMonster->posy * 48;
					}
					break;
				case MONSTERMOVESTATE::DOWN:
					if (_viMonster->atkdown)
					{
						_viMonster->movecount = 0;
						if (_viMonster->isGraceperiod == false) attack();
						_viMonster->isGraceperiod = true;
					}
					else
					{
						_viMonster->movecount = 0;
						_viMonster->posy += 1;
						_viMonster->x = _viMonster->posx * 48;
						_viMonster->y = _viMonster->posy * 48;
					}
					break;
				case MONSTERMOVESTATE::NONE:
					_viMonster->movecount = 0;
					_viMonster->posy += 0;
					_viMonster->posx += 0;
					_viMonster->x = _viMonster->posx * 48;
					_viMonster->y = _viMonster->posy * 48;
					break;
				}
			}

		}
	}
}

void white_skeleton::updateRect(vector<tagMonster>::iterator iter)
{
	iter->rc = RectMake(iter->x, iter->y, iter->img->getFrameWidth(), iter->img->getFrameHeight());
}

green_dragon::green_dragon()
{
	IMAGE->addFrameImage("드래곤", "images/monster/green_dragon.bmp", 48 * 8 * 1.5, 48 * 2 * 2, 8, 2, true);
}

green_dragon::~green_dragon()
{
}

HRESULT green_dragon::init()
{
	return S_OK;
}

void green_dragon::release()
{
}

void green_dragon::update(rhythmUI* _rtm)
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end();)
	{
		deathcheck();
		if (_viMonster->monsterState == MONSTERSTATE::DEAD)
		{
			if (!(SOUND->isPlaySound("dragondeath")))
			{
				SOUND->play("dragondeath", 0.5);
			}
			_viMonster = _vMonster.erase(_viMonster);
		}
		else
		{
			++_viMonster;
		}
	}
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		checkInvincibility();
	}

	moveMonster(_rtm, _wm, _rwm);
}

void green_dragon::render()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		if (_viMonster->hp != _viMonster->maxhp)
			showhp();
		switch (_viMonster->monsterState)
		{
		case MONSTERSTATE::ATTACK:
			if (_viMonster->atkdown == true)
			{
				ZORDER->ZorderAniRender(_viMonster->_atkup, 6, 0, _viMonster->x, _viMonster->y + 24, _viMonster->A_atkdown);
			}
			if (_viMonster->atkup == true)
			{
				ZORDER->ZorderAniRender(_viMonster->_atkup, 6, 0, _viMonster->x, _viMonster->y - 24, _viMonster->A_atkup);
			}
			if (_viMonster->atkright == true)
			{
				ZORDER->ZorderAniRender(_viMonster->_atkleft, 6, 0, _viMonster->x + 24, _viMonster->y, _viMonster->A_atkright);
			}
			if (_viMonster->atkleft == true)
			{
				ZORDER->ZorderAniRender(_viMonster->_atkleft, 6, 0, _viMonster->x - 24, _viMonster->y, _viMonster->A_atkleft);
			}
		case MONSTERSTATE::MOVE:
		case MONSTERSTATE::DIGGING:
		case MONSTERSTATE::HIT:
		case MONSTERSTATE::STOP:
			if (_isDebug) {
				ZORDER->ZorderRectangle(_viMonster->rc, 3);
			}

			if (_viMonster->monsterMoveState == MONSTERMOVESTATE::LEFT || _viMonster->monsterMoveState == MONSTERMOVESTATE::DOWN)
			{
				ZORDER->ZorderAniRender(_viMonster->img, 4, _viMonster->rc.bottom, _viMonster->x, _viMonster->y - 48, _viMonster->leftani);
			}
			else
			{
				ZORDER->ZorderAniRender(_viMonster->img, 4, _viMonster->rc.bottom, _viMonster->x, _viMonster->y - 48, _viMonster->rightani);
			}

			break;
		case MONSTERSTATE::DEAD:
			break;
		}
	}
}

void green_dragon::digsound()
{
	if (!(SOUND->isPlaySound("dirtdig")))
	{
		SOUND->play("dirtdig", 0.5);
	}
}

void green_dragon::movesound()
{
	if (!(SOUND->isPlaySound("dragonmove")))
	{
		SOUND->play("dragonmove", 0.5);
	}
}

void green_dragon::atksound()
{
	if (!(SOUND->isPlaySound("dragonatk")))
	{
		SOUND->play("dragonatk", 0.5);
	}
}

void green_dragon::addMonster(float x, float y)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("드래곤");
	newMonster.x = x;
	newMonster.y = y;
	newMonster.posx = x / 48;
	newMonster.posy = y / 48;
	newMonster.rc = RectMake(newMonster.x, newMonster.y, newMonster.img->getFrameWidth(), newMonster.img->getFrameHeight());
	newMonster.maxhp = 8;
	newMonster.hp = 8;
	newMonster.atk = 4;
	newMonster.leftani = ANIMATION->addNoneKeyAnimation("드래곤", 0, 3, 4, false, true);
	newMonster.rightani = ANIMATION->addNoneKeyAnimation("드래곤", 4, 7, 4, false, true);
	newMonster.shadowani = ANIMATION->addNoneKeyAnimation("드래곤", 8, 11, 4, false, true);
	newMonster.shadowani = ANIMATION->addNoneKeyAnimation("드래곤", 12, 15, 4, false, true);
	newMonster._atkup = IMAGE->findImage("상하공격");
	newMonster._atkleft = IMAGE->findImage("좌우공격");
	newMonster.A_atkdown = ANIMATION->addNoneKeyAnimation("상하공격", 0, 4, 5, false, true);
	newMonster.A_atkup = ANIMATION->addNoneKeyAnimation("상하공격", 9, 5, 5, false, true);
	newMonster.A_atkright = ANIMATION->addNoneKeyAnimation("좌우공격", 0, 4, 5, false, true);
	newMonster.A_atkleft = ANIMATION->addNoneKeyAnimation("좌우공격", 9, 5, 5, false, true);
	newMonster.m_emptyheart = IMAGE->findImage("몬스터빈하트");
	newMonster.m_heart = IMAGE->findImage("몬스터하트");
	newMonster.m_halfheart = IMAGE->findImage("몬스터절반하트");
	newMonster.canBreakWall = false;
	newMonster.isDetecting = false;
	newMonster.isDead = false;
	newMonster.isHit = false;
	newMonster.isCurrentRight = false;
	newMonster.isMove = false;
	newMonster.AniLeft = true;
	newMonster.canleft = false;
	newMonster.canright = false;
	newMonster.canup = false;
	newMonster.candown = false;
	newMonster.digup = false;
	newMonster.digleft = false;
	newMonster.digright = false;
	newMonster.digdown = false;
	newMonster.limit = TILE_SIZE_Y;
	newMonster.speed = 48 * 2;
	newMonster.movecount = 0;
	newMonster.isOnceMove = false;
	newMonster.monsterState = MONSTERSTATE::STOP;
	newMonster.monsterMoveState = MONSTERMOVESTATE::LEFT;
	_vMonster.push_back(newMonster);
}

void green_dragon::stateCheck()
{
}

void green_dragon::moveMonster(rhythmUI* _rtm, wallManager* _wm, realwallManager* _rwm)
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{

		if (_rtm->checkstep() && _viMonster->rtmcount == false)
		{
			_viMonster->movecount += 1;
			_viMonster->rtmcount = true;
		}
		if (!(_rtm->checkstep()))
		{
			_viMonster->rtmcount = false;
		}
		if (_viMonster->movecount >= 2)
		{
			int x = PLAYER->getPlayerAddress().posx;
			int y = PLAYER->getPlayerAddress().posy;
			if (abs(_viMonster->posx - x) < 5 && abs(_viMonster->posy - y) < 5)
			{
				float deltaTime = TIME->getElapsedTime();
				float delta = 2;//_viMonster->speed * deltaTime;
				setbrokerdirection();
				switch (_viMonster->monsterMoveState)
				{
				case MONSTERMOVESTATE::LEFT:
					if (_viMonster->digleft)
					{
						digsound();
						_viMonster->movecount = 0;
						_viMonster->digleft = false;
						_wm->setDungeon(_viMonster->posx - 1, _viMonster->posy, 1);
						_rwm->getSoftWall()->eraseWall(_viMonster->posx - 1, _viMonster->posy);
					}
					else
					{
						if (_viMonster->atkleft)
						{
							atksound();
							_viMonster->movecount = 0;
							if (_viMonster->isGraceperiod == false) attack();
							_viMonster->isGraceperiod = true;
						}
						else
						{
							movesound();
							_viMonster->movecount = 0;
							_viMonster->posx -= 1;
							_viMonster->x = _viMonster->posx * 48;
							_viMonster->y = _viMonster->posy * 48;
						}
					}
					break;
				case MONSTERMOVESTATE::RIGHT:
					if (_viMonster->digright)
					{
						digsound();
						_viMonster->movecount = 0;
						_viMonster->digright = false;
						_wm->setDungeon(_viMonster->posx + 1, _viMonster->posy, 1);
						_rwm->getSoftWall()->eraseWall(_viMonster->posx + 1, _viMonster->posy);
					}
					else
					{
						if (_viMonster->atkright)
						{
							atksound();
							_viMonster->movecount = 0;
							if (_viMonster->isGraceperiod == false) attack();
							_viMonster->isGraceperiod = true;
						}
						else
						{
							movesound();
							_viMonster->movecount = 0;
							_viMonster->posx += 1;
							_viMonster->x = _viMonster->posx * 48;
							_viMonster->y = _viMonster->posy * 48;
						}
					}
					break;
				case MONSTERMOVESTATE::UP:
					if (_viMonster->digup)
					{
						digsound();
						_viMonster->movecount = 0;
						_viMonster->digup = false;
						_wm->setDungeon(_viMonster->posx, _viMonster->posy - 1, 1);
						_rwm->getSoftWall()->eraseWall(_viMonster->posx, _viMonster->posy - 1);
					}
					else
					{
						if (_viMonster->atkup)
						{
							atksound();
							_viMonster->movecount = 0;
							if (_viMonster->isGraceperiod == false) attack();
							_viMonster->isGraceperiod = true;
						}
						else
						{
							movesound();
							_viMonster->movecount = 0;
							_viMonster->posy -= 1;
							_viMonster->x = _viMonster->posx * 48;
							_viMonster->y = _viMonster->posy * 48;
						}
					}
					break;
				case MONSTERMOVESTATE::DOWN:
					if (_viMonster->digdown)
					{
						digsound();
						_viMonster->movecount = 0;
						_viMonster->digdown = false;
						_wm->setDungeon(_viMonster->posx, _viMonster->posy + 1, 1);
						_rwm->getSoftWall()->eraseWall(_viMonster->posx, _viMonster->posy + 1);
					}
					else
					{
						if (_viMonster->atkdown)
						{
							atksound();
							_viMonster->movecount = 0;
							if (_viMonster->isGraceperiod == false) attack();
							_viMonster->isGraceperiod = true;
						}
						else
						{
							movesound();
							_viMonster->movecount = 0;
							_viMonster->posy += 1;
							_viMonster->x = _viMonster->posx * 48;
							_viMonster->y = _viMonster->posy * 48;
						}
					}
					break;
				case MONSTERMOVESTATE::NONE:
					_viMonster->movecount = 0;
					_viMonster->posy += 0;
					_viMonster->posx += 0;
					_viMonster->x = _viMonster->posx * 48;
					_viMonster->y = _viMonster->posy * 48;
					break;
				}
			}

		}
	}
}

void green_dragon::updateRect(vector<tagMonster>::iterator iter)
{
	iter->rc = RectMake(iter->x, iter->y, iter->img->getFrameWidth(), iter->img->getFrameHeight());

}

king_konga::king_konga()
{
	IMAGE->addFrameImage("킹콩가", "images/monster/kong.bmp", 48 * 4 * 1.5, 48 * 2, 4, 1, true);
	
}

king_konga::~king_konga()
{
}

HRESULT king_konga::init()
{
	return S_OK;
}

void king_konga::release()
{
}

void king_konga::update(rhythmUI* _rtm)
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end();)
	{
		deathcheck();
		if (_viMonster->monsterState == MONSTERSTATE::DEAD)
		{
			if (!(SOUND->isPlaySound("kongdeath")))
			{
				SOUND->play("kongdeath");
			}
			_viMonster = _vMonster.erase(_viMonster);
		}
		else
		{
			++_viMonster;
		}
	}
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		checkInvincibility();
		if (_viMonster->monsterState == MONSTERSTATE::HIT)
		{
			teleport();
		}
	}
	moveMonster(_rtm, _boss, _rwm);
}

void king_konga::render()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		if (_viMonster->hp != _viMonster->maxhp)
			showhp();
		switch (_viMonster->monsterState)
		{
		case MONSTERSTATE::ATTACK:
			
			if (_viMonster->atkdown == true)
			{
				atksound();
				ZORDER->ZorderAniRender(_viMonster->_atkup, 6, 0, _viMonster->x, _viMonster->y + 24, _viMonster->A_atkdown);
			}
			if (_viMonster->atkup == true)
			{
				atksound();
				ZORDER->ZorderAniRender(_viMonster->_atkup, 6, 0, _viMonster->x, _viMonster->y - 24, _viMonster->A_atkup);
			}
			if (_viMonster->atkright == true)
			{
				atksound();
				ZORDER->ZorderAniRender(_viMonster->_atkleft, 6, 0, _viMonster->x + 24, _viMonster->y, _viMonster->A_atkright);
			}
			if (_viMonster->atkleft == true)
			{
				atksound();
				ZORDER->ZorderAniRender(_viMonster->_atkleft, 6, 0, _viMonster->x - 24, _viMonster->y, _viMonster->A_atkleft);
			}
		case MONSTERSTATE::HIT:
		case MONSTERSTATE::MOVE:
		case MONSTERSTATE::DIGGING:
		case MONSTERSTATE::STOP:
			if (_isDebug) {
				ZORDER->ZorderRectangle(_viMonster->rc, 3);
			}
			if (_viMonster->monsterMoveState == MONSTERMOVESTATE::LEFT || _viMonster->monsterMoveState == MONSTERMOVESTATE::DOWN)
			{
				ZORDER->ZorderAniRender(_viMonster->img, 4, _viMonster->rc.bottom, _viMonster->x, _viMonster->y - 48, _viMonster->leftani);
			}
			else
			{
				ZORDER->ZorderAniRender(_viMonster->img, 4, _viMonster->rc.bottom, _viMonster->x, _viMonster->y - 48, _viMonster->rightani);
			}

			break;
		case MONSTERSTATE::DEAD:
			break;
		}
	}
}

void king_konga::atksound()
{
	if (!(SOUND->isPlaySound("kongAtk")))
	{
		SOUND->play("kongAtk");
	}
}

void king_konga::teleport()
{
	if (_viMonster->monsterState == MONSTERSTATE::HIT)
	{
		int tempX = RND->getFromInTo(1, 18);
		int tempY = RND->getFromInTo(1, 18);
		_viMonster->posx = tempX;
		_viMonster->posy = tempY;
		_viMonster->x = _viMonster->posx * 48;
		_viMonster->y = _viMonster->posy * 48;
		_viMonster->monsterState = MONSTERSTATE::MOVE;
	}
}

void king_konga::addMonster(float x, float y)
{
	tagMonster newMonster;
	newMonster.img = IMAGE->findImage("킹콩가");
	newMonster.x = x;
	newMonster.y = y;
	newMonster.posx = x / 48;
	newMonster.posy = y / 48;
	newMonster.rc = RectMake(newMonster.x, newMonster.y, newMonster.img->getFrameWidth(), newMonster.img->getFrameHeight());
	newMonster.maxhp = 4;
	newMonster.hp = 4;
	newMonster.atk = 3;
	newMonster.leftani = ANIMATION->addNoneKeyAnimation("킹콩가", 0, 1, 4, false, true);
	newMonster.rightani = ANIMATION->addNoneKeyAnimation("킹콩가", 2, 3, 4, false, true);
	newMonster._atkup = IMAGE->findImage("상하공격");
	newMonster._atkleft = IMAGE->findImage("좌우공격");
	newMonster.A_atkdown = ANIMATION->addNoneKeyAnimation("상하공격", 0, 4, 5, false, true);
	newMonster.A_atkup = ANIMATION->addNoneKeyAnimation("상하공격", 9, 5, 5, false, true);
	newMonster.A_atkright = ANIMATION->addNoneKeyAnimation("좌우공격", 0, 4, 5, false, true);
	newMonster.A_atkleft = ANIMATION->addNoneKeyAnimation("좌우공격", 9, 5, 5, false, true);
	newMonster.m_emptyheart = IMAGE->findImage("몬스터빈하트");
	newMonster.m_heart = IMAGE->findImage("몬스터하트");
	newMonster.m_halfheart = IMAGE->findImage("몬스터절반하트");
	newMonster.canBreakWall = false;
	newMonster.isDetecting = false;
	newMonster.isDead = false;
	newMonster.isHit = false;
	newMonster.isCurrentRight = false;
	newMonster.isMove = false;
	newMonster.AniLeft = true;
	newMonster.canleft = false;
	newMonster.canright = false;
	newMonster.canup = false;
	newMonster.candown = false;
	newMonster.digup = false;
	newMonster.digleft = false;
	newMonster.digright = false;
	newMonster.digdown = false;
	newMonster.limit = TILE_SIZE_Y;
	newMonster.speed = 48 * 2;
	newMonster.movecount = 0;
	newMonster.isOnceMove = false;
	newMonster.monsterState = MONSTERSTATE::STOP;
	newMonster.monsterMoveState = MONSTERMOVESTATE::LEFT;
	_vMonster.push_back(newMonster);
}

void king_konga::stateCheck()
{
}

void king_konga::moveMonster(rhythmUI* _rtm, bossMap* _boss, realwallManager* _rwm)
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{

		if (_rtm->checkstep() && _viMonster->rtmcount == false)
		{
			_viMonster->movecount += 1;
			_viMonster->rtmcount = true;
		}
		if (!(_rtm->checkstep()))
		{
			_viMonster->rtmcount = false;
		}
		if (_viMonster->movecount >= 2)
		{
			int x = PLAYER->getPlayerAddress().posx;
			int y = PLAYER->getPlayerAddress().posy;

			float deltaTime = TIME->getElapsedTime();
			float delta = 2;//_viMonster->speed * deltaTime;
			setbrokerdirection();
			switch (_viMonster->monsterMoveState)
			{
			case MONSTERMOVESTATE::LEFT:
				if (_viMonster->digleft)
				{
					_viMonster->movecount = 0;
					_viMonster->digleft = false;
					_boss->setDungeon(_viMonster->posx - 1, _viMonster->posy, 1);
					_rwm->getSoftWall()->eraseWall(_viMonster->posx - 1, _viMonster->posy);
				}
				else
				{
					if (_viMonster->atkleft)
					{
						_viMonster->movecount = 0;
						if (_viMonster->isGraceperiod == false) attack();
						_viMonster->isGraceperiod = true;
					}
					else
					{
						_viMonster->movecount = 0;
						_viMonster->posx -= 1;
						_viMonster->x = _viMonster->posx * 48;
						_viMonster->y = _viMonster->posy * 48;
					}
				}
				break;
			case MONSTERMOVESTATE::RIGHT:
				if (_viMonster->digright)
				{
					_viMonster->movecount = 0;
					_viMonster->digright = false;
					_boss->setDungeon(_viMonster->posx + 1, _viMonster->posy, 1);
					_rwm->getSoftWall()->eraseWall(_viMonster->posx + 1, _viMonster->posy);
				}
				else
				{
					if (_viMonster->atkright)
					{
						_viMonster->movecount = 0;
						if (_viMonster->isGraceperiod == false) attack();
						_viMonster->isGraceperiod = true;
					}
					else
					{
						_viMonster->movecount = 0;
						_viMonster->posx += 1;
						_viMonster->x = _viMonster->posx * 48;
						_viMonster->y = _viMonster->posy * 48;
					}
				}
				break;
			case MONSTERMOVESTATE::UP:
				if (_viMonster->digup)
				{
					_viMonster->movecount = 0;
					_viMonster->digup = false;
					_boss->setDungeon(_viMonster->posx, _viMonster->posy - 1, 1);
					_rwm->getSoftWall()->eraseWall(_viMonster->posx, _viMonster->posy - 1);
				}
				else
				{
					if (_viMonster->atkup)
					{
						_viMonster->movecount = 0;
						if (_viMonster->isGraceperiod == false) attack();
						_viMonster->isGraceperiod = true;
					}
					else
					{
						_viMonster->movecount = 0;
						_viMonster->posy -= 1;
						_viMonster->x = _viMonster->posx * 48;
						_viMonster->y = _viMonster->posy * 48;
					}
				}
				break;
			case MONSTERMOVESTATE::DOWN:
				if (_viMonster->digdown)
				{
					_viMonster->movecount = 0;
					_viMonster->digdown = false;
					_boss->setDungeon(_viMonster->posx, _viMonster->posy + 1, 1);
					_rwm->getSoftWall()->eraseWall(_viMonster->posx, _viMonster->posy + 1);
				}
				else
				{
					if (_viMonster->atkdown)
					{
						_viMonster->movecount = 0;
						if (_viMonster->isGraceperiod == false) attack();
						_viMonster->isGraceperiod = true;
					}
					else
					{
						_viMonster->movecount = 0;
						_viMonster->posy += 1;
						_viMonster->x = _viMonster->posx * 48;
						_viMonster->y = _viMonster->posy * 48;
					}
				}
				break;
			case MONSTERMOVESTATE::NONE:
				_viMonster->movecount = 0;
				_viMonster->posy += 0;
				_viMonster->posx += 0;
				_viMonster->x = _viMonster->posx * 48;
				_viMonster->y = _viMonster->posy * 48;
				break;
			}
		}
	}
}

void king_konga::updateRect(vector<tagMonster>::iterator iter)
{
}
