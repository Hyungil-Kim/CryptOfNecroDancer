#pragma once
#include "gameNode.h"
#include "makeWall.h"
#include "CMap.h"
typedef struct DLocation {
	int r1, c1, r2, c2;
	int r3, c3, r4, c4;
};
struct SpawnPoint {
	int x;
	int y;
};
class wallManager : public gameNode
{
private:
	makeSoftWall* _makeSoftWall;
	makeHardWall* _makeHardWall;
	CMap* _cmap;
	int Dungeon[TILE_NUM_X][TILE_NUM_Y] = {};

	vector<SpawnPoint> _vSpawn;
	vector<SpawnPoint>::iterator _viSpawn;

private:
	bool _isDebug;

public:
	wallManager();
	~wallManager();

	HRESULT init();
	void release();
	void update();
	void render();
	void makeDungeon();
	void showDungeon();
	

	int getDungeon(int i , int k) { return Dungeon[i][k]; }
	vector<SpawnPoint>& getVSpawnPoint() { return _vSpawn; }
	DLocation divideDungeon(int depth, int r1, int c1, int r2, int c2);
	makeSoftWall* getsoftWall() { return _makeSoftWall; }
	void setIsDebug(bool isDebug) {
		_isDebug = isDebug;
		_makeSoftWall->setIsDebug(_isDebug);
	
	}
	void SpawnPoint();
};

