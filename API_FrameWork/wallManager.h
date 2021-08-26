#pragma once
#include "gameNode.h"
#include "makeWall.h"
#include "CMap.h"
class wallManager : public gameNode
{
private:
	makeSoftWall* _makeSoftWall;
	makeHardWall* _makeHardWall;
	CMap* _cmap;
private:
	bool _isDebug;

public:
	wallManager();
	~wallManager();

	HRESULT init();
	void release();
	void update();
	void render();
	void makeDungeon(int i , int l);
	
	makeSoftWall* getsoftWall() { return _makeSoftWall; }
	void setIsDebug(bool isDebug) {
		_isDebug = isDebug;
		_makeSoftWall->setIsDebug(_isDebug);
	
	}
};

