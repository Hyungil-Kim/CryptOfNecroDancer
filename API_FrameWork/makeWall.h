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
	void update();//�÷��̾� ��ġ �����ϱ����� 
	void render();

	virtual void addWall(float x, float y);
	virtual void updateRect(vector<tagWall>::iterator iter);
};

