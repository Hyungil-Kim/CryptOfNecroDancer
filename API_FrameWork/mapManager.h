#pragma once
#include"gameNode.h"

class rhythmUI;
class monsterManager;
class realwallManager;
class wallManager;
class bossMap;
class mapManager :public gameNode
{
	bossMap* _bossmap;
	wallManager* _wm;
	monsterManager* _mm;
	realwallManager* _rwm;
	rhythmUI* _rtm;
public:

	mapManager();
	~mapManager();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);
	
	bossMap* getBossMap() { return _bossmap; }
	wallManager* getWallManager() { return _wm; }
	rhythmUI* getRhythm() { return _rtm; }
	void setMonsterManagerMemoryLink(monsterManager* monsterManager) {_mm = monsterManager; }
	void setrealWallManagerMemoryLink(realwallManager* realwallManager) {_rwm = realwallManager; }
	void setrhythmMemoryLink(rhythmUI* rhythmUI) {_rtm = rhythmUI; }
};

