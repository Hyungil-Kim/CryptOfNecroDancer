#pragma once
#include "gameNode.h"
#include "makeMonster.h"
class monsterManager : public gameNode
{
private:
	Player* _py;
private:
	green_slime* _green_slime;






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







	//링크
	void setPlayerMemoryLink(Player* py) { _py = py; }
	//디버그
	void setIsDebug(bool isDebug) {
		_isDebug = isDebug;
		_green_slime->setIsDebug(_isDebug);
	}
};

