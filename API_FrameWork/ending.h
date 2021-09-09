#pragma once
#include "gameNode.h"
class ending : public gameNode
{
private:
	image* _title;
	image* _continue;
	bool _isStart;
	bool _isDone;
public:
	ending();
	~ending();

	HRESULT init();
	void release();
	void update();
	void render();

	bool getIsStart() { return _isStart; }
	bool getIsDone() { return _isDone; }
};

