#pragma once
#include "gameNode.h"
#include"monsterManager.h"
#include"wallManager.h"
#include"rhythmUI.h"
#include "CMap.h"


class necroDancerMain : public gameNode
{
private:
	monsterManager* _mm;
	rhythmUI* _rUI;
	wallManager* _wm;
	CMap* map;
	monster* _mon;

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
	 void initForSound();
	void setIsDebug(bool isDebug) { 
		_isDebug = isDebug; 
		//PLAYER->setIsDebug(_isDebug);
		//_mm->setIsDebug(_isDebug);
		//_wm->setIsDebug(_isDebug);
		//map->setIsDebug(_isDebug);
		_rUI->setIsDebug(_isDebug);
	}
};

