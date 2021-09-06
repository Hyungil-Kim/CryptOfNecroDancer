#pragma once
#include"gameNode.h"

#include "CMap.h"
class rhythmUI;
class monsterManager;
class monster;
class realwallManager;
class bossMap :public gameNode
{
private:
	monsterManager* _mm;
	realwallManager* _rwm;
	image* _nextDoorOn;
	image* _nextDoorOff;
	monster* _mon;
	rhythmUI* _rtm;
	CMap* _cmap;
	int Dungeon[TILE_NUM_X][TILE_NUM_Y] = {};
	float monsterNum;
	int doorNum = 1;
	int startNum;
	int doorX, doorY;
	bool makeDoor = false;
	int level;
	int randdomNum;
	bool spawnTime;
	bool doorOpen = false;
	float timing;
	float _count;
	bool soundOn = false;
public:
	bossMap();
	~bossMap();

	HRESULT init();
	void release();
	void update();
	void render();
	void makeDungeon();
	void showDungeon();
	void spawnMon();
	void spawnNextStageDoor();

	void setrtmMemoryLink(rhythmUI* rhythmUI) { _rtm = rhythmUI; }
	void setMonsterManagerMemoryLink(monsterManager* monsterManager) { _mm = monsterManager; }
	void setMonsterMemoryLink(monster* monster) { _mon = monster; }
	void setrealWallManagerMemoryLink(realwallManager* realwallManager) { _rwm = realwallManager; }
};

