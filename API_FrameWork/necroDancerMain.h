#pragma once
#include "gameNode.h"
#include"monsterManager.h"
#include"wallManager.h"
#include"rhythmUI.h"
#include "CMap.h"
#include "realwallManager.h"
#include "Title.h"
#include "bossMap.h"
#include "mapManager.h"
class necroDancerMain : public gameNode
{
private:
	monsterManager* _mm;
	rhythmUI* _rUI;
	wallManager* _wm;
	CMap* map;
	makeSoftWall* _swall;
	makeHardWall* _hwall; 
	makeUnBrokeWall* _uwall;
	monster* _mon;
	realwallManager* _rwm;
	bossMap* _boss;
	mapManager* _map;
private:
	enum class SCENESTATE
	{
		START,
		GAME,
		ENDING
	};
private:
	Title* _title;
	bool _isDebug;
	SCENESTATE _sceneState;
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

