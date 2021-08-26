#pragma once
#include "gameNode.h"
#include "monster.h"
class wallManager;
class monsterManager;
class collisionManager : public gameNode
{
private:
	wallManager* wm;
	monsterManager* mm;

	float _x;
	float _y;
	RECT rcTemp;
private:
	bool _isDebug;
public:
	collisionManager();
	~collisionManager();
	HRESULT init();
	void release();
	void update();

	void playerToWall();
	void playerToMon();
	void checkMonsterRectPlayer(monster* monster);
	void setMonsterMemoryLink(monsterManager* monsterManger) { mm = monsterManger; }

};

