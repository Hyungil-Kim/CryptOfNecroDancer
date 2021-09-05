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
	virtual void eraseWall(int x, int y);
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
	void update();//�÷��̾� ��ġ �����ϱ����� 
	void render();
	virtual void eraseWall(int x, int y);
	virtual void addWall(float x, float y);
	virtual void updateRect(vector<tagWall>::iterator iter);
};

class makeUnBrokeWall :public CWall
{
	image* unBrokeWall;

public:
	makeUnBrokeWall();
	~makeUnBrokeWall();

	HRESULT init();
	void release();
	void update();//�÷��̾� ��ġ �����ϱ����� 
	void render();
	virtual void eraseWall(int x, int y);
	virtual void addWall(float x, float y);
	virtual void updateRect(vector<tagWall>::iterator iter);
};

