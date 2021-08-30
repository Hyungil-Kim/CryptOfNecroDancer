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
	if (_wm->getDungeon(tempX,tempY) != 0)
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
