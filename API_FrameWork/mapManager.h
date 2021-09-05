#pragma once
#include"gameNode.h"
class wallManager;
class bossMap;
class mapManager :public gameNode
{
	wallManager* _wm;
	bossMap* _bossmap;
	string currentMap;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);
	void setWallManagerMemoryLink(wallManager* wallManager) { _wm = wallManager; }
	void setbossMapMemoryLink(bossMap* bossMap) { _bossmap = bossMap; }
};

