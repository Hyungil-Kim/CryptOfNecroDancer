#pragma once
#include "CWall.h"
class makeSoftWall :public CWall
{
	image* normal_wall;
public:
	makeSoftWall();
	~makeSoftWall();

	HRESULT init();
	void release();
	void update();//플레이어 위치 참고하기위해 
	void render();

	virtual void addWall(float x, float y);
	virtual void updateRect(vector<tagWall>::iterator iter);
};

class makeHardWall :public CWall
{
	image* hard_wall;
public:
	makeHardWall();
	~makeHardWall();

	HRESULT init();
	void release();
	void update();//플레이어 위치 참고하기위해 
	void render();

	virtual void addWall(float x, float y);
	virtual void updateRect(vector<tagWall>::iterator iter);
};

