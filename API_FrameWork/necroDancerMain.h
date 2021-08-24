#pragma once
#include "gameNode.h"
#include"monsterManager.h"
#include "dummyMap.h"

class necroDancerMain : public gameNode
{
private:
	monsterManager* _mm;
	dummyMap* _dmap;

private:
	bool _isDebug;


public:
	necroDancerMain();
	~necroDancerMain();

	 HRESULT init();
	 void release();
	 void update();
	 void render(/*HDC hdc*/);
	 void gameinit();
	void setIsDebug(bool isDebug) { 
		_isDebug = isDebug; 
		PLAYER->setIsDebug(_isDebug);
		_mm->setIsDebug(_isDebug);
	}
};

