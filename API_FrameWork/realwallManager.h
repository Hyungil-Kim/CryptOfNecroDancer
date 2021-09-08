#pragma once
#include "gameNode.h"
#include "makeWall.h"
class wallManager;
class CWall;
class bossMap;
class realwallManager : public gameNode
{
	wallManager* _wm;
	makeSoftWall* _swall;
	makeHardWall* _hwall;
	makeUnBrokeWall* _uwall;
	CWall* _cwall;
	bossMap* _boss;

	string curScene;
public:

	realwallManager();
	~realwallManager();

	HRESULT init();
	void release();
	void update();
	void render();


 	makeSoftWall* getSoftWall() { return _swall; }
	makeHardWall* getHardWall() { return _hwall; }
	makeUnBrokeWall* getUnBrokeWall() { return _uwall; }

	string getcurScene() { return curScene; }
	void setcurScene(string curScene) { this->curScene = curScene; }
	void setWallManagerMemoryLink(wallManager* wallManager) { _wm = wallManager; }
	void setCWallMemoryLink(CWall* CWall) { _cwall = CWall; }
	void setbossMapMemoryLink(bossMap* bossMap) { _boss = bossMap; }
};

