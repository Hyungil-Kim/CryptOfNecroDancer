#include "framework.h"
#include "makeMonster.h"
/*
================================================ =
Find monster class ctrl + F4("name!")
================================================ =
monstername					imagename
1.	green_slime				그린슬라임
2.	blue_slime				블루슬라임
3.	orange_slime			오랜지슬라임
4	
5.	

*/
//////////////////////////////////////////////////////////////
//////////////////////green_slime!	그린슬라임!//////////////////////////
//////////////////////////////////////////////////////////////
green_slime::green_slime()
{
	IMAGE->addFrameImage("그린슬라임", "images/monster/slime_green.bmp", 48*4, 48*2, 4, 2, true);
	
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
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		RectMake(_viMonster->x, _viMonster->y, _viMonster->img->getFrameWidth(), _viMonster->img->getFrameHeight());
	}
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
	newMonster.img = IMAGE->findImage("그린슬라임");
	newMonster.x = x;
	newMonster.y = y;
	newMonster.posx = x/48;
	newMonster.posy = y/48;
	newMonster.rc = RectMake(x, y, newMonster.img->getFrameWidth(), newMonster.img->getFrameHeight());
	newMonster.hp = 4;
	newMonster.atk = 2;
	newMonster.ani = ANIMATION->addNoneKeyAnimation("그린슬라임",0,3, 5, false,true);
	newMonster.shadowani = ANIMATION->addNoneKeyAnimation("그린슬라임",4,7,5,false,true);
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
void green_slime::updateRect(vector<tagMonster>::iterator iter)
{
	iter->rc = RectMake(iter->x, iter->y, iter->img->getFrameWidth(), iter->img->getFrameHeight());
}
//////////////////////////////////////////////////////////////
//////////////////////blue!	블루슬라임!//////////////////////////
//////////////////////////////////////////////////////////////
blue_slime::blue_slime()
{
	IMAGE->addFrameImage("블루슬라임", "images/monster/slime_blue.bmp", 48*8, 48*2, 8, 2, true);

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
	newMonster.img = IMAGE->findImage("블루슬라임");
	newMonster.x = x;
	newMonster.y = y;
	newMonster.posx = x / 48;
	newMonster.posy = y / 48;
	newMonster.rc = RectMake(x, y, newMonster.img->getFrameWidth(), newMonster.img->getFrameHeight());
	newMonster.hp = 4;
	newMonster.atk = 2;
	newMonster.ani = ANIMATION->addNoneKeyAnimation("블루슬라임", 0, 7, 4, false, true);
	newMonster.shadowani = ANIMATION->addNoneKeyAnimation("블루슬라임", 8,15, 5, false, true);
	newMonster.canBreakWall = false;
	newMonster.isDetecting = false;
	newMonster.isDead = false;
	newMonster.isHit = false;
	newMonster.isCurrentRight = false;
	newMonster.isMove = false;
	newMonster.AttackOn = false;
	newMonster.candown = false;
	newMonster.canleft = false;
	newMonster.canright = false;
	newMonster.canup = false;
	newMonster.speed = 4;
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
		isCanMove();
		if (_viMonster->canup == true)
		{
			if (_viMonster->ani->findNowPlayIndex() == 7 && _viMonster->isOnceMove == false && _viMonster->isMove == false)
			{
				_viMonster->y -= 4;
				_viMonster->AttackOn = true;
				_viMonster->limit -= _viMonster->speed;
				if (_viMonster->limit - _viMonster->speed <= -2)
				{
					_viMonster->limit = TILE_SIZE_Y;
					_viMonster->isMove = true;
					_viMonster->AttackOn = false;
					_viMonster->isOnceMove = true;
					_viMonster->monsterMoveState = MONSTERMOVESTATE::DOWN;
					updateRect(_viMonster);
					break;
				}
			}
		}
		if (_viMonster->ani->findNowPlayIndex() == 7 && _viMonster->isOnceMove == false && _viMonster->isMove == true)
		{
			_viMonster->y += _viMonster->speed;
			_viMonster->AttackOn = true;
			_viMonster->limit -= _viMonster->speed;
			if (_viMonster->limit - _viMonster->speed <= -2)
			{	
				_viMonster->limit = TILE_SIZE_Y;
				_viMonster->isMove = false;
				_viMonster->AttackOn = false;
				_viMonster->isOnceMove = true;
				updateRect(_viMonster);
				_viMonster->monsterMoveState = MONSTERMOVESTATE::UP;
			}
		}
		if (_viMonster->ani->findNowPlayIndex() == 0)
		{
			_viMonster->isOnceMove = false;
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
	moveMonster();
}

void orange_slime::render()
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
	newMonster.hp = 4;
	newMonster.atk = 2;
	newMonster.ani = ANIMATION->addNoneKeyAnimation("주황슬라임", 0, 3, 4, false, true);
	newMonster.leftani = ANIMATION->addNoneKeyAnimation("주황슬라임", 4, 7, 4, false, true);
	newMonster.shadowani = ANIMATION->addNoneKeyAnimation("주황슬라임", 15, 12, 4, false, true);
	newMonster.shadowani = ANIMATION->addNoneKeyAnimation("주황슬라임", 11, 8, 4, false, true);
	newMonster.canBreakWall = false;
	newMonster.isDetecting = false;
	newMonster.isDead = false;
	newMonster.isHit = false;
	newMonster.isCurrentRight = false;
	newMonster.isMove = false;
	newMonster.AttackOn = false;
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
		isCanMove();
		if (_viMonster->canup == true)
		{
			if (_viMonster->ani->findNowPlayIndex() == 3 && _viMonster->isOnceMove == false && _viMonster->isMove == false && _viMonster->AniLeft == true)
			{
				_viMonster->y -= _viMonster->speed;
				_viMonster->AttackOn = true;
				_viMonster->limit -= _viMonster->speed;
				if (_viMonster->limit - _viMonster->speed <= -2)
				{
					_viMonster->AttackOn = false;
					_viMonster->limit = TILE_SIZE_Y;
					_viMonster->isMove = true;
					_viMonster->isOnceMove = true;
					updateRect(_viMonster);
					_viMonster->monsterMoveState = MONSTERMOVESTATE::LEFT;
				}
			}
		}
		isCanMove();
		if (_viMonster->canleft == true)
		{
			if (_viMonster->ani->findNowPlayIndex() == 3 && _viMonster->isOnceMove == false && _viMonster->isMove == true && _viMonster->AniLeft == true)
			{
				_viMonster->AttackOn = true;
				_viMonster->x -= _viMonster->speed;
				_viMonster->limit -= _viMonster->speed;
				if (_viMonster->limit - _viMonster->speed <= -2)
				{
					_viMonster->limit = TILE_SIZE_Y;
					_viMonster->isMove = false;
					_viMonster->AttackOn = false;
					_viMonster->isOnceMove = true;
					_viMonster->AniLeft = false;
					updateRect(_viMonster);
					_viMonster->monsterMoveState = MONSTERMOVESTATE::DOWN;
				}
			}
		}
		isCanMove();
		if (_viMonster->candown == true)
		{
			if (_viMonster->ani->findNowPlayIndex() == 3 && _viMonster->isOnceMove == false && _viMonster->isMove == false && _viMonster->AniLeft == false)
			{
				_viMonster->y += _viMonster->speed;
				_viMonster->AttackOn = true;
				_viMonster->limit -= _viMonster->speed;
				if (_viMonster->limit - _viMonster->speed <= -2)
				{
					_viMonster->limit = TILE_SIZE_Y;
					_viMonster->AttackOn = false;
					_viMonster->isMove = true;
					_viMonster->isOnceMove = true;
					updateRect(_viMonster);
					_viMonster->monsterMoveState = MONSTERMOVESTATE::RIGHT;
				}
			}
		}
		isCanMove();
		if (_viMonster->candown == true)
		{
			if (_viMonster->ani->findNowPlayIndex() == 3 && _viMonster->isOnceMove == false && _viMonster->isMove == true && _viMonster->AniLeft == false)
			{
				_viMonster->x += _viMonster->speed;
				_viMonster->AttackOn = true;
				_viMonster->limit -= _viMonster->speed;
				if (_viMonster->limit - _viMonster->speed <= -2)
				{
					_viMonster->limit = TILE_SIZE_Y;
					_viMonster->isMove = false;
					_viMonster->AttackOn = false;
					_viMonster->isOnceMove = true;
					_viMonster->AniLeft = true;
					updateRect(_viMonster);
					_viMonster->monsterMoveState = MONSTERMOVESTATE::UP;
				}
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

void white_skeleton::update(Player* cp)
{
	moveMonster();
}

void white_skeleton::render()
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
	newMonster.hp = 4;
	newMonster.atk = 2;
	newMonster.ani = ANIMATION->addNoneKeyAnimation("해골", 0, 15, 4, false, true);
	newMonster.leftani = ANIMATION->addNoneKeyAnimation("해골",32 , 47, 4, false, true);
	newMonster.shadowani = ANIMATION->addNoneKeyAnimation("해골", 16, 31, 4, false, true);
	newMonster.shadowani = ANIMATION->addNoneKeyAnimation("해골", 48, 63, 4, false, true);
	newMonster.canBreakWall = false;
	newMonster.isDetecting = false;
	newMonster.isDead = false;
	newMonster.isHit = false;
	newMonster.isCurrentRight = false;
	newMonster.isMove = false;
	newMonster.AttackOn = false;
	newMonster.AniLeft = true;
	newMonster.limit = TILE_SIZE_Y;
	newMonster.speed = 4;
	newMonster.isOnceMove = false;
	newMonster.monsterState = MONSTERSTATE::STOP;
	newMonster.monsterMoveState = MONSTERMOVESTATE::UP;
	_vMonster.push_back(newMonster);
}

void white_skeleton::stateCheck()
{
}

void white_skeleton::moveMonster()
{
}

void white_skeleton::updateRect(vector<tagMonster>::iterator iter)
{
}
