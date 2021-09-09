#include "framework.h"
#include "wallManager.h"
#include "monsterManager.h"
#include"monster.h"
#include"rhythmUI.h"
#include "CWall.h"
#include "realwallManager.h"
wallManager::wallManager()
{
	_nextDoorOn = IMAGE->addImage("������", "images/tile/stairs.bmp", 48, 48,true);
	_nextDoorOff = IMAGE->addImage("������", "images/tile/stairs_locked_miniboss.bmp", 48, 48,true);
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
	count = 0.0;
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
	spawnHardWall();
	
	return S_OK;
}

void wallManager::release()
{
	_mm->getGreenSlime()->getVMonster().clear();
	_mm->getBlueSlime()->getVMonster().clear();
	_mm->getOrangeSlime()->getVMonster().clear();
	_mm->getWhiteskeleton()->getVMonster().clear();
	_rwm->getHardWall()->getVWall().clear();
	_rwm->getSoftWall()->getVWall().clear();
	_rwm->getUnBrokeWall()->getVWall().clear();
	for (int i = 0; i < 30; i++)
	{
		for (int k = 0; k < 30; k++)
		{
			setDungeon(i, k, 1);

		}
	}
}

void wallManager::update()
{
	if (soundOn == false)
	{
		SOUND->stop("������");
		SOUND->play("1��������", 0.3);
		soundOn = true;
	}
	count += TIME->getElapsedTime();
	timing += TIME->getElapsedTime();
	if (spawnTime == true)
	{
		if (doorNum == 1)
		{
			spawnNextStageDoor();
			--doorNum;
		}
		if (monsterNum > startNum)
		{
			spawnMon();
			startNum++;
		}
	}
	if (count > (2.08667/4))
	{
		_rtm->spawnBeat(480, 0);
		count = 0.0f;	
	}
	if (_mm->getGreenDragon()->getVMonster().size() == 0)
	{
		doorOpen = true;
	}
	if (PLAYER->getPlayerAddress().x == doorX && PLAYER->getPlayerAddress().y == doorY && doorOpen == true)
	{	
		PLAYER->getPlayerAddress().x = 9 * 48;
		PLAYER->getPlayerAddress().y = 15 * 48;
		PLAYER->getPlayerAddress().posx = PLAYER->getPlayerAddress().x/48;
		PLAYER->getPlayerAddress().posy = PLAYER->getPlayerAddress().y/48;
		_rwm->setcurScene("�ε�");
		SCENE->changeScene("�ε�");
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
	if (rLen / cLen > 1 || (cLen / rLen <= 1 && rand() % 2)) { // ���κ���
		int divideNum = (r2 - r1) * (rand() % 3 + 4) / 10;
		//�� ����
		temp1 = divideDungeon(depth - 1, r1, c1, r1 + divideNum, c2);
		temp2 = divideDungeon(depth - 1, r1 + divideNum, c1, r2, c2);

		//����ġ��.
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
	else {// ���κ���
		int divideNum = (c2 - c1) * (rand() % 3 + 4) / 10;
		//�����
		temp1 = divideDungeon(depth - 1, r1, c1, r2, c1 + divideNum);
		temp2 = divideDungeon(depth - 1, r1, c1 + +divideNum, r2, c2);

		//����ġ��
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

void wallManager::spawnHardWall()
{
	for (int i = 0; i < TILE_NUM_X; i++)
	{
		for (int k = 0; k < TILE_NUM_Y; k++)
		{
			if (i == 0 || i == TILE_NUM_X-1)
			{
				Dungeon[i][k] = 5;
				_rwm->getUnBrokeWall()->addWall(i*48, k * 48);
				_rwm->getSoftWall()->eraseWall(i*48,k*48);
			}
			if (k == 0 || k == TILE_NUM_Y-1)
			{
				Dungeon[i][k] = 5;
				_rwm->getUnBrokeWall()->addWall(i * 48, k * 48);
				_rwm->getSoftWall()->eraseWall(i*48,k*48);
			}
		}
	}
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
		_mm->getGreenDragon()->addMonster(i, k);
		doorX = i;
		doorY = k;
		makeDoor = true;
		eraseSPoint(_vSpawn.size() - 3);
		break;
	}
}
