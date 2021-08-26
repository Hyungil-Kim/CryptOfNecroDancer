#pragma once
#include "gameNode.h"
#include "CTile.h"
#include "monster.h"
#include "CWall.h"


class CMap :public gameNode
{
	CTile* tile[TILE_NUM_X * TILE_NUM_Y];
	
	
	bool _isDebug;
public:
	
	CMap();
	CMap(POINT startPos, POINT size);
	~CMap();

	HRESULT init();
	void release();
	void update();
	void render();
	void makeWall();


	CTile** getTile() { return tile; }

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

