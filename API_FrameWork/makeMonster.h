#pragma once
#include"monster.h"
class green_slime : public monster
{


public:
	green_slime();
	~green_slime();

	HRESULT init();
	void release();
	void update(Player* cp);//�÷��̾� ��ġ �����ϱ����� 
	void render();

	virtual void addMonster(float x, float y);
	virtual void stateCheck();
	virtual void moveMonster();
	
};
class blue_slime : public monster
{


public:
	blue_slime();
	~blue_slime();

	HRESULT init();
	void release();
	void update(Player* cp);//�÷��̾� ��ġ �����ϱ����� 
	void render();

	virtual void addMonster(float x, float y);
	virtual void stateCheck();
	virtual void moveMonster();
};
