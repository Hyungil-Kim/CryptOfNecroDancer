#pragma once
#include "gameNode.h"

#include "CMap.h"

typedef struct DLocation {
	int r1, c1, r2, c2;
	int r3, c3, r4, c4;
};
struct SpawnPoint {
	int x;
	int y;
};
class rhythmUI;
class monsterManager;
class monster;
class realwallManager;
class CWall;
class wallManager : public gameNode
{
private:
	monsterManager* _mm;
	realwallManager* _rwm;
	image* _nextDoorOn;
	image* _nextDoorOff;
	monster* _mon;
	rhythmUI* _rtm;
	CMap* _cmap;
	CWall* _cwall;
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
	bool soundOn = false;
	vector<SpawnPoint> _vSpawn;
	vector<SpawnPoint>::iterator _viSpawn;

private:
	bool _isDebug;
	float count = 0;//1,9167
public:
	wallManager();
	~wallManager();

	HRESULT init();
	void release();
	void update();
	void render();
	void makeDungeon();
	void showDungeon();
	void spawnMon();
	void eraseSPoint(int arrNum);
	void spawnNextStageDoor();
	void spawnHardWall();

	float getcount() { return count; }
	int getDungeon(int i , int k) { return Dungeon[i][k]; }
	void setDungeon(int i, int k, int t) { Dungeon[i][k] = t; }
	
	vector<SpawnPoint>& getVSpawnPoint() { return _vSpawn; }
	vector<SpawnPoint>::iterator& getViSpawnPoint() { return _viSpawn; }
	DLocation divideDungeon(int depth, int r1, int c1, int r2, int c2);


	void setrtmMemoryLink(rhythmUI* rhythmUI) { _rtm = rhythmUI; }
	void setMonsterManagerMemoryLink(monsterManager* monsterManager) { _mm = monsterManager; }
	void setMonsterMemoryLink(monster* monster) { _mon = monster; }
	void setrealWallManagerMemoryLink(realwallManager* realwallManager) { _rwm = realwallManager; }
	void setCWallMemoryLink(CWall* CWall) { _cwall = CWall; }
	void setIsDebug(bool isDebug) {
		_isDebug = isDebug;
	 
	}
	
};

