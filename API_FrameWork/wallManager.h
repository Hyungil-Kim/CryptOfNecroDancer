#pragma once
#include "gameNode.h"
#include "makeWall.h"
class wallManager : public gameNode
{
private:
	makeSoftWall* _makeSoftWall;
private:
	bool _isDebug;

public:
	wallManager();
	~wallManager();

	HRESULT init();
	void release();
	void update();
	void render();

	
	makeSoftWall* getsoftWall() { return _makeSoftWall; }
	void setIsDebug(bool isDebug) {
		_isDebug = isDebug;
		_makeSoftWall->setIsDebug(_isDebug);
	
	}
};

