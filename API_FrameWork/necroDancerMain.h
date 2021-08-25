#pragma once
#include "gameNode.h"

#include "dummyMap.h"

class necroDancerMain : public gameNode
{
private:
	
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
	
	}
};

