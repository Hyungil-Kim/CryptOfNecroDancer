#pragma once
#include "gameNode.h"
#include "makeMonster.h"

class wallManager;
class monster;
class rhythmUI;
class monsterManager : public gameNode
{
private:
	Player* _py;
	wallManager* _wm;
	monster* _mon;
	rhythmUI* _rtm;
private:
	green_slime* _green_slime;
	blue_slime* _blue_slime;
	orange_slime* _orange_slime;
	white_skeleton* _white_skeleton;



private:
	bool _isDebug;

public:
	monsterManager();
	~monsterManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//몬스터 인스턴스 getter
	green_slime* getGreenSlime() { return _green_slime; }
	blue_slime* getBlueSlime() { return _blue_slime; }
	orange_slime* getOrangeSlime() { return _orange_slime; }
	white_skeleton* getWhiteskeleton() { return _white_skeleton; }







	//링크
	void setPlayerMemoryLink(Player* py) { _py = py; }
	void spawn();
	virtual void setrtmMemoryLink(rhythmUI* rhythmUI) { _rtm = rhythmUI; }
	void setWallMemoryLink(wallManager* wallManager) { _wm = wallManager; }
	void setmonsterMemoryLink(monster* monster) { _mon = monster; }
	//디버그
	void setIsDebug(bool isDebug) {
		_isDebug = isDebug;
		_green_slime->setIsDebug(_isDebug);
		_blue_slime->setIsDebug(_isDebug);
		_orange_slime->setIsDebug(_isDebug);
	}
};

