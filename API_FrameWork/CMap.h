#pragma once
#include "gameNode.h"
#include "CTile.h"


class CMap :public gameNode
{
private:
	CTile* tile[TILE_NUM_X * TILE_NUM_Y];

	bool isDebug;

public:
	CMap();
	CMap(POINT startPos, POINT size);
	~CMap();

	HRESULT init();
	void release();
	void update();
	void render();

	CTile** getTile() { return tile; }

};

