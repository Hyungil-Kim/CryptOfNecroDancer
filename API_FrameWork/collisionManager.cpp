#include "framework.h"
#include "collisionManager.h"
#include "monsterManager.h"
#include "wallManager.h"

collisionManager::collisionManager()
{
}

collisionManager::~collisionManager()
{
}

HRESULT collisionManager::init()
{
	return S_OK;
}

void collisionManager::release()
{
}

void collisionManager::update()
{
	playerToMon();
	playerToWall();
}

void collisionManager::playerToWall()
{
}

void collisionManager::playerToMon()
{
	checkMonsterRectPlayer(mm->getGreenSlime());
	checkMonsterRectPlayer(mm->getBlueSlime());
	checkMonsterRectPlayer(mm->getOrangeSlime());
}

void collisionManager::checkMonsterRectPlayer(monster* monster)
{
	vector<tagMonster>& vMonster = monster->getVMonster();
	vector<tagMonster>::iterator iter = vMonster.begin();
	for (iter; iter != vMonster.end(); ++iter)
	{
		RECT temp;
		RECT* rc1 = &PLAYER->getPlayerAddress().player_rc;
		RECT* rc2 = &iter->rc;
		if (IntersectRect(&temp, rc1, rc2))
		{
			if (rc1->left-5 < rc2->right)
			{
				PLAYER->getPlayerAddress().goleft = false;
			}

		}
				PLAYER->getPlayerAddress().goleft = true;

	}
}
