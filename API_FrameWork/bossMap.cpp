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
	_chair = IMAGE->addFrameImage("의자", "images/monster/king_conga_throne.bmp", 48 , 48 * 2, 1, 1, true);
	_chairkonga = IMAGE->addFrameImage("킹콩가의자", "images/monster/stop_kong.bmp", 48 * 5, 48 * 2*2, 5, 2, true);
	_chairKong = ANIMATION->addNoneKeyAnimation("킹콩가의자", 4,0,4, false, true);
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
	startNum = 0;
	_count = 0;
	elsecount = 5;
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
	spawnMon();
	return S_OK;
}

void bossMap::release()
{

}

void bossMap::update()
{
	if (soundOn == false)
	{
		if (_rwm->getcurScene() == "보스전")
		{
			SOUND->stop("로딩");
			SOUND->play("보스전", 0.5);
			soundOn = true;
		}
	}
	_count += TIME->getElapsedTime();

	if (spawnTime == true)
	{
		if (monsterNum > startNum && _mm->getWhiteskeleton()->getVMonster().size() == 0)
		{
			Dungeon[9][5] = 0;
			spawnBoss();
			startNum++;
		}
		if (doorNum == 1)
		{
			spawnNextStageDoor();
			--doorNum;
		}
	}
	if (_count > (2.0f) / 4)
	{
		if (!(elsecount == 8))
		{
			_rtm->spawnBeat(480, 0);
		}
		else
		{
			elsecount = 0;
		}
		elsecount++;
		_count = 0.0f;
	}

	if (_mm->getKingKong()->getVMonster().size() == 0 && _mm->getWhiteskeleton()->getVMonster().size() == 0)
	{
		doorOpen = true;
	}
	if (PLAYER->getPlayerAddress().x == doorX && PLAYER->getPlayerAddress().y == doorY && doorOpen == true)
	{
		PLAYER->getPlayerAddress().x = 9 * 48;
		PLAYER->getPlayerAddress().y = 15 * 48;
		PLAYER->getPlayerAddress().posx = PLAYER->getPlayerAddress().x / 48;
		PLAYER->getPlayerAddress().posy = PLAYER->getPlayerAddress().y / 48;
		_rwm->setcurScene("엔딩");
		SCENE->changeScene("엔딩");
		
	}
}

void bossMap::render()
{
	if (_mm->getWhiteskeleton()->getVMonster().size() == 0)
	{
		ZORDER->ZorderRender(_chair, 3, 0, 9 * 48, 4 * 48);
	}
	else
	{
		ZORDER->ZorderAniRender(_chairkonga, 3, 10000, 9 * 48, 4 * 48, _chairKong);
	}

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
	for (int i = 0; i < 30; i++)
	{
		for (int k = 0; k < 20; k++)
		{
			{
				Dungeon[i][k] = 1;
			}
		}
	}
	for (int i = 0; i < 20; i++)
	{
		for (int k = 0; k < 20; k++)
		{
			if (i == 0 || i == 19)
			{
				Dungeon[i][k] = 5;

			}
			if (k == 0 || k == 19)
			{
				Dungeon[i][k] = 5;
			}
		}
	}
}


void bossMap::showDungeon()
{
	for (int i = 0; i < 20; i++) {
		for (int k = 0; k < 20; k++) {
			if (Dungeon[i][k] == 5 )
			{
				_rwm->getUnBrokeWall()->addWall(i * 48, k * 48);
			}
		}
	}
}

void bossMap::spawnMon()
{


	for (int t = 3; t < 16; t++)
	{
		for (int j = 5; j < 13; j++)
		{
			if (t == 9 && j == 5)
				Dungeon[t][j] = 5;
			if (t == 3 || t == 15)
			{
			_mm->getWhiteskeleton()->addMonster(t*48, j*48);
			}
		}
	}
}

void bossMap::spawnBoss()
{
	int i = 7 * 48;
	int k = 4 * 48;
	_mm->getKingKong()->addMonster(i, k);

}

void bossMap::spawnNextStageDoor()
{
	int i = 9*48;
	int k = 3*48;

	doorX = i;
	doorY = k;
	makeDoor = true;
}
