#pragma once
#include "gameNode.h"
class loading :public gameNode
{
private:
	image* _title;
	image* _continue;
	bool _isStart;
	bool _isDone;
	int loadingCount;
	int loadingTime;
public:
	loading();
	~loading();

	HRESULT init();
	void release();
	void update();
	void render();

	bool getIsStart() { return _isStart; }
	bool getIsDone() { return _isDone; }
	void setIsStart(bool _isStart) { this->_isStart = _isStart; }

};

