#include "framework.h"
#include "monster.h"
#include"wallManager.h"
#include"monsterManager.h"
#include "bossMap.h"
#include"rhythmUI.h"
monster::monster()
{
	IMAGE->addFrameImage("좌우공격", "images/monster/monatk1.bmp", 135 * 2, 46 * 2, 5, 2, true);
	IMAGE->addFrameImage("상하공격", "images/monster/monatk2.bmp", 115 * 2, 54 * 2, 5, 2, true);
	ANIMATION->addNoneKeyAnimation("상하공격", 0, 4, 3, false, false);
	ANIMATION->addNoneKeyAnimation("상하공격", 9, 5, 3, false, false);
	ANIMATION->addNoneKeyAnimation("좌우공격", 0, 4, 3, false, false);
	ANIMATION->addNoneKeyAnimation("좌우공격", 5, 9, 3, false, false);
	IMAGE->addImage("몬스터빈하트", "images/UI/m_heart_empty.bmp", 24, 22, true);
	IMAGE->addImage("몬스터하트", "images/UI/m_heart.bmp", 24, 22, true);
	IMAGE->addImage("몬스터절반하트", "images/UI/m_heart_half.bmp", 24, 22, true);
}

monster::~monster()
{
}

HRESULT monster::init()
{
	
	return S_OK;
}

void monster::release()
{
}

void monster::update(Player* cp)
{
	
}

void monster::render()
{
}

void monster::addMonster(float x, float y)
{
}

void monster::move()
{
}

void monster::stateCheck()
{
}

void monster::moveMonster()
{
}

void monster::isCanMove()
{
	int tempX = _viMonster->posx;
	int tempY = _viMonster->posy;
	switch (_viMonster->monsterMoveState)
	{
	case MONSTERMOVESTATE::LEFT:
		tempX -= 1;
		break;
	case MONSTERMOVESTATE::UP:
		tempY -= 1;
		break;
	case MONSTERMOVESTATE::RIGHT:
		tempX += 1;
		break;
	case MONSTERMOVESTATE::DOWN:
		tempY += 1;
		break;
	default:
		break;
	}
	
	if (findPlayer(tempX, tempY) == false)
	 {
		if (monTomon(tempX,tempY) == false)
		{
			if (_wm->getDungeon(tempX, tempY) != 0)
			{
				_viMonster->posx = tempX;
				_viMonster->posy = tempY;
				switch (_viMonster->monsterMoveState)
				{
				case MONSTERMOVESTATE::LEFT:
					_viMonster->canleft = true;
					break;
				case MONSTERMOVESTATE::UP:
					_viMonster->canup = true;
					break;
				case MONSTERMOVESTATE::RIGHT:
					_viMonster->canright = true;
					break;
				case MONSTERMOVESTATE::DOWN:
					_viMonster->candown = true;
					break;
				default:
					break;
				}
			}
		}
	}
	else if (findPlayer(tempX, tempY) == true)
	{
		_viMonster->atkdown = true;
		_viMonster->atkup = true;
		_viMonster->atkright = true;
		_viMonster->atkleft = true;
	}

}

bool monster::findPlayer(tagPlayer& player)
{
	int playerX = player.posx;
	int playerY = player.posy;

	if (playerX + 1 == _viMonster->posx && playerY == _viMonster->posy)
		return true;
	if (playerX - 1 == _viMonster->posx && playerY == _viMonster->posy)
		return true;
	if (playerX == _viMonster->posx && playerY + 1== _viMonster->posy)
		return true;
	if (playerX == _viMonster->posx && playerY - 1== _viMonster->posy)
		return true;
	return false;
}
bool monster::findMonster(monster* monster)
{
	vector<tagMonster>& vMonster = monster->getVMonster();
	vector<tagMonster>::iterator iter = vMonster.begin();
	for (iter; iter != vMonster.end(); ++iter)
	{
		for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
		{
			if (iter->posx + 1 == _viMonster->posx && iter->posy == _viMonster->posy)
				return true;
			if (iter->posx - 1 == _viMonster->posx && iter->posy == _viMonster->posy)
				return true;
			if (iter->posx == _viMonster->posx && iter->posy + 1 == _viMonster->posy)
				return true;
			if (iter->posx == _viMonster->posx && iter->posy - 1 == _viMonster->posy)
				return true;
		}
	}
	return false;
}
bool monster::monTomon(tagMonster& monster)
{
	return false;
}
bool monster::findPlayer(int x, int y)
{
	if (PLAYER->getPlayerAddress().posx ==x && PLAYER->getPlayerAddress().posy == y)
		return true;
	else
		return false;
}
bool monster::findMonster(monster* monster,int x, int y)
{
	vector<tagMonster>& vMonster = monster->getVMonster();
	vector<tagMonster>::iterator iter = vMonster.begin();
	for (iter; iter != vMonster.end(); ++iter)
	{
		if (iter->posx == x && iter->posy == y)
		{
			return true;
		}
	}
	return false;
}
bool monster::monTomon(int x, int y)
{
	if (findMonster(_mm->getGreenSlime(), x, y) ||
		findMonster(_mm->getBlueSlime(), x, y) ||
		findMonster(_mm->getOrangeSlime(), x, y) ||
		findMonster(_mm->getWhiteskeleton(),x,y) ||
		findMonster(_mm->getGreenDragon(),x,y) ||
		findMonster(_mm->getKingKong(), x, y)
		)
	{
		return true;
	}
	return false;
}
void monster::attack()
{
	if (!(SOUND->isPlaySound("playerhurt")))
	{
		SOUND->play("playerhurt", 0.5);
	}
	PLAYER->getPlayerAddress().hp -= _viMonster->atk;
}
void monster::getDamage()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		_viMonster->hp -= PLAYER->getPlayerAddress().atk;
	}
}
void monster::checkInvincibility()
{
	//무적확인함수
	if (_viMonster->isGraceperiod) {
		_viMonster->gracePeriodCount++;
		if (_viMonster->gracePeriodCount > INVINTIME) {
			_viMonster->gracePeriodCount = 0;
			_viMonster->isGraceperiod = false;
		}
	}
}
void monster::deathcheck()
{
	if (_viMonster->monsterState != MONSTERSTATE::DEAD && _viMonster->hp <= 0) {
		_viMonster->hp = 0;
		_viMonster->monsterState = MONSTERSTATE::DEAD;
	}

}

void monster::checkstate()
{
	int tempX = _viMonster->posx;
	int tempY = _viMonster->posy;
	
		if (!(_wm->getDungeon(tempX + 1, tempY) == 0 || monTomon(tempX + 1, tempY)))
		{
			_viMonster->canright = true;;		
		}
		if (!(_wm->getDungeon(tempX-1, tempY) == 0 || monTomon(tempX -1, tempY)))
		{
			_viMonster->canleft = true;;
		}
		if (!(_wm->getDungeon(tempX, tempY - 1) == 0 || monTomon(tempX, tempY - 1)))
		{
			_viMonster->canup = true;;
		}
		if (!(_wm->getDungeon(tempX, tempY + 1) == 0 || monTomon(tempX, tempY + 1)))
		{
			_viMonster->candown = true;;
		}

		if (!(_boss->getDungeon(tempX + 1, tempY) == 0 || monTomon(tempX + 1, tempY)))
		{
			_viMonster->canright = true;;
		}
		if (!(_boss->getDungeon(tempX - 1, tempY) == 0 || monTomon(tempX - 1, tempY)))
		{
			_viMonster->canleft = true;;
		}
		if (!(_boss->getDungeon(tempX, tempY - 1) == 0 || monTomon(tempX, tempY - 1)))
		{
			_viMonster->canup = true;;
		}
		if (!(_boss->getDungeon(tempX, tempY + 1) == 0 || monTomon(tempX, tempY + 1)))
		{
			_viMonster->candown = true;;
		}



			
}

void monster::checkstatebroker()
{
	int tempX = _viMonster->posx;
	int tempY = _viMonster->posy;

	if (!(monTomon(tempX + 1, tempY)))
	{
		_viMonster->canright = true;;
	}
	if (!(monTomon(tempX - 1, tempY)))
	{
		_viMonster->canleft = true;;
	}
	if (!(monTomon(tempX, tempY - 1)))
	{
		_viMonster->canup = true;;
	}
	if (!(monTomon(tempX, tempY + 1)))
	{
		_viMonster->candown = true;;
	}
	if (!(_wm->getDungeon(tempX + 1, tempY))&&!(_boss->getDungeon(tempX + 1, tempY)))
	{
		_viMonster->digright = true;;
	}
	if (!(_wm->getDungeon(tempX - 1, tempY)) && !(_boss->getDungeon(tempX - 1, tempY)))
	{
		_viMonster->digleft = true;;
	}
	if (!(_wm->getDungeon(tempX, tempY - 1)) && !(_boss->getDungeon(tempX, tempY -1)))
	{
		_viMonster->digup = true;;
	}
	if (!(_wm->getDungeon(tempX, tempY + 1)) && !(_boss->getDungeon(tempX, tempY+1)))
	{
		_viMonster->digdown = true;;
	}
}

void monster::showhp()
{
	for (int i = 0; i < _viMonster->maxhp / 2; i++)
	{
		int k;
		if (i / 5 < 1) k = 0;
		else  k = 1;
		{
			ZORDER->ZorderRender(_viMonster->m_emptyheart, 7, 5, _viMonster->x-12 + 24*i,_viMonster->y -12);
		}
	}
	for (int i = 0; i < _viMonster->hp / 2; i++)
	{

		int k;
		if (i / 5 < 1) k = 0;
		else  k = 1;
		{
			ZORDER->ZorderRender(_viMonster->m_heart, 8, 5, _viMonster->x - 12 + 24 * i, _viMonster->y - 12);
		}

		if (_viMonster->hp % 2 != 0)
		{
			int t = _viMonster->hp / 2;
			int k;
			if (i / 4 < 1) k = 0;
			else  k = 1;
			{
				ZORDER->ZorderRender(_viMonster->m_halfheart, 8, 0, _viMonster->x-12 + 24*i,_viMonster->y -12);
			}
		}
	}
}
void monster::hpinit()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		monstermaxhp = _viMonster->maxhp;
		monsterhp = _viMonster->hp;
	}
}
void monster::setdirection()
{
	// 0. 플레이어에시 4칸 범위 안에 들어온 몬스터가 움직이기 시작하게
	// 
	// 1. 몬스터 플레이어 몬스터 추적
	// 2. 바로 옆 타일에 플레이어가 있으면 공격

	int playerX = PLAYER->getPlayerAddress().posx;
	int playerY = PLAYER->getPlayerAddress().posy;

	int dirX = playerX - _viMonster->posx;
	int dirY = _viMonster->posy - playerY;


	MONSTERMOVESTATE lr = dirX > 0 ? MONSTERMOVESTATE::RIGHT : MONSTERMOVESTATE::LEFT;
	MONSTERMOVESTATE td = dirY > 0 ? MONSTERMOVESTATE::UP : MONSTERMOVESTATE::DOWN;
	_viMonster->monsterMoveState = abs(dirX) > abs(dirY) ? lr : td;

	if (findPlayer(PLAYER->getPlayerAddress()))
	{
		_viMonster->monsterState = MONSTERSTATE::ATTACK;

		_viMonster->atkleft = dirX == -1;
		_viMonster->atkright = dirX == 1;
		_viMonster->atkdown = dirY == -1;
		_viMonster->atkup = dirY == 1;
		return;
	}


	_viMonster->monsterState = MONSTERSTATE::MOVE;
	_viMonster->atkleft = false;
	_viMonster->atkright = false;
	_viMonster->atkdown = false;
	_viMonster->atkup = false;


	int tempX = _viMonster->posx;
	int tempY = _viMonster->posy;
	switch (_viMonster->monsterMoveState)
	{
	case MONSTERMOVESTATE::LEFT:
		tempX -= 1;
		break;
	case MONSTERMOVESTATE::UP:
		tempY -= 1;
		break;
	case MONSTERMOVESTATE::RIGHT:
		tempX += 1;
		break;
	case MONSTERMOVESTATE::DOWN:
		tempY += 1;
		break;
	default:
		break;
	}
	checkstate();
	switch (_viMonster->monsterMoveState)
	{
	case MONSTERMOVESTATE::LEFT:
		if (_viMonster->canleft == false)
		{
			if (dirY > 0)
			{
				if (_viMonster->canup)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::UP;
				}
				else if (_viMonster->canright)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::RIGHT;
				}
				else
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
				}
			}
			else if (dirY <= 0)
			{
				if (_viMonster->candown)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::DOWN;
				}
				else if (_viMonster->canright)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::RIGHT;
				}
				else
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
				}
			}
			else
			{
				_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
			}
		}
		else if (_viMonster->canleft)
		{
			_viMonster->monsterMoveState = MONSTERMOVESTATE::LEFT;
		}
		else if (_viMonster->canright)
		{
			_viMonster->monsterMoveState = MONSTERMOVESTATE::RIGHT;
		}
		else
		{
			_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
		}
		break;
	case MONSTERMOVESTATE::RIGHT:
		if (_viMonster->canright == false)
		{
			if (dirY > 0)
			{
				if (_viMonster->canup)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::UP;
				}
				else if (_viMonster->canleft)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::LEFT;
				}
				else
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
				}

			}
			else if(dirY <= 0)
			{
				if (_viMonster->candown)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::DOWN;
				}
				else if (_viMonster->canleft)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::LEFT;
				}
				else
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
				}
			}
			else
			{
				_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
			}

		}
		else if (_viMonster->canright)
		{
			_viMonster->monsterMoveState = MONSTERMOVESTATE::RIGHT;
		}
		else if (_viMonster->canleft)
		{
			_viMonster->monsterMoveState = MONSTERMOVESTATE::LEFT;
		}
		else
		{
			_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
		}
		break;
	case MONSTERMOVESTATE::DOWN:
		if (_viMonster->candown == false)
		{
			if (dirX > 0)
			{
				if (_viMonster->canright)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::RIGHT;
				}
				else if (_viMonster->canup)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::UP;
				}
				else
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
				}
			}
			else if (dirX <= 0)
			{
				if (_viMonster->canleft)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::LEFT;
				}
				else if (_viMonster->canup)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::UP;
				}
				else
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
				}
			}
			else
			{
				_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
			}

		}
		else if (_viMonster->candown)
		{
			_viMonster->monsterMoveState = MONSTERMOVESTATE::DOWN;
		}
		else if (_viMonster->canup)
		{
			_viMonster->monsterMoveState = MONSTERMOVESTATE::UP;
		}
		else
		{
			_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
		}
		break;
	case MONSTERMOVESTATE::UP:
		if (_viMonster->canup == false)
		{
			if (dirX > 0)
			{
				if (_viMonster->canright)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::RIGHT;
				}
				else if (_viMonster->candown)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::DOWN;
				}
				else
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
				}
			}
			else if (dirX <= 0)
			{
				if (_viMonster->canleft)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::LEFT;
				}
				else if (_viMonster->candown)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::DOWN;
				}
				else
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
				}
			}
			else
			{
				_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
			}

		}
		else if (_viMonster->canup)
		{
			_viMonster->monsterMoveState = MONSTERMOVESTATE::UP;
		}
		else if (_viMonster->candown)
		{
			_viMonster->monsterMoveState = MONSTERMOVESTATE::DOWN;
		}
		else
		{
			_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
		}
		break;
	}
	_viMonster->candown = false;
	_viMonster->canup = false;
	_viMonster->canright = false;
	_viMonster->canleft = false;
}

void monster::setbrokerdirection()
{
	int playerX = PLAYER->getPlayerAddress().posx;
	int playerY = PLAYER->getPlayerAddress().posy;

	int dirX = playerX - _viMonster->posx;
	int dirY = _viMonster->posy - playerY;


	MONSTERMOVESTATE lr = dirX > 0 ? MONSTERMOVESTATE::RIGHT : MONSTERMOVESTATE::LEFT;
	MONSTERMOVESTATE td = dirY > 0 ? MONSTERMOVESTATE::UP : MONSTERMOVESTATE::DOWN;
	_viMonster->monsterMoveState = abs(dirX) > abs(dirY) ? lr : td;

	if (findPlayer(PLAYER->getPlayerAddress()))
	{
		_viMonster->monsterState = MONSTERSTATE::ATTACK;

		_viMonster->atkleft = dirX == -1;
		_viMonster->atkright = dirX == 1;
		_viMonster->atkdown = dirY == -1;
		_viMonster->atkup = dirY == 1;
		return;
	}


	_viMonster->monsterState = MONSTERSTATE::MOVE;
	_viMonster->atkleft = false;
	_viMonster->atkright = false;
	_viMonster->atkdown = false;
	_viMonster->atkup = false;


	int tempX = _viMonster->posx;
	int tempY = _viMonster->posy;
	switch (_viMonster->monsterMoveState)
	{
	case MONSTERMOVESTATE::LEFT:
		tempX -= 1;
		break;
	case MONSTERMOVESTATE::UP:
		tempY -= 1;
		break;
	case MONSTERMOVESTATE::RIGHT:
		tempX += 1;
		break;
	case MONSTERMOVESTATE::DOWN:
		tempY += 1;
		break;
	default:
		break;
	}
	checkstatebroker();
	switch (_viMonster->monsterMoveState)
	{
	case MONSTERMOVESTATE::LEFT:
		if (_viMonster->canleft == false)
		{
			if (dirY > 0)
			{
				if (_viMonster->canup)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::UP;
				}
				else if (_viMonster->canright)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::RIGHT;
				}
				else
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
				}
			}
			else if (dirY <= 0)
			{
				if (_viMonster->candown)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::DOWN;
				}
				else if (_viMonster->canright)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::RIGHT;
				}
				else
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
				}
			}
			else
			{
				_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
			}
		}
		else if (_viMonster->canleft)
		{
			_viMonster->monsterMoveState = MONSTERMOVESTATE::LEFT;
		}
		break;
	case MONSTERMOVESTATE::RIGHT:
		if (_viMonster->canright == false)
		{
			if (dirY > 0)
			{
				if (_viMonster->canup)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::UP;
				}
				else if (_viMonster->canleft)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::LEFT;
				}
				else
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
				}

			}
			else if (dirY <= 0)
			{
				if (_viMonster->candown)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::DOWN;
				}
				else if (_viMonster->canleft)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::LEFT;
				}
				else
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
				}
			}
			else
			{
				_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
			}

		}
		else if (_viMonster->canright)
		{
			_viMonster->monsterMoveState = MONSTERMOVESTATE::RIGHT;
		}
		break;
	case MONSTERMOVESTATE::DOWN:
		if (_viMonster->candown == false)
		{
			if (dirX > 0)
			{
				if (_viMonster->canright)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::RIGHT;
				}
				else if (_viMonster->canup)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::UP;
				}
				else
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
				}
			}
			else if (dirX <= 0)
			{
				if (_viMonster->canleft)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::LEFT;
				}
				else if (_viMonster->canup)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::UP;
				}
				else
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
				}
			}
			else
			{
				_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
			}

		}
		else if (_viMonster->candown)
		{
			_viMonster->monsterMoveState = MONSTERMOVESTATE::DOWN;
		}
		break;
	case MONSTERMOVESTATE::UP:
		if (_viMonster->canup == false)
		{
			if (dirX > 0)
			{
				if (_viMonster->canright)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::RIGHT;
				}
				else if (_viMonster->candown)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::DOWN;
				}
				else
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
				}
			}
			else if (dirX <= 0)
			{
				if (_viMonster->canleft)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::LEFT;
				}
				else if (_viMonster->candown)
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::DOWN;
				}
				else
				{
					_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
				}
			}
			else
			{
				_viMonster->monsterMoveState = MONSTERMOVESTATE::NONE;
			}

		}
		else if (_viMonster->canup)
		{
			_viMonster->monsterMoveState = MONSTERMOVESTATE::UP;
		}
		break;
	}
	_viMonster->candown = false;
	_viMonster->canup = false;
	_viMonster->canright = false;
	_viMonster->canleft = false;

}
