#pragma once
#include "gameNode.h"
class necroDancerMain : public gameNode
{
public:
	necroDancerMain();
	~necroDancerMain();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);

};

