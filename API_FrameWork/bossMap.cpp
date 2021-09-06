#include "framework.h"
#include "bossMap.h"
#include "monsterManager.h"
#include"monster.h"
#include"realwallManager.h"
#include"rhythmUI.h"

bossMap::bossMap()
{
	_nextDoorOn = IMAGE->addImage("열린문", "images/tile/stair.bmp", 48, 48, true);
	_nextDoorOff = IMAGE->addImage("닫힌문", "images/tile/stairs_locked_miniboss.bmp", 48, 48, true);
}

bossMap::~bossMap()
{
}

HRESULT bossMap::init()
{
	
	spawnTime = true;
	level = 1;
	startNum = 0;
	doorX = 0;
	doorY = 0;
	makeDoor = false;
	doorOpen = false;
	timing = 0.0f;
	monsterNum = 1;
	soundOn = false;

	for (int i = 0; i < TILE_NUM_X; i++)
	{
		for (int k = 0; k < TILE_NUM_Y; k++)
		{
			Dungeon[i][k] = { 0 };
		}
	}
	srand(time(NULL));
	makeDungeon();
	showDungeon();

	return S_OK;
}

void bossMap::release()
{
}

void bossMap::update()
{
	if (soundOn == false)
	{
		SOUND->stop("1스테이지");
		SOUND->play("보스전", 0.5);
		soundOn = true;
	}
	_count += TIME->getElapsedTime();
	timing += TIME->getElapsedTime();

	if (spawnTime == true)
	{
		if (monsterNum > startNum)
		{
			spawnMon();
			startNum++;
		}
		if (doorNum == 1)
		{
			spawnNextStageDoor();
			--doorNum;
		}
	}
	if (_count > (1.9167f + 0.05f) / 4)
	{
		_rtm->spawnBeat(480, 0);
		_count = 0.0f;
	}
}

void bossMap::render()
{
	

	if (makeDoor == true)
	{
		if (doorOpen == true)
		{
			ZORDER->ZorderRender(_nextDoorOn, 4, 0, doorX, doorY);
		}
		else
		{
			ZORDER->ZorderRender(_nextDoorOff, 4, 0, doorX, doorY);
		}
	}
}

void bossMap::makeDungeon()
{
	for (int i = 0; i < 20; i++)
	{
		for (int k = 0; k < 15; k++)
		{
			if (k == 3)
			{
				Dungeon[i][k] = 0;
			}
			else
			{
				Dungeon[i][k] = 1;
			}
		}
	}

}


void bossMap::showDungeon()
{
	for (int i = 0; i < 20; i++) {
		for (int k = 0; k < 15; k++) {
			if (Dungeon[i][k] == 0 )
			{
				//_makeUnBrokeWall->addWall(i * 48, k * 48);
			}

		}
	}
}

void bossMap::spawnMon()
{
	int i = 7;
	int k = 4;
	_mm->getBlueSlime()->addMonster(i, k);
}

void bossMap::spawnNextStageDoor()
{
	int i = 7;
	int k = 1;

	doorX = i;
	doorY = k;
	makeDoor = true;
}
