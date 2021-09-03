#pragma once
#include"monster.h"
class green_slime : public monster
{


public:
	green_slime();
	~green_slime();

	HRESULT init();
	void release();
	void update(Player* cp);//플레이어 위치 참고하기위해 
	void render();

	virtual void addMonster(float x, float y);
	virtual void stateCheck();
	virtual void moveMonster();
	virtual void dead();
	virtual void updateRect(vector<tagMonster>::iterator iter);
	
};
class blue_slime : public monster
{

public:
	blue_slime();
	~blue_slime();

	HRESULT init();
	void release();
	void update(Player* cp);//플레이어 위치 참고하기위해 
	void render();

	virtual void addMonster(float x, float y);
	virtual void stateCheck();
	virtual void moveMonster();
	virtual void movestate();
	virtual void updateRect(vector<tagMonster>::iterator iter);
};
class orange_slime : public monster
{


public:
	orange_slime();
	~orange_slime();

	HRESULT init();
	void release();
	void update(Player* cp);//플레이어 위치 참고하기위해 
	void render();

	virtual void addMonster(float x, float y);
	virtual void stateCheck();
	virtual void moveMonster();
	virtual void updateRect(vector<tagMonster>::iterator iter);
};
class white_skeleton : public monster
{


public:
	white_skeleton();
	~white_skeleton();

	HRESULT init();
	void release();
	void update(Player* cp,rhythmUI* _rtm);//플레이어 위치 참고하기위해 
	void render();

	virtual void addMonster(float x, float y);
	virtual void stateCheck();
	virtual void moveMonster(rhythmUI* _rtm);
	virtual void updateRect(vector<tagMonster>::iterator iter);
};
