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
	void update(rhythmUI* _rtm);//플레이어 위치 참고하기위해 
	void render();

	virtual void atkSound();
	virtual void addMonster(float x, float y);
	virtual void stateCheck();
	virtual void moveMonster(rhythmUI* _rtm);
	virtual void updateRect(vector<tagMonster>::iterator iter);
};
class green_dragon : public monster
{
public:
	green_dragon();
	~green_dragon();

	HRESULT init();
	void release();
	void update(rhythmUI* _rtm);//플레이어 위치 참고하기위해 
	void render();

	virtual void digsound();
	virtual void movesound();
	virtual void atksound();
	virtual void addMonster(float x, float y);
	virtual void stateCheck();
	virtual void moveMonster(rhythmUI* _rtm,wallManager* _wm,realwallManager* _rwm);
	virtual void updateRect(vector<tagMonster>::iterator iter);
};
class king_konga : public monster
{
public:
	king_konga();
	~king_konga();

	HRESULT init();
	void release();
	void update(rhythmUI* _rtm);//플레이어 위치 참고하기위해 
	void render();


	virtual void atksound();
	virtual void teleport();
	virtual void addMonster(float x, float y);
	virtual void stateCheck();
	virtual void moveMonster(rhythmUI* _rtm,bossMap* _boss, realwallManager* _rwm);
	virtual void updateRect(vector<tagMonster>::iterator iter);
};
