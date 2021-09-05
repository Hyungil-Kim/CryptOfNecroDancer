#pragma once
#include "gameNode.h"
class Title :public gameNode
{
private:
	image* _title;
	image* _continue;
	bool _isStart;
	bool _isDone;
public:
	Title();
	~Title();

	HRESULT init();
	void release();
	void update();
	void render();

	bool getIsStart() { return _isStart; }
	bool getIsDone() { return _isDone; }
};

