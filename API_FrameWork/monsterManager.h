#pragma once
#include "gameNode.h"
#include "makeMonster.h"
class monsterManager : public gameNode
{
private:
	Player* _py;
private:
	green_slime* _green_slime;
	blue_slime* _blue_slime;





private:
	bool _isDebug;

public:
	monsterManager();
	~monsterManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//���� �ν��Ͻ� getter
	green_slime* getGreenSlime() { return _green_slime; }







	//��ũ
	void setPlayerMemoryLink(Player* py) { _py = py; }
	//�����
	void setIsDebug(bool isDebug) {
		_isDebug = isDebug;
		_green_slime->setIsDebug(_isDebug);
	}
};

