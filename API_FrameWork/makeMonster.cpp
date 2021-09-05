#include "framework.h"
#include "makeMonster.h"
#include "rhythmUI.h"
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
			if(_viMonster->atkup == true)
			{
				ZORDER->ZorderAniRender(_viMonster->_atkup, 6, 0, _viMonster->x, _viMonster->y - 24, _viMonster->A_atkup);
			}
			if(_viMonster->atkright == true)
			{
				ZORDER->ZorderAniRender(_viMonster->_atkleft, 6, 0, _viMonster->x - 24, _viMonster->y, _viMonster->A_atkright);
			}
			if(_viMonster->atkleft == true)
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
			else if(_viMonster->atkup == true)
			{
				_viMonster->monsterState = MONSTERSTATE::ATTACK;
				_viMonster->atkdown = false;
				_viMonster->atkright = false;
				_viMonster->atkleft = false;
				if(_viMonster->isGraceperiod == false) attack();
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
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
	moveMonster(_rtm);
		
	}
}

void white_skeleton::render()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		if(_viMonster->hp != _viMonster->maxhp)
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
	newMonster.ani = ANIMATION->addNoneKeyAnimation("해골", 0, 15, 4, false, true);
	newMonster.leftani = ANIMATION->addNoneKeyAnimation("해골", 32, 47, 4, false, true);
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
	newMonster.limit = TILE_SIZE_Y;
	newMonster.speed = 48*2;
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
	setdirection();
			//if (abs(_viMonster->posx - PLAYER->getPlayerAddress().posx) < 4 || abs(_viMonster->posy - PLAYER->getPlayerAddress().posy) < 4)
			{
				float deltaTime = TIME->getElapsedTime();
				float delta = 48 / 16;//_viMonster->speed * deltaTime;
				switch (_viMonster->monsterMoveState)
				{
				case MONSTERMOVESTATE::LEFT:
					_viMonster->x -= delta;
					_viMonster->movecount = 0;
					_viMonster->posx = _viMonster->x / 48;
					break;
				case MONSTERMOVESTATE::RIGHT:
					_viMonster->x += delta;
					_viMonster->movecount = 0;
					_viMonster->posx = _viMonster->x / 48;
					_viMonster->posy = _viMonster->y / 48;
					break;
				case MONSTERMOVESTATE::UP:
					_viMonster->y -= delta;
					_viMonster->movecount = 0;
					_viMonster->posx = _viMonster->x / 48;
					_viMonster->posy = _viMonster->y / 48;
					break;
				case MONSTERMOVESTATE::DOWN:
					_viMonster->y += delta;
					_viMonster->movecount = 0;
					_viMonster->posx = _viMonster->x / 48;
					_viMonster->posy = _viMonster->y / 48;
					break;
				default:
					break;
				}
			}
}

void white_skeleton::updateRect(vector<tagMonster>::iterator iter)
{
	iter->rc = RectMake(iter->x, iter->y, iter->img->getFrameWidth(), iter->img->getFrameHeight());
}
