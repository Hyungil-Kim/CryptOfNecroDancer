#include "framework.h"
#include "monster.h"
#include"wallManager.h"
#include"monsterManager.h"
#include"rhythmUI.h"
monster::monster()
{
	IMAGE->addFrameImage("�¿����", "images/monster/monatk1.bmp", 135 * 2, 46 * 2, 5, 2, true);
	IMAGE->addFrameImage("���ϰ���", "images/monster/monatk2.bmp", 115 * 2, 54 * 2, 5, 2, true);
	ANIMATION->addNoneKeyAnimation("���ϰ���", 0, 4, 3, false, false);
	ANIMATION->addNoneKeyAnimation("���ϰ���", 9, 5, 3, false, false);
	ANIMATION->addNoneKeyAnimation("�¿����", 0, 4, 3, false, false);
	ANIMATION->addNoneKeyAnimation("�¿����", 5, 9, 3, false, false);
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
	else
	{
		_viMonster->atkdown = true;
		_viMonster->atkup = true;
		_viMonster->atkright = true;
		_viMonster->atkleft = true;
	}

}

void monster::isCanMove2()
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
		if (monTomon(tempX, tempY) == false)
		{
			if (_wm->getDungeon(tempX, tempY) != 0)
			{
				_viMonster->isMove = true;
			}
		}
	}

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
		findMonster(_mm->getWhiteskeleton(),x,y)
		)
	{
		return true;
	}
	return false;
}



void monster::attack()
{
	PLAYER->getPlayerAddress().hp -= _viMonster->atk;
}

void monster::getDamage()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		_viMonster->hp -= PLAYER->getPlayerAddress().atk;
	}
}

void monster::setdirection()
{
	
		_viMonster->posx = _viMonster->x / 48;
		_viMonster->posy = _viMonster->y / 48;
		int tempX = _viMonster->posx;
		int tempY = _viMonster->posy;
		switch (_viMonster->monsterMoveState)
		{
		case MONSTERMOVESTATE::LEFT:
			tempX -= 1;
			if (_viMonster->posx <= PLAYER->getPlayerAddress().posx && _viMonster->isMove == true)
			{
				if (_viMonster->posy < PLAYER->getPlayerAddress().posy)
					_viMonster->monsterMoveState = MONSTERMOVESTATE::DOWN;
				else if (_viMonster->posy > PLAYER->getPlayerAddress().posy)
					_viMonster->monsterMoveState = MONSTERMOVESTATE::UP;
			}
			break;
		case MONSTERMOVESTATE::RIGHT:
			tempX += 1;
			if (_viMonster->posx >= PLAYER->getPlayerAddress().posx && _viMonster->isMove == true)
			{
				if (_viMonster->posy < PLAYER->getPlayerAddress().posy)
					_viMonster->monsterMoveState = MONSTERMOVESTATE::DOWN;
				else if (_viMonster->posy > PLAYER->getPlayerAddress().posy)
					_viMonster->monsterMoveState = MONSTERMOVESTATE::UP;
			}
			break;
		case MONSTERMOVESTATE::UP:
			tempY -= 1;
			if (_viMonster->posy <= PLAYER->getPlayerAddress().posy || _viMonster->isMove == false)
			{
				if (_viMonster->posx > PLAYER->getPlayerAddress().posx)
					_viMonster->monsterMoveState = MONSTERMOVESTATE::LEFT;
				else if (_viMonster->posx < PLAYER->getPlayerAddress().posx)
					_viMonster->monsterMoveState = MONSTERMOVESTATE::RIGHT;
			}
			break;
		case MONSTERMOVESTATE::DOWN:
			tempY += 1;
			if (_viMonster->posy >= PLAYER->getPlayerAddress().posy || _viMonster->isMove == false)
			{
				if (_viMonster->posx > PLAYER->getPlayerAddress().posx)
					_viMonster->monsterMoveState = MONSTERMOVESTATE::LEFT;
				else if (_viMonster->posx < PLAYER->getPlayerAddress().posx)
					_viMonster->monsterMoveState = MONSTERMOVESTATE::RIGHT;
			}
			break;
		}
	
}

void monster::checkInvincibility()
{
	//����Ȯ���Լ�
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
