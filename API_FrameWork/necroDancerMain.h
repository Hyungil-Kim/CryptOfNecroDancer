#pragma once
#include "gameNode.h"
#include"monsterManager.h"
#include"wallManager.h"
#include "CMap.h"
class necroDancerMain : public gameNode
{
private:
	monsterManager* _mm;
	wallManager* _wm;
	CMap* map;


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
		_wm->setIsDebug(_isDebug);
		map->setIsDebug(_isDebug);
	}
};

