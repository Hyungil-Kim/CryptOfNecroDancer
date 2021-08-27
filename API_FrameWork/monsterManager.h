#pragma once
#include "gameNode.h"
#include "makeMonster.h"

class wallManager;
class monsterManager : public gameNode
{
private:
	Player* _py;
	wallManager* _wm;
private:
	green_slime* _green_slime;
	blue_slime* _blue_slime;
	orange_slime* _orange_slime;
	



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







	//링크
	void setPlayerMemoryLink(Player* py) { _py = py; }

	void setWallMemoryLink(wallManager* wallManager) { _wm = wallManager; }
	//디버그
	void setIsDebug(bool isDebug) {
		_isDebug = isDebug;
		_green_slime->setIsDebug(_isDebug);
		_blue_slime->setIsDebug(_isDebug);
		_orange_slime->setIsDebug(_isDebug);
	}
};

