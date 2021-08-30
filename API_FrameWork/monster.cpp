#include "framework.h"
#include "monster.h"
#include"wallManager.h"
monster::monster()
{
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
	
	if (findPlayer(tempX,tempY) == false)
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
	else
	{
		_viMonster->canleft = false;
		_viMonster->canright = false;
		_viMonster->canup = false;
		_viMonster->candown = false;
	}
}

bool monster::findMonster(int x, int y)
{
	for (int i = 0; i < _vMonster.size(); i++)
	{
		if (_vMonster[i].posx == x && _vMonster[i].posy == y)
		{
			return true;
			
		}
	}
	return false;
}

bool monster::findPlayer(int x, int y)
{
	if (PLAYER->getPlayerAddress().posx ==x && PLAYER->getPlayerAddress().posy == y)
		return true;
	else
		return false;
}
