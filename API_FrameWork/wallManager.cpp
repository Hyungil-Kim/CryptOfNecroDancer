#include "framework.h"
#include "wallManager.h"
#include "monsterManager.h"
#include"monster.h"
#include"rhythmUI.h"
#include "CWall.h"
#include "realwallManager.h"
wallManager::wallManager()
{
	_nextDoorOn = IMAGE->addImage("열린문", "images/tile/stair.bmp", 48, 48,true);
	_nextDoorOff = IMAGE->addImage("닫힌문", "images/tile/stairs_locked_miniboss.bmp", 48, 48,true);
}

wallManager::~wallManager()
{
}

HRESULT wallManager::init()
{
	spawnTime = true;
	level = 1;
	startNum = 0;
	doorX = 0;
	doorY = 0;
	makeDoor = false;
	doorOpen = false;
	count = 0.0f;
	timing = 0.0f;
	monsterNum = 12 + level * 2.5;
	count = 0;
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

void wallManager::release()
{
}

void wallManager::update()
{
	if (soundOn == false)
	{
		SOUND->stop("오프닝");
		SOUND->play("1스테이지", 0.5);
		soundOn = true;
	}
	count += TIME->getElapsedTime();
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
	if (count > (1.9167f + 0.05f)/4)
	{
		_rtm->spawnBeat(480, 0);
		count = 0.0f;	
	}
	
}

void wallManager::render()
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

DLocation wallManager::divideDungeon(int depth, int r1, int c1, int r2, int c2)
{
	DLocation Location;
	if (depth == 0 || (r2 - r1 <= 10 || c2 - c1 <= 10)) {
		for (int i = r1 + 2; i < r2 - 2; i++) {
			for (int k = c1 + 2; k < c2 - 2; k++)
			{
				Dungeon[i][k] = 1;// _makeSoftWall->addWall(i * 48, k * 48);
				if (Dungeon[i][k] == 1)
				{
					SpawnPoint newspawnPoint;
					newspawnPoint.x = i*48;
					newspawnPoint.y = k*48;
					_vSpawn.push_back(newspawnPoint);
				}
			}
		}
	return { r1 + 2,c1 + 2,r2 - 3,c2 - 3,r1 + 2,c1 + 2,r2 - 3,c2 - 3 };
	}

	int rLen = r2 - r1;
	int cLen = c2 - c1;
	DLocation temp1, temp2;
	if (rLen / cLen > 1 || (cLen / rLen <= 1 && rand() % 2)) { // 세로분할
		int divideNum = (r2 - r1) * (rand() % 3 + 4) / 10;
		//방 분할
		temp1 = divideDungeon(depth - 1, r1, c1, r1 + divideNum, c2);
		temp2 = divideDungeon(depth - 1, r1 + divideNum, c1, r2, c2);

		//방합치기.
		Dungeon[temp1.r4 + 1][(temp1.c3 + temp1.c4) / 2] = 4;
		Dungeon[temp1.r4 + 2][(temp1.c3 + temp1.c4) / 2] = 4;
		Dungeon[temp2.r1 - 1][(temp2.c1 + temp2.c2) / 2] = 4;
		Dungeon[temp2.r1 - 2][(temp2.c1 + temp2.c2) / 2] = 4;
		int rmin = min((temp1.c3 + temp1.c4) / 2, (temp2.c1 + temp2.c2) / 2);
		int rmax = max((temp1.c3 + temp1.c4) / 2, (temp2.c1 + temp2.c2) / 2);
		for (int i = rmin; i <= rmax; i++) {
			Dungeon[temp2.r1 - 2][i] = 4;
		}
	}
	else {// 가로분할
		int divideNum = (c2 - c1) * (rand() % 3 + 4) / 10;
		//방분할
		temp1 = divideDungeon(depth - 1, r1, c1, r2, c1 + divideNum);
		temp2 = divideDungeon(depth - 1, r1, c1 + +divideNum, r2, c2);

		//방합치기
		Dungeon[(temp1.r3 + temp1.r4) / 2][temp1.c4 + 1] = 3;
		Dungeon[(temp1.r3 + temp1.r4) / 2][temp1.c4 + 2] = 3;
		Dungeon[(temp2.r1 + temp2.r2) / 2][temp2.c1 - 1] = 3;
		Dungeon[(temp2.r1 + temp2.r2) / 2][temp2.c1 - 2] = 3;

		int rmin = min((temp1.r3 + temp1.r4) / 2, (temp2.r1 + temp2.r2) / 2);
		int rmax = max((temp1.r3 + temp1.r4) / 2, (temp2.r1 + temp2.r2) / 2);
		for (int i = rmin; i <= rmax; i++) {
			Dungeon[i][temp2.c1 - 2] = 3;
		}
	}
	Location.r1 = temp1.r1, Location.r2 = temp1.r2, Location.c1 = temp1.c1, Location.c2 = temp1.c2;
	Location.r3 = temp2.r3, Location.r4 = temp2.r4, Location.c3 = temp2.c3, Location.c4 = temp2.c4;

	return Location;
}



void wallManager::makeDungeon()
{
	memset(Dungeon, 0, sizeof(Dungeon));
	divideDungeon(5, 0, 0, TILE_NUM_X, TILE_NUM_Y);
}
void wallManager::showDungeon() {
	for (int i = 0; i < TILE_NUM_X; i++) {
		for (int k = 0; k < TILE_NUM_Y; k++) {
			if (Dungeon[i][k] == 0)
			{
				_rwm->getSoftWall()->addWall(i*48,k*48);
				
			}
		}
	}
}

void wallManager::spawnMon()
{
	for (int j = 0; j < _vSpawn.size(); j++)
	{
		int random = 0;
		random = RND->getFromInTo(0, _vSpawn.size()-1);
		int randdomNum = RND->getFromInTo(0, 3);
		int i =	_vSpawn[random].x;
		int k =	_vSpawn[random].y;
		switch (randdomNum)
		{
			case 0:
			//	_mm->getWhiteskeleton()->addMonster(i, k);
				_mm->getGreenSlime()->addMonster(i, k);
			eraseSPoint(random);
				break;
			case 1:	
				//_mm->getWhiteskeleton()->addMonster(i, k);
			_mm->getBlueSlime()->addMonster(i, k);
			eraseSPoint(random);
				break;
			case 2:	
			//	_mm->getWhiteskeleton()->addMonster(i, k);
			_mm->getOrangeSlime()->addMonster(i, k);
			eraseSPoint(random);
				break;
			case 3:
				_mm->getWhiteskeleton()->addMonster(i, k);
				eraseSPoint(random);
				break;
		default:
			break;
		}
		break;

	}
}

void wallManager::eraseSPoint(int arrNum)
{
	_vSpawn.erase(_vSpawn.begin() + arrNum);
}

void wallManager::spawnNextStageDoor()
{
	for (int j = 0; j < _vSpawn.size(); j++)
	{
		int i = _vSpawn[_vSpawn.size() - 3].x;
		int k = _vSpawn[_vSpawn.size() - 3].y;

		doorX = i;
		doorY = k;
		makeDoor = true;
	}
}
